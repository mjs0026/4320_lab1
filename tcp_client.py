#!/usr/bin/python
#source: http://www.tutorialspoint.com/python/python_networking.htm

import socket

s = socket.socket()
host = socket.gethostname()
port = 10024

s.connect((host, port))
print s.recv(1024)
s.close()
