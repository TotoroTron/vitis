Setup:

1) Download "Versal common image" (1.49 GB): 
    https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html
    Extract the tarball.

2) Extract Petalinux via "sdk.h"
    Extract to its own "petalinux/2025.1" dir, NOT to the same common image dir

3) Edit "Host_srcs/Makefile"
    Remove or comment out line: "export SYSROOT := ..."
    (SYSROOT is redefined in "setup_env.sh")

4) make all
