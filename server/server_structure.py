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

	def getPlayerList (self):
		return self.players

	def getUsernameList (self):
		return self.usernames

	def getReadyList (self):
		return self.ready

	def getGame (self):
		return self.game

	def getPlayerByPID (self, pid):
		return self.players[pid]

	def getKPUID (self):
		return self.kpu_id

	def getWolfList (self):
		lst = []
		for player in self.players:
			if player != "" and player.getRole() == 1:
				lst.append(player.getName())
		return lst

	# def broadcastByRoom (self, rid, message):
	# 	msg = json.dumps(message,separators=(',',':'))
	# 	for player in self.players:
	# 		if ( ( player != "" ) and ( player.getRoomID() == rid ) ):
	# 			player.getIPort().send(msg + "\r\n")

	def broadcastAll (self, message):
		msg = json.dumps(message,separators=(',',':'))
		for player in self.players:
			if player != "":
				player.getIPort().send(msg + "\r\n")

	def broadcastByPID (self, pid, message):
		msg = json.dumps(message,separators=(',',':'))
		player = self.players[pid]
		if player != "":
			player.getIPort().send(msg + "\r\n")


	def newPlayer (self, username, iport, address):
		i = 0
		for x in self.players:
			if ( x == "" ):
				self.players[i] = Player(i, address, iport, username, 1 if (i % 3 > 0) else 0)
				self.username[i] = username
				self.n_online += 1
				self.game.addPlayer(i, 1 if (i % 3 > 0) else 0)
				return i
			i += 1
		return None

	def delPlayer (self, pid):
		self.players[pid] = ""
		self.username[pid] = ""
		self.n_online -= 1

	def disconnectPlayer (self, pid):
		self.players[pid].disconnect()
		self.n_online -= 1

	def playerQuit (self, pid):
		self.delPlayer(pid)
		print "Player (" + str(pid) + ") quit from game"

	def voteKPU (self, pid, kpu_id):
		if self.can_vote[pid]:
			self.votes[pid] = kpu_id
			if self.votes.count(kpu_id) > (n_online/2):
				self.kpu_id = kpu_id
				setAllVoteStatus(False)
			return True
		else:
			return False

	def resetVotes (self):
		for vote in self.votes:
			vote = -1

	def setAllVoteStatus (self, status):
		for vote in self.can_vote:
			vote = status

	def voteKill (self, kpu_id, pid):
		if self.kpu_id == kpu_id:
			self.players[pid].kill()
			resetVotes()
			setAllVoteStatus(True)

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
			if msg['username'] == "":
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"invalid username"}))
			if msg['username'] in GameServer.getUsernameList():
				index = GameServer.getUsernameList().index(msg['username'])
				if not GameServer.getPlayerList()[index].isOnline():
					self.sendResponse(clientsocket, json.dumps({"status":"ok", "player_id":GameServer.getPlayerList()[index].getID()}))
				else:
					self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"user exists"}))
			elif GameServer.getGame().isStarted():
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please wait, game is currently running"}))
			elif "" not in self.usernames:
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"full room"}))
			else:
				self.clientid = GameServer.newPlayer(msg['username'], clientsocket, clientaddr)
				self.sendResponse(clientsocket, json.dumps({"status":"ok", "player_id":self.clientid}))

		elif msg['method'] == 'leave':
			if not GameServer.getGame().isStarted():
				GameServer.playerQuit(self.clientid)
				self.sendResponse(clientsocket, json.dumps({"status":"ok"}))
			else:
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"game has started"}))

		elif msg['method'] == 'ready':
			GameServer.getReadyList()[self.clientid] = 1
			self.sendResponse(clientsocket, json.dumps({"status":"ok", "description":"waiting for other player to start"}))
			n_ready = 0
			n_players = 0
			for player in GameServer.getPlayerList():
				if player != "":
					n_players += 1
			for r in GameServer.getReadyList():
				if r == 1:
					n_ready += 1
			if n_ready == n_players:
				for player in GameServer.getPlayerList():
					if player != "":
						self.sendResponse({"method":"start", "time":"day", "role":player.getRoleName(), "friend":GameServer.getWolfList() if player.getRole() == 1 else "", "description":"game is started"})
				
		elif msg['method'] == 'client_address':
			lst = []
			for player in GameServer.getPlayerList():
				if player != "":
					player_data = []
					lst.append({"player_id":player.getID(), "is_alive":player.isAlive(), "address":player.getAddress(), "port":player.getIPort(), "username":player.getName()})
			self.sendResponse({"status":"ok", "clients":lst, "description":"list of clients retrieved"})

		elif msg['method'] == 'prepare_proposal':
			if msg['kpu_id'] > -1:
				if GameServer.voteKPU(clientid, msg['kpu_id']):
					self.sendResponse({"status":"ok", "description":""})
				else:
					self.sendResponse({"status":"fail", "description":"voting ended"})
			else:
				self.sendResponse({"status":"fail", "description":"invalid id"})

		elif msg['method'] == 'vote_result_werewolf':
			if clientid == GameServer.getKPUID():
				if msg['vote_status'] == 1:
					voteKill(msg['player_killed'])
					self.sendResponse({"status":"ok", "description":""})
					win = GameServer.getGame().checkWin()
					if win == -1:
						GameServer.getGame().advanceTime()
						self.sendResponse({"method":"change_phase", "time":GameServer.getGame().getTimeName(), "days":GameServer.getGame().getTurn(), "description":""})
					else:
						self.sendResponse({"method":"game_over", "winner": "civilian" if win == 0 else "werewolf", "days":GameServer.getGame().getTurn(), "description":""})
				elif msg['vote_status'] == -1:
					self.sendResponse({"status":"ok", "description":""})
				else:
					self.sendResponse({"status":"fail", "description":"invalid status"})
			else:
				self.sendResponse({"status":"fail", "description":"invalid kpu"})

		elif msg['method'] == 'vote_result_civilian':
			if clientid == GameServer.getKPUID():
				if msg['vote_status'] == 1:
					voteKill(msg['player_killed'])
					self.sendResponse({"status":"ok", "description":""})
					win = GameServer.getGame().checkWin()
					if win == -1:
						GameServer.getGame().advanceTime()
						self.sendResponse({"method":"change_phase", "time":GameServer.getGame().getTimeName(), "days":GameServer.getGame().getTurn(), "description":""})
					else:
						self.sendResponse({"method":"game_over", "winner": "civilian" if win == 0 else "werewolf", "days":GameServer.getGame().getTurn(), "description":""})
				elif msg['vote_status'] == -1:
					self.sendResponse({"status":"ok", "description":""})
				else:
					self.sendResponse({"status":"fail", "description":"invalid status"})
			else:
				self.sendResponse({"status":"fail", "description":"invalid kpu"})

	def objectToJSON (self, request, GameServer):
		class message(object):
			def __init__(self):
				self.type = "response"
				self.object = "undefined"
				self.data = []

		msgobj = message()

		if (request == "rooms"):
			msgobj.object = "rooms"
			for room in GameServer.getRoomList():
				if ( room != "" ):
					msgobj.data.append({"id": room[0].getID(), "name":room[0].getName()})

		elif (request == "players"):
			msgobj.object = "players"
			for player in GameServer.getRoomList()[GameServer.getPlayerList()[self.clientid].getRoomID()][1].getPlayerList():
				if GameServer.getPlayerByPID(player) != "":
					msgobj.data.append({"id":player, "name": GameServer.getPlayerByPID(player).getName(), "char":GameServer.getPlayerByPID(player).getChar()})

		elif (request == "board"):
			msgobj.object = "board"
			for b in GameServer.getRoomList()[GameServer.getPlayerList()[self.clientid].getRoomID()][1].getBoard():
				msgobj.data.append(b)

		msg = json.dumps(msgobj.__dict__)
		return msg

	def sendResponse (self, clientsocket, msg):
		print msg
		clientsocket.send(msg +"\r\n")

	def __del__ (self):
		if self.GameServer.getGame().isStarted():
			self.GameServer.disconnectPlayer(self.clientid)
		else:
			self.GameServer.playerQuit(self.clientid)
		print "Message Server destroyed"
