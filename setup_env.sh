#!/usr/bin/env bash

# ============================================================
#  AMD/Xilinx Vitis 2025.1.1 Environment for VCK190 (Versal AI Core)
# ============================================================

# Tool install roots
export XILINX_TOOLS=/home/bcheng/workspace/tools/Xilinx/2025.1.1
export XILINX_VITIS=$XILINX_TOOLS/Vitis
export XILINX_VIVADO=$XILINX_TOOLS/Vivado

# Common image for runtime
export COMMON_IMAGE_VERSAL=/home/bcheng/workspace/tools/xilinx-versal-common-v2025.1

# Sysroot from Petalinux SDK
export SYSROOT=/home/bcheng/workspace/tools/petalinux/2025.1/sysroots/cortexa72-cortexa53-amd-linux
export SDKTARGETSYSROOT=$SYSROOT

# Platform repo and device
export PLATFORM_REPO_PATHS=$XILINX_VITIS/base_platforms
export PLATFORM=$PLATFORM_REPO_PATHS/xilinx_vck190_base_202510_1/xilinx_vck190_base_202510_1.xpfm

# # Compiler / cross tools
# export CROSS_COMPILE=aarch64-linux-gnu-
# export CC=${CROSS_COMPILE}gcc
# export CXX=${CROSS_COMPILE}g++
# export PATH=$PATH:/usr/bin

# Source Vitis & Vivado setup
source $XILINX_VITIS/settings64.sh
source $XILINX_VIVADO/settings64.sh

# # Memory / Java options
# export _JAVA_OPTIONS="-Xmx32G"

# Sanity check
echo
echo "============================================================"
echo " AMD/Xilinx Vitis 2025.1.1 Environment"
echo "============================================================"
echo "XILINX_TOOLS:        $XILINX_TOOLS"
echo "XILINX_VITIS:        $XILINX_VITIS"
echo "XILINX_VIVADO:       $XILINX_VIVADO"
echo "COMMON_IMAGE_VERSAL: $COMMON_IMAGE_VERSAL"
echo "SYSROOT:             $SYSROOT"
echo "PLATFORM:            $PLATFORM"
echo "CROSS_COMPILE:       $CROSS_COMPILE"
echo "============================================================"
echo "✅ Environment ready. Run: make all"
echo "============================================================"
