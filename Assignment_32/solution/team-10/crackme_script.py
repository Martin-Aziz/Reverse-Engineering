import subprocess

# With buffer overflow
crackme_input = "A"*44 + "HSMA"
print(f"\nUsing this string for buffer overflow:\n{crackme_input}")

print("\nOutput of the crackme with buffer overflow:")
p = subprocess.run(['./crackme'], input=crackme_input, capture_output=True, text=True)
print(p.stdout)

# With the correct password
correct_password = "Cr4zy_s3cr3t_p4ssword!!!"
print(f"\nUsing password of the crackme:\n{correct_password}")

print("\nOutput of the crackme with correct password:")
p = subprocess.run(['./crackme'], input=correct_password, capture_output=True, text=True)
print(p.stdout)
