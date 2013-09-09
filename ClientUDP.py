import socket 
import sys
import datetime
j = 0
class MessageObj:  
	TML = '%04x' % (len(sys.argv[4]) + 5)
	requestID = '%04x' % 7  
	operation = '%02x' %  int(sys.argv[3])
	message = "".join("{0:x}".format(ord(c)) for c in sys.argv[4])
if sys.argv[3] != str(85) and sys.argv[3] != str(170):
	print "You must choose either 85 or 170"
	exit()
obj = MessageObj()
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
start = datetime.datetime.now()
s.sendto(( obj.TML + obj.requestID + obj.operation + obj.message), (sys.argv[1], int(sys.argv[2])))
recieve = s.recv(256)
end = datetime.datetime.now()
print "Length " + str(int(recieve[0:4], 16))
print "Request ID: " + str(int(recieve[4:8], 16))
if sys.argv[3] == '85':
	print "Number of vowels: " + str(int(recieve[8:], 16))
else:
	print "Message without vowels: " + recieve[8:].decode("hex")
print "Transmission time: " + str((end - start).microseconds) + " microseconds"


