#!/bin/bash
echo "Applying changes"
printf '\x32\x60' | dd status=none conv=notrunc of=license.key bs=1 seek=$((0x00000000))
printf '\x14\x00\x0E\x13\x2B\x10' | dd status=none conv=notrunc of=license.key bs=1 seek=$((0x00000003))
echo "Running program"
./crackme14
