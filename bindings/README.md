# Deepstream python bindings

## 1 - Purpose

This file describes how to compile and install deepstream python bindings

## 2 - Prerequisites

The following dependencies need to be met:

### 2.1 Base dependencies
Ubuntu - 18.04 :
```
apt install -y git python-dev python3 python3-pip python3.6-dev python3.8-dev cmake g++ build-essential \
    libglib2.0-dev libglib2.0-dev-bin python-gi-dev libtool m4 autoconf automake
```

Ubuntu - 20.04 [use python-3.8, python-3.6 will not work] :
```
apt install python3-gi python3-dev python3-gst-1.0 python-gi-dev git python-dev \
    python3 python3-pip python3.8-dev cmake g++ build-essential libglib2.0-dev \
    libglib2.0-dev-bin python-gi-dev libtool m4 autoconf automake
```

### 2.2 Initialization of submodules
```
git submodule update --init
```
### 2.3 Installing Gst-python

Following commands ensure we add the new certificates that gst-python git server now uses:
```
sudo apt-get install -y apt-transport-https ca-certificates -y
sudo update-ca-certificates
```

Build and install gst-python:
```
cd 3rdparty/gst-python/
./autogen.sh
make
make install
```
### 2.4 - Deepstream SDK
Go to https://developer.nvidia.com/deepstream-sdk, download and install Deepstream SDK and its dependencies

## 3 - Building the bindings

### 3.1 Quick build (x86-ubuntu-18.04 | python 3.6 | Deepstream 6.0.1)
```
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake .. -DPYTHON_MAJOR_VERSION=3 -DPYTHON_MINOR_VERSION=6
make
```

### 3.1.1 Quick build (x86-ubuntu-20.04 | python 3.8 | Deepstream 6.1)

```
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake ..
make
```


### 3.2 Advanced build

#### 3.2.1 Using Cmake options

Multiple options can be passed to cmake as follows:
```
cmake [-D<var>=<value> [-D<var>=<value> [-D<var>=<value> ... ]]]
```
#### 3.2.2 Available cmake options

| Var | Default value | Purpose | Available values
|-----|:-------------:|---------|:----------------:
| DS_VERSION | 6.1 | Used to determine default deepstream library path | should match to the deepstream version installed on your computer
| PYTHON_MAJOR_VERSION | 3 | Used to set the python version used for the bindings | 3
| PYTHON_MINOR_VERSION | 8 | Used to set the python version used for the bindings | 6, 8
| PIP_PLATFORM | linux_x86_64 | Used to select the target architecture to compile the bindings | linux_x86_64, linux_aarch64
| DS_PATH | /opt/nvidia/deepstream/deepstream-${DS_VERSION} | Path where deepstream libraries are available | Should match the existing deepstream library folder

#### 3.2.3 Example 

Following commands can be used to build the bindings natively on Jetson devices

```
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake ..  -DPYTHON_MAJOR_VERSION=3 -DPYTHON_MINOR_VERSION=8 \
    -DPIP_PLATFORM=linux_aarch64 -DDS_PATH=/opt/nvidia/deepstream/deepstream/
make
```

### 3.3 Cross-Compilation for aarch64 on x86

This section outlines how to enable cross-compiling of the DeepStreamSDK python bindings for aarch64 using Docker on x86 host.

NOTE: This will only emulate the CPU, so any calls requiring embedded hardware, such as using CUDA or inference are not supported.

#### 3.3.1 Build Pre-requisites

We use [qemu](https://www.qemu.org/) processor emulator to achieve cross-compilation. Qemu can be installed on the x86 Ubuntu host machine as shown below:

```bash
# Install qemu packages
sudo apt-get install qemu binfmt-support qemu-user-static

# Execute the registering scripts
docker run --rm --privileged dockerhub.nvidia.com/multiarch/qemu-user-static --reset -p yes

# Verify qemu installation
docker run --rm -t  nvcr.io/nvidia/deepstream-l4t:6.1-samples uname -m
#aarch64
```

#### 3.3.2 Download the JetPack SDK 5.0.1 DP
1. Download and install the [NVIDIA SDK manager](https://developer.nvidia.com/nvidia-sdk-manager)
2. Launch the SDK Manager and login with your NVIDIA developer account.
3. Select the platform and target OS (example: Jetson AGX Xavier, `Linux Jetpack 5.0.1 DP`) and click Continue.
4. Under `Download & Install Options` change the download folder and select `Download now, Install later`. Agree to the license terms and click Continue.
5. Go to the download folder, and run:

```bash
# path/to/deepstream_python_apps is the path where you downloaded the deepstream_python_apps repository
mkdir -p path/to/deepstream_python_apps/bindings/docker/jetpack_files
mv ~/Downloads/nvidia/sdkm_downloads/* path/to/deepstream_python_apps/bindings/docker/jetpack_files
```

#### 3.3.3 Generate the cross-compile build container

Below command generates the build container

```bash
# Make sure you are in deepstream_python_apps/bindings directory
docker build --tag=deepstream-6.1-ubuntu20.04-python-l4t -f qemu_docker/ubuntu-cross-aarch64.Dockerfile .
```

#### 3.3.4 Launch the cross-compile build container

```bash
# Create a directory to mount to the container and store your pyds wheel package in
mkdir export_pyds

# Make sure the tag matches the one from Generate step above
docker run -it -v $PWD/export_pyds:/export_pyds deepstream-6.1-ubuntu20.04-python-l4t bash
```

#### 3.3.5 Build DeepStreamSDK python bindings

Inside the cross-compile docker, run following commands:

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

Build output is generated in the created export_pyds directory (deepstream_python_apps/bindings/export_pyds).

## 4 - Using the generated pip wheel

### 4.1 Installing the pip wheel
```
apt install libgirepository1.0-dev libcairo2-dev
pip3 install ./pyds-1.1.2-py3-none*.whl
```

#### 4.1.1 pip wheel troubleshooting
Please make sure you upgrade pip if the wheel installation fails

### 4.2 launching test 1 app
```
cd apps/deepstream-test1
python3 deepstream_test_1.py <input .h264 file>
```
