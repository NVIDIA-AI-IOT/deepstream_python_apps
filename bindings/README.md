# DeepStream python bindings

SDK version supported: 6.3

The latest prebuilt release package complete with python bindings and sample applications can be downloaded from the [release section](../../../releases)
for both x86 and Jetson platforms.

This readme describes how to compile and install DeepStream python bindings (henceforth referred as bindings). This process is mainly useful for making customizations in the bindings and compiling it yourself instead of using the prebuilt versions provided in the release section.

The readme is divided into three main parts:
- [DeepStream python bindings](#deepstream-python-bindings)
  - [1 Prerequisites](#1-prerequisites)
    - [1.1 Deepstream SDK](#11-deepstream-sdk)
    - [1.2 Base dependencies](#12-base-dependencies)
    - [1.3 Initialization of submodules](#13-initialization-of-submodules)
    - [1.4 Installing Gst-python](#14-installing-gst-python)
  - [2 Compiling the bindings](#2-compiling-the-bindings)
    - [2.1 Quick build (x86-ubuntu-20.04 | python 3.8 | Deepstream 6.3)](#21-quick-build-x86-ubuntu-2004--python-38--deepstream-63)
    - [2.2 Advanced build](#22-advanced-build)
      - [2.2.1 Using Cmake options](#221-using-cmake-options)
      - [2.2.2 Available cmake options](#222-available-cmake-options)
      - [2.2.3 Example](#223-example)
    - [2.3 Cross-Compilation for aarch64 on x86](#23-cross-compilation-for-aarch64-on-x86)
      - [2.3.1 Build Pre-requisites](#231-build-pre-requisites)
      - [2.3.2 Download the JetPack SDK 5.1.2](#232-download-the-jetpack-sdk-512)
      - [2.3.3 Generate the cross-compile build container](#233-generate-the-cross-compile-build-container)
      - [2.3.4 Launch the cross-compile build container](#234-launch-the-cross-compile-build-container)
      - [2.3.5 Build DeepStreamSDK python bindings](#235-build-deepstreamsdk-python-bindings)
  - [3 Installing the bindings](#3-installing-the-bindings)
    - [3.1 Installing the pip wheel](#31-installing-the-pip-wheel)
      - [3.1.1 pip wheel troubleshooting](#311-pip-wheel-troubleshooting)
    - [3.2 Launching test-1 app](#32-launching-test-1-app)

<a name="prereqs"></a>
## 1 Prerequisites

The following dependencies need to be met in order to compile bindings:

<a name="prereq_ds"></a>
### 1.1 Deepstream SDK
Go to https://developer.nvidia.com/deepstream-sdk, download and install Deepstream SDK and its dependencies

<a name="prereq_base"></a>
### 1.2 Base dependencies
To compile bindings on Ubuntu - 20.04 [use python-3.8, python-3.6 will not work] :
```
apt install python3-gi python3-dev python3-gst-1.0 python-gi-dev git \
    python3 python3-pip python3.8-dev cmake g++ build-essential libglib2.0-dev \
    libglib2.0-dev-bin libgstreamer1.0-dev libtool m4 autoconf automake libgirepository1.0-dev libcairo2-dev
```

<a name="prereq_init_sub"></a>
### 1.3 Initialization of submodules
Make sure you clone the deepstream_python_apps repo under <DeepStream 6.3 ROOT>/sources:
git clone https://github.com/NVIDIA-AI-IOT/deepstream_python_apps

This will create the following directory:
```
<DeepStream 6.3 ROOT>/sources/deepstream_python_apps
```

The repository utilizes gst-python and pybind11 submodules.
To initializes them, run the following command:
```bash
cd /opt/nvidia/deepstream/deepstream/sources/deepstream_python_apps/
git submodule update --init
```
<a name="prereq_install_gst"></a>
### 1.4 Installing Gst-python

Following commands ensure we add the new certificates that gst-python git server now uses:
```bash
sudo apt-get install -y apt-transport-https ca-certificates -y
sudo update-ca-certificates
```

Build and install gst-python:
```bash
cd 3rdparty/gst-python/
./autogen.sh
make
sudo make install
```

<a name="compile_bindings"></a>
## 2 Compiling the bindings
Python bindings are compiled using CMake.
Following commands provide quick cmake configurations for common compilation options:

<a name="compile_quick"></a>
### 2.1 Quick build (x86-ubuntu-20.04 | python 3.8 | Deepstream 6.3)
```bash
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake ..
make -j$(nproc)
```

<a name="compile_advance"></a>
### 2.2 Advanced build

#### 2.2.1 Using Cmake options

Multiple options can be used with cmake as follows:
```bash
cmake .. [-D<var>=<value> [-D<var>=<value> [-D<var>=<value> ... ]]]
```
#### 2.2.2 Available cmake options

| Var | Default value | Purpose | Available values
|-----|:-------------:|---------|:----------------:
| DS_VERSION | 6.3 | Used to determine default deepstream library path | should match to the deepstream version installed on your computer
| PYTHON_MAJOR_VERSION | 3 | Used to set the python version used for the bindings | 3
| PYTHON_MINOR_VERSION | 8 | Used to set the python version used for the bindings | 6, 8
| PIP_PLATFORM | linux_x86_64 | Used to select the target architecture to compile the bindings | linux_x86_64, linux_aarch64
| DS_PATH | /opt/nvidia/deepstream/deepstream-${DS_VERSION} | Path where deepstream libraries are available | Should match the existing deepstream library folder

#### 2.2.3 Example 

Following commands can be used to compile the bindings natively on Jetson devices

```bash
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake ..  -DPYTHON_MAJOR_VERSION=3 -DPYTHON_MINOR_VERSION=8 \
    -DPIP_PLATFORM=linux_aarch64 -DDS_PATH=/opt/nvidia/deepstream/deepstream/
make
```

<a name="compile_cross"></a>
### 2.3 Cross-Compilation for aarch64 on x86

This section outlines how to enable cross-compiling of the DeepStreamSDK python bindings for aarch64 using Docker on x86 host.

NOTE: This will only emulate the CPU, so any calls requiring embedded hardware, such as using CUDA or inference are not supported.

#### 2.3.1 Build Pre-requisites

We use [qemu](https://www.qemu.org/) processor emulator to achieve cross-compilation. Qemu can be installed on the x86 Ubuntu host machine as shown below:

```bash
# Install qemu packages
sudo apt-get install qemu binfmt-support qemu-user-static

# Execute the registering scripts
docker run --rm --privileged dockerhub.nvidia.com/multiarch/qemu-user-static --reset -p yes

# Verify qemu installation
docker run --rm -t  nvcr.io/nvidia/deepstream-l4t:6.3-samples uname -m
#aarch64
```

#### 2.3.2 Download the JetPack SDK 5.1.2
Cross-compilation for Jetson on x86 host requires some low level libraries which can be downloaded using SDK Manager.
Follow these steps to obtain these libraries, which are utilized by the docker build later.

1. Download and install the [NVIDIA SDK manager](https://developer.nvidia.com/nvidia-sdk-manager)
2. Launch the SDK Manager and login with your NVIDIA developer account.
3. Select the platform and target OS (example: Jetson AGX Xavier, `Linux Jetpack 5.1.2`) and click Continue.
4. Under `Download & Install Options` change the download folder and select `Download now, Install later`. Agree to the license terms and click Continue.
5. Go to the download folder, and run:

```bash
# create directories as follows:
mkdir -p deepstream_python_apps/bindings/docker/jetpack_files
# <path/to> would be /opt/nvidia/deepstream/deepstream/sources/deepstream_python_apps/
# where you downloaded the deepstream_python_apps repository
mv ~/Downloads/nvidia/sdkm_downloads/* <path/to>/deepstream_python_apps/bindings/docker/jetpack_files
```

#### 2.3.3 Generate the cross-compile build container

Below command generates the build container

```bash
# cd to bindings dir
cd deepstream_python_apps/bindings
# Make sure you are in deepstream_python_apps/bindings directory
# This command builds the cross-compile docker and adds the mentioned tag
docker build --tag=deepstream-6.3-ubuntu20.04-python-l4t -f qemu_docker/ubuntu-cross-aarch64.Dockerfile .
```

#### 2.3.4 Launch the cross-compile build container

```bash
# Create a directory to mount to the container and store your pyds wheel package in
mkdir export_pyds

# Run the container. Make sure the tag matches the one from Generate step above
docker run -it --entrypoint bash -v $PWD/export_pyds:/export_pyds deepstream-6.3-ubuntu20.04-python-l4t
```

#### 2.3.5 Build DeepStreamSDK python bindings

After the container launches successfully, while inside the cross-compile docker, run following commands:

```bash
# cd to /opt/nvidia/deepstream/deepstream/sources/ dir
cd /opt/nvidia/deepstream/deepstream/sources/

# Sync deepstream_python_apps repo from github
git clone https://github.com/NVIDIA-AI-IOT/deepstream_python_apps.git

cd deepstream_python_apps/bindings/

# Initialize submodules
git submodule update --init

# Create build dir and cd to it
mkdir build && cd build

# Run cmake with following options
cmake ..  -DPYTHON_MAJOR_VERSION=3 -DPYTHON_MINOR_VERSION=8 -DPIP_PLATFORM=linux_aarch64 -DDS_PATH=/opt/nvidia/deepstream/deepstream

# Build pybind wheel and pyds.so
make -j$(nproc)

# Copy the pyds wheel package to the export dir
cp pyds-*.whl /export_pyds
```

Build output (pip wheel) is copied to the previously created export_pyds directory (deepstream_python_apps/bindings/export_pyds) on the host machine.

<a name="install_bindings"></a>
## 3 Installing the bindings
Following commands can be used to install the generated pip wheel.

<a name="install_wheel"></a>
### 3.1 Installing the pip wheel
```bash
pip3 install ./pyds-1.1.8-py3-none*.whl
```

#### 3.1.1 pip wheel troubleshooting
If the wheel installation fails, upgrade the pip using the following command:
```bash
python3 -m pip install --upgrade pip
```

<a name="install_launch"></a>
### 3.2 Launching test-1 app
```bash
cd apps/deepstream-test1
python3 deepstream_test_1.py <input .h264 file>
```
