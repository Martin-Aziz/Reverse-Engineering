FlagLength = 21
Key = "sup3r_s3cr3t_k3y_1337"
buffer = bytearray(FlagLength + 30)

for i in range(FlagLength):
	buffer[i + 24] = ord(Key[i]) -34
	
xorStream = bytearray([0x37, 0x3F, 0x2F, 0x76, 0x2B, 0x62, 0x28, 0x21, 0x34, 0xF, 0x77, 0x62, 0x48, 0x27, 0x75, 0x8, 0x56, 0x6A, 0x68, 0x4E, 0x68])

buffer[:len(xorStream)] = xorStream

for i in range(FlagLength):
	buffer[i] ^= buffer[i + 24]
	
print(buffer[:FlagLength].decode("ASCII"))
