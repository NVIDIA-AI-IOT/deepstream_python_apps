# SPDX-FileCopyrightText: Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

FROM nvcr.io/nvidia/deepstream-l4t:6.1.1-samples
LABEL maintainer="NVIDIA CORPORATION"

# Set timezone.
ENV TZ=America/Los_Angeles

# Install requried libraries
RUN apt-get update && apt-get install -y software-properties-common
RUN apt-get update && apt-get install -y --no-install-recommends \
    libcurl4-openssl-dev \
    wget \
    curl \
    zlib1g-dev \
    git \
    pkg-config \
    python3 \
    python3-pip \
    python3-dev \
    python3-wheel \
    g++ \
    libglib2.0-dev \
    libglib2.0-dev-bin \
    python-gi-dev \
    libtool \
    m4 \
    autoconf \
    automake \
    sudo \
    ssh \
    pbzip2 \
    pv \
    bzip2 \
    unzip \
    cmake \
    build-essential \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstrtspserver-1.0-dev \
    libglew-dev \
    libssl-dev \
    libopencv-dev \
    freeglut3-dev \
    libjpeg-dev \
    libjson-glib-dev \
    libcairo2-dev \
    libpango1.0-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libgtk-3-dev \
    libpng-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    librabbitmq-dev

RUN pip3 install --upgrade pip
RUN pip3 install setuptools>=41.0.0

COPY docker/jetpack_files/Jetson*Linux_R*aarch64.tbz2 /bsp_files/

# Copy libs from BSP
RUN cd /bsp_files \
    && tar -jxpf Jetson*Linux_R35*aarch64.tbz2 \
    && cd Linux_for_Tegra/nv_tegra \
    && tar -jxpf nvidia_drivers.tbz2 \
    && cp -aprf usr/lib/aarch64-linux-gnu/tegra/libnvbuf*.so.1.0.0 /opt/nvidia/deepstream/deepstream/lib/ \
    && cd /opt/nvidia/deepstream/deepstream/lib/ \
    && rm libnvbufsurface.so libnvbufsurftransform.so \
    && ln -s libnvbuf_utils.so.1.0.0 libnvbuf_utils.so \
    && ln -s libnvbufsurface.so.1.0.0 libnvbufsurface.so \
    && ln -s libnvbufsurftransform.so.1.0.0 libnvbufsurftransform.so
