#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk 2> /dev/null
make clean > /dev/null && cd Toolchain && make clean > /dev/null
