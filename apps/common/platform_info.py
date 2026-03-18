################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
################################################################################

import sys
import platform
import os
from pathlib import Path
from typing import Dict, Tuple
from threading import Lock
from cuda.bindings import runtime
from cuda.bindings import driver

guard_platform_info = Lock()

class PlatformInfo:
    def __init__(self):
        self.is_wsl_system = False
        self.wsl_verified = False
        self.is_integrated_gpu_system = False
        self.is_integrated_gpu_verified = False
        self.is_aarch64_platform = False
        self.is_aarch64_verified = False
        self.is_dgx_spark_platform = False

    def is_wsl(self):
        with guard_platform_info:
            # Check if its already verified as WSL system or not.
            if not self.wsl_verified:
                try:
                    # Open /proc/version file
                    with open("/proc/version", "r") as version_file:
                        # Read the content
                        version_info = version_file.readline()
                        version_info = version_info.lower()
                        self.wsl_verified = True

                        # Check if "microsoft" is present in the version information
                        if "microsoft" in version_info:
                            self.is_wsl_system = True
                except Exception as e:
                    print(f"ERROR: Opening /proc/version failed: {e}")

        return self.is_wsl_system
    
    def is_integrated_gpu(self):
        #Using cuda apis to identify whether integrated/discreet
        #This is required to distinguish Tegra and ARM_SBSA devices
        with guard_platform_info:
            #Cuda initialize
            if not self.is_integrated_gpu_verified:
                cuda_init_result, = driver.cuInit(0)
                if  cuda_init_result == driver.CUresult.CUDA_SUCCESS:
                    #Get cuda devices count
                    device_count_result, num_devices = driver.cuDeviceGetCount()
                    if device_count_result == driver.CUresult.CUDA_SUCCESS:
                        #If atleast one device is found, we can use the property from
                        #the first device
                        if num_devices >= 1:
                            #Get properties from first device
                            property_result, properties = runtime.cudaGetDeviceProperties(0)
                            if property_result == runtime.cudaError_t.cudaSuccess:
                                print("Is it Integrated GPU? :", properties.integrated)
                                self.is_integrated_gpu_system = properties.integrated
                                self.is_integrated_gpu_verified = True
                            else:
                                print("ERROR: Getting cuda device property failed: {}".format(property_result))
                        else:
                            print("ERROR: No cuda devices found to check whether iGPU/dGPU")
                    else:
                        print("ERROR: Getting cuda device count failed: {}".format(device_count_result))
                else:
                    print("ERROR: Cuda init failed: {}".format(cuda_init_result))

        return self.is_integrated_gpu_system

    def is_platform_aarch64(self):
        #Check if platform is aarch64 using uname
        if not self.is_aarch64_verified:
            if platform.uname()[4] == 'aarch64':
                self.is_aarch64_platform =  True
            self.is_aarch64_verified = True
        return self.is_aarch64_platform

    DMI_PATHS = {
        "product_name": Path("/sys/class/dmi/id/product_name"),
        "board_name": Path("/sys/class/dmi/id/board_name"),
        "product_sku": Path("/sys/class/dmi/id/product_sku"),
        "sys_vendor": Path("/sys/class/dmi/id/sys_vendor"),
    }

    def read_dmi_field(self, path: Path) -> str:
        try:
            if path.is_file():
                return path.read_text(encoding="utf-8", errors="ignore").strip()
        except Exception:
            pass
        return ""

    def is_dgx_spark(self) -> bool:
        """
        Return True if this system is detected as DGX Spark, else False.
        Detection is based on DMI product/board/SKU strings.
        """
        product_name = self.read_dmi_field(self.DMI_PATHS["product_name"])
        board_name = self.read_dmi_field(self.DMI_PATHS["board_name"])
        product_sku = self.read_dmi_field(self.DMI_PATHS["product_sku"])

        combined = " ".join(
            s for s in (product_name, board_name, product_sku) if s
        ).lower()

        self.is_dgx_spark_platform = "dgx spark" in combined
        return self.is_dgx_spark_platform


sys.path.append('/opt/nvidia/deepstream/deepstream/lib')
