#!/usr/bin/python
#source: http://www.tutorialspoint.com/python/python_networking.htm

import socket

s = socket.socket()
host = socket.gethostname()
port = 10024
s.bind((host, port))

s.listen(10)

while True:
  c, addr = s.accept()
  print 'SERVER: Connection from ', addr
  c.send('thanks for connecting')
  c.close()
