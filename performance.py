import sys
import time
import os
from subprocess import Popen, PIPE
from time import sleep
from threading import Thread

#Reads in arguements 
hashList = sys.argv[1]
algorithm = sys.argv[2]
timeout = int(sys.argv[3])
f = open(hashList)
o = open('passlist/passwords.txt', 'w+')

#Reads a hash from hash list file
def readHash():
    global cracked
    cracked = 0
    while True:
	for line in iter(f):
		if not line:
			break;
		command = "./"+ str(algorithm) + " "+str(line)
		print command	
		pipe = Popen(command,shell=True,stdout=PIPE,stderr=PIPE)     
        	line = pipe.stdout.readline()
		if "The password is " in line:
			o.write(line)
			cracked += 1
		print line
        break

#Create a seperate thread to run password 
#algorithm and stop after certain time
t = Thread(target=readHash)                                
t.daemon = True                                             
t.start()
snooziness = int(timeout)
sleep(snooziness)

f.close()
o.close()
result = "Finished after " + str(timeout) + " seconds with " + str(cracked) + " passwords written to passlist/passwords.txt " 
print result
