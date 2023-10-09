#!/bin/bash
printf '\x21\xA0\x00\x2E\x41\x33\x21\xA3\x6C' | dd status=none conv=notrunc of=license.key bs=1 seek=$((0x00000000))
echo "Orginalzustand hergestellt"
