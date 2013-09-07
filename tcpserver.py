import SocketServer
import binascii
import sys

class TCPHandler(SocketServer.BaseRequestHandler):


  def handle(self):
      
    msg = self.request.recv(1024)
    print "{} wrote:".format(self.client_address[0])
    print msg

  def vowels(self, string):
    vowels = "aeiouAEIOU"
    return str(len([letter for letter in string if letter in vowels]))

  def devowel(self, string):
    vowels = "aeiouAEIOU"
    return ''.join(letter for letter in string if letter not in vowels)


if __name__ == "__main__":


  HOST = ''
  PORT =  int(sys.argv[2])

  server = SocketServer.TCPServer((HOST, PORT), TCPHandler)

  server.serve_forever()


