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

"""
Script for parsing pybind11 code to create rst files for Sphinx Documentation
"""

import os

# Directory containing bindings source code files
bindings_dir = "../bindings/src/"
# List of bindings code file names to parse (assumes files are in bindings_dir)
bindings_list = "./bindings_file_list.txt"
# Directory to write output files
output_dir = "./PYTHON_API/"

# Create output dir if not already existing
if not os.path.isdir(output_dir):
    os.mkdir(output_dir)

# Read file names from bindings_list and store into list
fileL = []
with open(bindings_list) as f:
    fileL = [filename.strip() for filename in f]

# Iterate through file in list of files
for filename in fileL:
    # Get file path
    filepath = bindings_dir + filename
    # Initialize name, output directory, and toctree file name for API group
    api_name = ''
    api_output_dir = ''
    api_toctree_file = ''
    # Open bindings file
    with open(filepath) as f:
        # Iterate through lines in file
        for line in f:
            line = line.strip()
            # API name is taken from first comment in the file
            if not api_name and line.startswith("//"):
                # Comment with API name should be formatted as "// API_NAME"
                # So split by whitespace and take second element of list
                api_name = line.split()[1]
                api_output_dir = output_dir + api_name + '/'
                api_toctree_file = api_output_dir + api_name + '_toc.rst'
                # Create output directory if not already existing
                if not os.path.isdir(api_output_dir):
                    os.mkdir(api_output_dir)
                # Create toctree file
                with open(api_toctree_file, 'w') as o:
                    o.write("=" * len(api_name) + '\n')
                    o.write(api_name + '\n')
                    o.write("=" * len(api_name) + "\n\n")
                    o.write(".. toctree::")

            # Search for py::class keyword to find classes
            if api_toctree_file and "py::class" in line:
                # Code looks like: 
                # py::class_<CLASS_NAME>(m,"CLASS_NAME", docstring_name)
                # So split by " and take second/middle element of list
                class_name = line.split('"')[1]
                # Append the class name to the toctree file of the API
                with open(api_toctree_file, 'a') as o:
                    o.write('\n\t' + class_name)
                # Create rst file for class directives
                class_file = api_output_dir + class_name + ".rst"
                with open(class_file, 'w') as o:
                    o.write("=" * len(class_name) + '\n')
                    o.write(class_name + '\n')
                    o.write("=" * len(class_name) + "\n\n")
                    o.write(".. autoclass:: pyds." + class_name + '\n')
                    o.write("\t:members:")

            # Search for py::enum keyword to find enumerators
            if api_toctree_file and "py::enum" in line:
                # Code looks like: 
                # py::enum_<ENUM_NAME>(m,"ENUM_NAME", docstring_name)
                # So split by " and take second/middle element of list
                enum_name = line.split('"')[1]
                # Append the enum name to the toctree file of the API
                with open(api_toctree_file, 'a') as o:
                    o.write('\n\t' + enum_name)
                # Create rst file for enum directives
                enum_file = api_output_dir + enum_name + ".rst"
                with open(enum_file, 'w') as o:
                    o.write("=" * len(enum_name) + '\n')
                    o.write(enum_name + '\n')
                    o.write("=" * len(enum_name) + "\n\n")
                    o.write(".. autodata:: pyds." + enum_name + '\n')
                    o.write("\t:annotation:")