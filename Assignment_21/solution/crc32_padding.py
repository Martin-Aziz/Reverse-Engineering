#!/usr/bin/python

import BitVector as bv
import sys

def bit_reverse(n):
    s = '{:032b}'.format(n)
    return int(s[::-1], 2)

def inverse(k):
    POLY = 0x104C11DB7
    poly = bv.BitVector(intVal = POLY)
    inv = bv.BitVector(intVal = 0x100000000).gf_MI(poly, 32)
    p = bv.BitVector(intVal = k).gf_multiply_modular(inv, poly, 32)
    return int(p.getHexStringFromBitVector(), 16)

def bytes_reverse(n):
    b = (n >> 0 & 0xff,
         n >> 8 & 0xff,
         n >> 16 & 0xff,
         n >> 24 & 0xff)

    r = int('{:08b}'.format(b[0])[::-1], 2) << 0 | \
        int('{:08b}'.format(b[1])[::-1], 2) << 8 | \
        int('{:08b}'.format(b[2])[::-1], 2) << 16 | \
        int('{:08b}'.format(b[3])[::-1], 2) << 24

    return '%#x' % r


if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <target crc32> <actual crc32>")
    sys.exit(1)

crc_new = int(sys.argv[1], 16)
crc_org = int(sys.argv[2], 16)

xor = crc_org ^ crc_new
r_xor = bit_reverse(xor)
inv = inverse(r_xor)

print("Padding-Bytes: " + bytes_reverse(inv))