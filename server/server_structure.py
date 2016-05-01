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
		self.MAX_VOTE = 2
		self.MIN_PLAYERS = 6
		self.vote_limit = self.MAX_VOTE

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

	def getMaxVote (self):
		return self.MAX_VOTE

	def getMinPlayers (self):
		return self.MIN_PLAYERS

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


	def newPlayer (self, username, iport, uport, address):
		i = 0
		for x in self.players:
			if ( x == "" ):
				self.players[i] = Player(i, address, iport, uport, username, 1 if (i % 3 > 0) else 0)
				self.usernames[i] = username
				self.n_online += 1
				self.game.addPlayer(i, 1 if (i % 3 > 0) else 0)
				return i
			i += 1
		return None

	def joinPlayer (self, username, iport, uport, address):
		pid = self.usernames.index(username)
		self.players[pid].setIPort(iport)
		self.players[pid].setUPort(uport)
		self.players[pid].setAddress(address)
		return pid

	def delPlayer (self, pid):
		self.ready[pid] = 0
		self.players[pid] = ""
		self.usernames[pid] = ""
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
			if self.votes.count(kpu_id) > (self.n_online/2):
				self.kpu_id = kpu_id
				setAllVoteStatus(False)
				return self.kpu_id
			return -1
		else:
			return -2

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

	def reduceVoteLimit (self, reduction):
		self.vote_limit -= reduction
		return self.vote_limit > 0

	def resetVoteLimit (self):
		self.vote_limit = self.MAX_VOTE

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
				# msg = msg.split("\r\n", 1)
				msg = msg.split("\n", 1)
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

		if 'method' in msg:
			if msg['method'] == 'join':
				self.joinResponse(msg, clientsocket, GameServer)

			elif msg['method'] == 'leave':
				self.leaveResponse(msg, clientsocket, GameServer)

			elif msg['method'] == 'ready':
				self.readyResponse(msg, clientsocket, GameServer)
					
			elif msg['method'] == 'client_address':
				self.clientAddressResponse(msg, clientsocket, GameServer)

			elif msg['method'] == 'accepted_proposal':
				self.acceptedProposalResponse(msg, clientsocket, GameServer)

			elif msg['method'] == 'vote_result_werewolf':
				self.voteResultResponse(msg, clientsocket, 0, GameServer)

			elif msg['method'] == 'vote_result_civilian':
				self.voteResultResponse(msg, clientsocket, 1, GameServer)

			else:
				self.sendResponse(clientsocket, json.dumps({"status":"error", "description":"invalid request"}))
		
		elif 'status' in msg:
			if 'description' not in msg:
				if msg['status'] == 'ok':
					print 'ok'
				else:
					print clientsocket + ' ' + clientaddr + ', ' + msg['status'] + ' something went wrong'
			else:
				print clientsocket + ' ' + clientaddr + ', ' + msg['status'] + ' ' + msg['description']

		else:
			self.sendResponse(clientsocket, json.dumps({"status":"error", "description":"invalid request"}))

	def joinResponse (self, msg, clientsocket, GameServer):
		if 'username' not in msg or 'udp_address' not in msg or 'udp_port' not in msg:
			self.sendResponse(clientsocket, json.dumps({"status":"error", "description":"wrong request"}))
		elif self.clientid > -1:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"already joined"}))
		elif GameServer.getGame().isStarted():
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please wait, game is currently running"}))
		else:
			if msg['username'] == "":
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"invalid username"}))
			elif msg['username'] in GameServer.getUsernameList():
				index = GameServer.getUsernameList().index(msg['username'])
				if not GameServer.getPlayerList()[index].isOnline():
					self.clientid = GameServer.joinPlayer(msg['username'], clientsocket, msg['udp_port'], msg['udp_address'])
					self.sendResponse(clientsocket, json.dumps({"status":"ok", "player_id":GameServer.getPlayerList()[index].getID()}))
				else:
					self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"user exists"}))
			elif "" not in GameServer.getUsernameList():
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"full room"}))
			else:
				self.clientid = GameServer.newPlayer(msg['username'], clientsocket, msg['udp_port'], msg['udp_address'])
				self.sendResponse(clientsocket, json.dumps({"status":"ok", "player_id":self.clientid}))

	def leaveResponse (self, msg, clientsocket, GameServer):
		if self.clientid < 0:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please login"}))
		else:
			if not GameServer.getGame().isStarted():
				GameServer.playerQuit(self.clientid)
				self.sendResponse(clientsocket, json.dumps({"status":"ok"}))
			else:
				self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"game has started"}))

	def readyResponse (self, msg, clientsocket, GameServer):
		if self.clientid < 0:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please login"}))
		elif GameServer.getGame().isStarted():
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"game has started"}))
		else:
			GameServer.getReadyList()[self.clientid] = 1
			self.sendResponse(clientsocket, json.dumps({"status":"ok", "description":"waiting for other player to start"}))
			n_ready = 0
			n_players = 0
			for player in GameServer.getPlayerList():
				if player != "":
					n_players += 1
			if n_players >= GameServer.getMinPlayers():
				for r in GameServer.getReadyList():
					if r == 1:
						n_ready += 1
				if n_ready == n_players:
					GameServer.getGame().startGame()
					# different message per role
					for player in GameServer.getPlayerList():
						if player != "":
							self.sendResponse(player.getIPort(), json.dumps({"method":"start", "time":"day", "role":player.getRoleName(), "friend":GameServer.getWolfList() if player.getRole() == 1 else "", "description":"game is started"}))

	def clientAddressResponse (self, msg, clientsocket, GameServer):
		if self.clientid < 0:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please login"}))
		else:
			lst = []
			for player in GameServer.getPlayerList():
				if player != "":
					player_data = []
					if player.isAlive():
						lst.append({"player_id":player.getID(), "is_alive":1, "address":player.getAddress(), "port":player.getUPort(), "username":player.getName()})
					else:
						lst.append({"player_id":player.getID(), "is_alive":0, "address":player.getAddress(), "port":player.getUPort(), "username":player.getName(), "role":player.getRoleName()})
			self.sendResponse(clientsocket, json.dumps({"status":"ok", "clients":lst, "description":"list of clients retrieved"}))

	def acceptedProposalResponse(self, msg, clientsocket, GameServer):
		if self.clientid < 0:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please login"}))
		elif not GameServer.getGame().isStarted():
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"game hasn't started"}))
		else:
			if 'kpu_id' not in msg or 'description' not in msg:
				self.sendResponse(clientsocket, json.dumps({"status":"error", "description":"wrong request"}))
			else:
				if msg['kpu_id'] > -1:
					result = GameServer.voteKPU(self.clientid, msg['kpu_id'])
					if result > -2:
						self.sendResponse(clientsocket, json.dumps({"status":"ok", "description":""}))
						if result > -1:
							GameServer.broadcastAll({"method":"kpu_selected", "kpu_id":result})
					else:
						self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"voting ended"}))
				else:
					self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"invalid id"}))

	def voteResultResponse (self, msg, clientsocket, mode, GameServer):
		if self.clientid < 0:
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"please login"}))
		elif not GameServer.getGame().isStarted():
			self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"game hasn't started"}))
		else:
			if 'vote_status' not in msg or 'vote_result' not in msg:
				self.sendResponse(clientsocket, json.dumps({"status":"error", "description":"wrong request"}))
			else:
				if self.clientid == GameServer.getKPUID() and GameServer.getGame().getTime() == mode:
					if msg['vote_status'] == 1:
						vote_result = -1
						nmax_vote = 0
						for votes in msg['vote_result']:
							if nmax_vote < votes[1]:
								nmax_vote = votes[1]
								vote_result = votes[0]
							elif nmax_vote == votes[1]:
								vote_result = -1

						if vote_result == msg['player_killed']:
							voteKill(msg['player_killed'])
							self.sendResponse(clientsocket, json.dumps({"status":"ok", "description":""}))
							GameServer.resetVoteLimit()
							win = GameServer.getGame().checkWin()
							if win == -1:
								GameServer.getGame().advanceTime()
								GameServer.broadcastAll({"method":"change_phase", "time":GameServer.getGame().getTimeName(), "days":GameServer.getGame().getTurn(), "description":""})
							else:
								GameServer.getGame().stopGame()
								GameServer.broadcastAll({"method":"game_over", "winner": "civilian" if win == 0 else "werewolf", "days":GameServer.getGame().getTurn(), "description":""})
						else:
							self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"wrong vote result"}))
					elif msg['vote_status'] == -1:
						if not GameServer.reduceVoteLimit(mode):
							GameServer.getGame().advanceTime()
							GameServer.broadcastAll({"method":"change_phase", "time":GameServer.getGame().getTimeName(), "days":GameServer.getGame().getTurn(), "description":""})
							GameServer.resetVoteLimit()
					else:
						self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"invalid status"}))
				else:
					self.sendResponse(clientsocket, json.dumps({"status":"fail", "description":"invalid request"}))
	# def objectToJSON (self, request, GameServer):
	# 	class message(object):
	# 		def __init__(self):
	# 			self.type = "response"
	# 			self.object = "undefined"
	# 			self.data = []

	# 	msgobj = message()

	# 	if (request == "rooms"):
	# 		msgobj.object = "rooms"
	# 		for room in GameServer.getRoomList():
	# 			if ( room != "" ):
	# 				msgobj.data.append({"id": room[0].getID(), "name":room[0].getName()})

	# 	elif (request == "players"):
	# 		msgobj.object = "players"
	# 		for player in GameServer.getRoomList()[GameServer.getPlayerList()[self.clientid].getRoomID()][1].getPlayerList():
	# 			if GameServer.getPlayerByPID(player) != "":
	# 				msgobj.data.append({"id":player, "name": GameServer.getPlayerByPID(player).getName(), "char":GameServer.getPlayerByPID(player).getChar()})

	# 	elif (request == "board"):
	# 		msgobj.object = "board"
	# 		for b in GameServer.getRoomList()[GameServer.getPlayerList()[self.clientid].getRoomID()][1].getBoard():
	# 			msgobj.data.append(b)

	# 	msg = json.dumps(msgobj.__dict__)
	# 	return msg

	def sendResponse (self, clientsocket, msg):
		print msg
		# clientsocket.send(msg +"\r\n")
		clientsocket.send(msg +"\n")

	def __del__ (self):
		if self.GameServer.getGame().isStarted():
			self.GameServer.disconnectPlayer(self.clientid)
		else:
			self.GameServer.playerQuit(self.clientid)
		print "Message Server destroyed"
