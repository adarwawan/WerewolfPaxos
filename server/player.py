class Player:
	def __init__ (self, pid, address, iport, username, role):
		self.id = pid
		self.address = address
		self.iport = iport
		self.username = username
		self.role = role
		self.alive = True
		self.online = True
		# self.kpu_vote = -1
		# self.can_vote = True

	def getID (self):
		return self.id

	def getAddress (self):
		return self.address

	def getIPort (self):
		return self.iport

	def getName (self):
		return self.name

	def getRole (self):
		return self.role

	def getRoleName (self):
		if self.role == 0:
			return "civilian"
		elif self.role == 1:
			return "werewolf"
		else:
			return "invalid role"

	def isAlive (self):
		return self.alive

	def isOnline (self):
		return self.online

	def setAddress (self, address):
		self.address = address

	def setIPort (self, iport):
		self.iport = iport

	def kill (self):
		self.alive = False

	def disconnect (self):
		self.online = False

	def connect (self):
		self.online = True

	# def canVote (self):
	# 	return self.can_vote

	# def getVote (self):
	# 	return self.kpu_vote
		
	# def vote (self, kpu_vote):
	# 	if self.can_vote:
	# 		self.kpu_vote = kpu_vote
	# 		self.can_vote = False

	# def resetVote (self):
	# 	self.can_vote = True
	# 	self.kpu_vote = -1

	# def disableVote (self):
	# 	self.can_vote = False

	def __del__ (self):
		print "Player [ " +  self.name + " ("  + str(self.id) + ") ] exited"
