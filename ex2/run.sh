#!/bin/bash

source /home/bcheng/workspace/tools/Xilinx/2025.1.1/Vitis/settings64.sh

export XILINXD_LICENSE_FILE=/home/bcheng/workspace/tools/Xilinx/Xilinx.lic
export COMMON_IMAGE_VERSAL=/home/bcheng/workspace/tools/xilinx-versal-common-v2025.1
export PLATFORM_REPO_PATHS=/home/bcheng/workspace/tools/Xilinx/2025.1.1/Vitis/base_platforms
export COMMON_IMAGE_VERSAL=/home/bcheng/workspace/tools/xilinx-versal-common-v2025.1
export SYSROOT=$COMMON_IMAGE_VERSAL/sysroots/cortexa72-cortexa53-amd-linux
export SDKTARGETSYSROOT=$SYSROOT
export CXX=aarch64-linux-gnu-g++
export CC=aarch64-linux-gnu-gcc

make clean
make all
