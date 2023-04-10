import pexpect
import re

child = pexpect.spawn("./team15")

child.expect("passphrase:")

output = child.before.decode("utf-8") + "passphrase:"

print(output, end="")

magic_number = re.findall(r"\d{5}", output)[0]

child.sendline(f"{4294967295 + int(magic_number) + 1}")

print(child.read().decode("utf-8"), end="")