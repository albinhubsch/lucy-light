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
		summary = self.data[-3]['summary']

		# Prep
		tot = 0
		segments = []

		# 
		for d in summary:
			tot = tot + float(d['duration'])
			segments.append({'activity':d['activity'], 'duration': float(d['duration'])})

		print tot
		print segments

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
		Generate color
	'''
	def generateColor(self, total, segments):
		# cycling #00cdec
		# walking #00d55a
		# running #f660f4
		pass

	'''
		Get message to send to Arduino
	'''
	def getMessageToSend(self):
		pass