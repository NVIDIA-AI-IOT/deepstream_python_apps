# SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import configparser


def get_tracker_properties_from_config(config_path):
    config = configparser.ConfigParser()
    config.read(config_path)
    config.sections()

    get_attr = lambda k: config.get('tracker', k)
    getint_attr = lambda k: config.getint('tracker', k)

    keys_getter = {
        'tracker-width': getint_attr,
        'tracker-height': getint_attr,
        'gpu-id': getint_attr,
        'll-lib-file': get_attr,
        'll-config-file': get_attr
    }
    tracker_properties = {}
    for key in config['tracker']:
        if key not in keys_getter:
            raise Exception(f"Key: {key} not allowed in {config_path}")
        tracker_attr = keys_getter[key](key)
        tracker_properties[key] = tracker_attr
    return tracker_properties