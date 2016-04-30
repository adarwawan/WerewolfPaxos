from socket import *
import struct
import thread
import json

from game import *

class GameServer:

	def __init__ (self, max_players):
		self.players = [""] * max_players # maximum players online
		self.usernames = [""] * max_players # players' name
		self.ready = [0 for x in range(max_players)] # players' status
		self.votes = [-1 for x in range(max_players)] # players' kpu vote
		self.can_vote = [True for x in range(max_players)]
		self.game = Game()
		self.n_online = 0
		self.kpu_id = -1

class MessageServer:
	client = 0

	def __init__ (self, clientsocket, clientaddr, GameServer):
		self.clientid = -1
		print "Accepted connection from ", tuple(clientaddr)

		self.GameServer = GameServer
		onLoop = True

		while onLoop:			
			try:
				# size = struct.unpack("i", clientsocket.recv(struct.calcsize("i")))
				# data = ""
				# while len(data) < size[0]:
				# 	msg = clientsocket.recv(size[0] - len(data))
					# if not msg:
					# 	return None
					# data += msg

				msg = clientsocket.recv(4096)
				msg = msg.split("\r\n", 1)
				data = msg[0]
				if not data:
					break
				else:
					print "Received: " + data
					self.interpreter(data, clientsocket, clientaddr, GameServer)
			except error:
				GameServer.delPlayer(self.clientid)
				onLoop = False

		clientsocket.close()


	def interpreter (self, message, clientsocket, clientaddr, GameServer):
		msg = json.loads(message)

		if msg['method'] == 'join':
			self.sendResponse(clientsocket, json.dumps({"status":"ok", "player_id":"id"}))
				
		elif msg['method'] == 'leave':
			self.sendResponse(clientsocket, json.dumps({"status":"left"}))

		elif msg['method'] == 'ready':
			self.sendResponse(clientsocket, json.dumps({"status":"ok", "description":"waiting for other player to start"}))

		elif msg['method'] == 'client_address':
			self.sendResponse({"status":"ok", "clients":"lst", "description":"list of clients retrieved"})

		elif msg['method'] == 'prepare_proposal':
			self.sendResponse({"status":"ok", "description":"prepared"})

		elif msg['method'] == 'vote_result_werewolf':
			self.sendResponse({"status":"ok", "description":"werewolf killed"})

		elif msg['method'] == 'vote_result_civilian':
			self.sendResponse({"status":"ok", "description":"civilian killed"})

	def sendResponse (self, clientsocket, msg):
		print msg
		clientsocket.send(msg +"\r\n")

	def __del__ (self):
		self.GameServer.delPlayer(self.clientid)
		print "Message Server destroyed"
