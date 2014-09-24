#!/usr/bin/env python
# -*- coding: utf-8 -*-

import datetime

'''
	DataProcessor Class
'''
class DataProcessor():

	'''
		Class Constructor
	'''
	def __init__(self, data):
		self.data = data

	'''
		Check if currently moving
	'''
	def checkMoving(self):
		lastUpdate = self.data[-1]['lastUpdate'].split('T')[0][0:8] + self.data[-1]['lastUpdate'].split('T')[1][0:6]
		frmat = '%Y%m%d%H%M%S'
		lastUpdate = datetime.datetime.strptime(lastUpdate, frmat)
		now = datetime.datetime.now()

		if lastUpdate + datetime.timedelta(hours=1) > now:
			return True
		else:
			return False

	'''
		Generate day color
	'''
	def generateDayColor(self):
		print self.data[-1]

	'''
		Generate week color
	'''
	def generateWeekColor(self):
		pass

	'''
		Generate month color
	'''
	def generateMonthColor(self):
		pass

	'''
		Get message to send to Arduino
	'''
	def getMessageToSend(self):
		pass