import os
import sys
import logging
import time

process_id = os.fork()

if(process_id < 0):
    sys.exit(1) #failure

if(process_id > 0):
    sys.exit(0) #success

if(os.setsid() < 0):
    sys.exit(1) #failure

#double fork
process_id = os.fork()

if(process_id < 0):
    sys.exit(1)

if(process_id > 0):
    sys.exit(0)

os.umask(0)
os.chdir('/')

os.close(sys.stdin.fileno())
os.close(sys.stdout.fileno())
os.close(sys.stderr.fileno())

logging.basicConfig(filename= "mailer_log", filemode= 'w', level= logging.INFO)
logging.info("Daemon Started")

while(True):
    time.sleep(5)
    os.system('./mailer.py')
    break

logging.info("Daemon Terminated")


#get process id
getting_process_id = os.getpid()
print("Process ID: ", getting_process_id)