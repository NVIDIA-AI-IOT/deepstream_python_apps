/*
 * SPDX-FileCopyrightText: Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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



#pragma  once

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
#include <memory>
#include <optional>
#include <mutex>
#include <pybind11/cast.h>
#include <pybind11.h>

namespace py = pybind11;

namespace pydeepstream {
    // rewritting ""_a operator from pybind11 namespace and putting it into
    // pydeepstream namespace
    pybind11::arg operator ""_a(const char *str, size_t len);
}


namespace pydeepstream::utils {

    using COPYFUNC_SIG = gpointer(gpointer, gpointer);
    using RELEASEFUNC_SIG = void(gpointer, gpointer);

    /// Purpose:
    /// This templated struct allows storing std::function at compile time
    /// in a predetermined memory space, so that a function pointer
    /// referencing that std::function can be retrieved and stored
    /// somewhere else.
    /// This allows storing a function pointer in a C struct
    /// which will be used from some callbacks.
    /// This struct should not be used if you intend to work only
    /// with C++ app, please use directly std::function instead.
    /// UniqueName: used to create a unique function_storage
    /// RetValue: return value of the function
    /// ArgTypes: All function arguments
    template<const char *UniqueName, typename RetValue, typename... ArgTypes>
    struct function_storage {
    public:

        /// This allows decoupling std::function from the return value and arguments
        typedef std::optional<std::function<RetValue(ArgTypes...)>> function_type;

        /// Stores the provided std::function statically in the instanciated templated struct
        static void store(const function_type &f) {
            const std::lock_guard<std::mutex> lock(instance().mut_);
            auto &inst = instance();
            if(!inst.stopped_)
                inst.fn_ = f;
        }

	static void
	__attribute__((optimize("O0")))
	free_instance(){
            auto &inst = instance();
            const std::lock_guard<std::mutex> lock(inst.mut_);
            auto &opt = inst.fn_;
            if (opt.has_value()){
                opt.reset();
	    }
            inst.stopped_=true;
	}

        /// Helps defining the actual function pointer needed
        static RetValue invoke(ArgTypes... args) {
            const std::lock_guard<std::mutex> lock(instance().mut_);
            auto &opt = instance().fn_;
            // here we check if the function's content is valid before calling it,
            // as it can be empty if free instance is called. In that case we return
            // the default value of RetValue type. RetValue must have a default
            // constructor with no parameters.
            if (!opt.has_value())
                return RetValue();
            auto &fun = opt.value();
            if (!fun)
                return RetValue();
            return fun(args...);
        }

        /// Declares the type of pointer returned
        typedef decltype(&function_storage::invoke) pointer_type;

        /// Returns a function pointer that can be stored
        static pointer_type get_ptr() { return &invoke; }

    private:
        static function_storage &instance() {
            static function_storage inst_;
            return inst_;
        }

        /// contains a storage for an std::function.
        function_type fn_;
	std::mutex mut_;
	bool stopped_=false;
    };

    // Is used to keep track of font names without duplicate
    // since std::string::c_str() returns as const char*, it cannot be used
    // as is. We need a char *, that's the reason why a std::shared_ptr<char>
    // is used
    extern std::unordered_map<std::string, std::shared_ptr<char>> font_name_memory;

    template<typename TYPE, typename FIELDTYPE>
    auto get_field_content_lambda(FIELDTYPE member) {
        return [member](TYPE *object) {
            return reinterpret_cast<size_t>((*object).*member);
        };
    }

    template<typename TYPE, typename FIELDTYPE>
    auto set_field_content_string_lambda(FIELDTYPE member) {
        return [member](TYPE *object, std::string str) {
            auto &map_str = font_name_memory;
            const auto &search = map_str.find(str);
            if (search == map_str.end()) {
                auto tmp_str = std::shared_ptr<char>(
                        new char[str.size() + 1],
                        std::default_delete<char[]>());
                for (uint i = 0; i < str.size(); ++i)
                    tmp_str.get()[i] = str[i];
                tmp_str.get()[str.size()] = '\0';
                map_str[str] = tmp_str;
            }
            (*object).*member = map_str[str].get();
        };
    }

    template<const char *UniqueName, typename RetValue, typename... ArgTypes>
    typename function_storage<UniqueName, RetValue, ArgTypes...>::pointer_type
    get_fn_ptr_from_std_function(
            const std::function<RetValue(ArgTypes...)> &f) {
        typedef function_storage<UniqueName, RetValue, ArgTypes...> custom_fun;
        custom_fun::store(f);
        return custom_fun::get_ptr();
    }

    template<const char *UniqueName, typename RetValue, typename... ArgTypes>
    typename function_storage<UniqueName, RetValue, ArgTypes...>::pointer_type
    __attribute__((optimize("O0")))
    free_fn_ptr_from_std_function(const std::function<RetValue(ArgTypes...)> &f) {
        typedef function_storage<UniqueName, RetValue, ArgTypes...> custom_fun;
        custom_fun::free_instance();
    }

    void
    set_copyfunc(NvDsUserMeta *meta,
                 std::function<COPYFUNC_SIG> const &func);

    void set_freefunc(NvDsUserMeta *meta,
                      std::function<RELEASEFUNC_SIG> const &func);

    void release_all_func();

    void generate_ts_rfc3339(char *buf, int buf_size);
}


