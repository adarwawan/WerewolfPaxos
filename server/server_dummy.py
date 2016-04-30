from socket import *
from server_structure_dummy import GameServer
from server_structure_dummy import MessageServer

import struct
import thread
import json
import sys, getopt

def listener(clientsocket, clientaddr, GameServer):
	ms = MessageServer(clientsocket, clientaddr, GameServer)
	del ms

def main(argv):
    host = ''
    port = 55555
    addr = (host, port)

    serversocket = socket(AF_INET, SOCK_STREAM)
    serversocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    serversocket.bind(addr)
    serversocket.listen(5)

    gs = GameServer(int(argv[1]))

    while 1:
        print "Server is listening for connections\n"

        clientsocket, clientaddr = serversocket.accept()
        thread.start_new_thread(listener, (clientsocket, clientaddr, gs))
    serversocket.close()


if __name__ == '__main__':
	main(sys.argv)
