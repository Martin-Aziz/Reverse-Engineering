import os
from subprocess import Popen, PIPE

p = Popen('./crackme_12', stdin=PIPE, text=True) #NOTE: no shell=True here
p.communicate('bird')

