/*
 * SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gst/gst.h>
#include <glib.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/timeb.h>
#include <functional>
#include <iostream>
#include "gstnvdsmeta.h"
#include "nvdsmeta_schema.h"
#include "utils.hpp"
/**
 * Specifies the type of function to copy meta data.
 * It is passed the pointer to meta data and user specific data.
 * It allocates the required memory, copies the content from src metadata
 * and returns the pointer to newly allocated memory.
 *
 * user_data is for internal purpose only. User should set it to NULL.
 */
using COPYFUNC_SIG = gpointer(gpointer, gpointer);
/**
 * Specifies the type of function to free meta data.
 * It is passed the pointer to meta data and user specific data.
 * It should free any resource allocated for meta data.
 *
 * user_data is for internal purpose only. User should set it to NULL.
 */
using RELEASEFUNC_SIG = void(gpointer, gpointer);

namespace pydeepstream {
    pybind11::arg operator ""_a(const char *str, size_t len) {
        return pybind11::arg(str);
    }
}

namespace pydeepstream::utils {

    std::unordered_map<std::string, std::shared_ptr<char>> font_name_memory;
    static const char copyfuncname[] = "copy_func"; // must be unique
    static const char freefuncname[] = "free_func"; // must be unique
    /// The returned pointer from get_fn_ptr_from_std_function is the same for all
    /// instance templated on 'copy_func' string literal. Therefore it must only be
    /// stored at one place. In case of multiple registration the latest stored
    /// std::function will be the one called. The std::function 'func' is stored
    /// statically.
    void
    set_copyfunc(NvDsUserMeta *meta,
                 std::function<COPYFUNC_SIG> const &func) {
        // must be stored only at 1 place
        meta->base_meta.copy_func = get_fn_ptr_from_std_function<copyfuncname>(func);
    }

    /// same as set_copyfunc
    void set_freefunc(NvDsUserMeta *meta,
                      std::function<RELEASEFUNC_SIG> const &func) {
        // must be stored only at 1 place
        meta->base_meta.release_func = get_fn_ptr_from_std_function<freefuncname>(func);
    }

    void
    __attribute__((optimize("O0")))
    release_all_func() {
	// these dummy functions are only used for their type to match the appropriate template
	const auto dummy_copy_func = std::function<COPYFUNC_SIG>();
	const auto dummy_free_func = std::function<RELEASEFUNC_SIG>();
        // Here the functions must be freed because otherwise the destructor will be stuck with GIL
        // this is related to pybind11 behavior.
        // As far as I understand pybind11 does not expect us to store functions in a static storage
        // it tries to acquire a lock inside its custom destructor of these functions, but the lock was
	// destroyed before, thus creating a deadlock at program exit...
	free_fn_ptr_from_std_function<copyfuncname>(dummy_copy_func);
        free_fn_ptr_from_std_function<freefuncname>(dummy_free_func);
    }


    void generate_ts_rfc3339(char *buf, int buf_size) {
        time_t tloc;
        struct tm tm_log{};
        struct timespec ts{};
        char strmsec[6]; //.nnnZ\0
        clock_gettime(CLOCK_REALTIME, &ts);
        memcpy(&tloc, (void *) (&ts.tv_sec), sizeof(time_t));
        gmtime_r(&tloc, &tm_log);
        strftime(buf, buf_size, "%Y-%m-%dT%H:%M:%S", &tm_log);
        int ms = ts.tv_nsec / 1000000;
        g_snprintf(strmsec, sizeof(strmsec), ".%.3dZ", ms);
        strncat(buf, strmsec, buf_size);
    }
}
