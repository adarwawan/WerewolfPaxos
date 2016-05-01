from player import *

class Game:
	def __init__ (self):
		self.turn = 0
		self.time = 1
		self.winner = -1
		self.players = []
		self.isStart = False
		self.n_wolf = 0
		self.n_civ = 0

	def checkWin(self):
		self.n_wolf = 0
		self.n_civ = 0
		if self.n_wolf == 0:
			return 0
		elif self.n_wolf >= self.n_civ:
			return 1
		else:
			return -1

	def isStarted (self):
		return self.isStart

	def getPlayerCount (self):
		return len(self.players)

	def getTurn (self):
		return self.turn

	def getTime (self):
		return self.time

	def getTimeName (self):
		if self.time == 0:
			return "night"
		else:
			return "day"

	def advanceTime (self):
		self.time = (self.time + 1) % 2
		if self.time == 0:
			self.turn += 1

	def getPlayerList (self):
		return self.players

	def addPlayer (self, pid, role):
		self.players.append(pid)
		if role == 0:
			self.n_civ += 1
		elif role == 1:
			self.n_wolf += 1

	def killWolf ():
		self.n_wolf -= 1

	def killCiv ():
		self.n_civ -= 1

	def delPlayer (self, pid):
		self.players.remove(pid)

	def startGame (self):
		self.isStart = True

	def stopGame (self):
		self.isStart = False

	def __del__ (self):
		print "Game from Room ( " + str(self.room) + " ) stopped"