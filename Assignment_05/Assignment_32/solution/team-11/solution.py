import pexpect

# 1. Decrypt the license
decrypted_license = []
encrypted_license = [0x2c, 0x3a, 0x27, 0x2c, 0x2a, 0x20, 0x26, 0x25]

# Convert little to big endian
encrypted_license = reversed(encrypted_license)

# XOR decrypt license with the constant 0x69
decrypted_license = [chr(byte^0x69) for byte in encrypted_license]

# 2. Exploit the buffer overflow
prefix = "".join(decrypted_license)
padding = "A" * 120
address = chr(0x37) + chr(0x21) + chr(0x40) # 0x402137
# alternatively: address = "7!@"

executable = './crackme'
proc = pexpect.spawn(executable)

# wait for prompt
proc.expect('Please enter a valid license key:')
proc.write(prefix + padding + address + "\n")
proc.expect('FLAG')
print("Flag found:", proc.buffer.decode("utf-8"))
proc.kill(0)
