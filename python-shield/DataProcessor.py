#!/usr/bin/env python
# -*- coding: utf-8 -*-

import datetime

SHORTNAMES = {'walking': 'w', 'cycling': 'c', 'running': 'r'}
NUMBER_OF_LEDS = 60

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
			if d['activity'] is not 'transport':
				tot = tot + float(d['duration'])
				segments.append({'activity':SHORTNAMES[d['activity']], 'duration': float(d['duration'])})

		return self.generateLEDS(tot, segments)

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
	def generateLEDS(self, total, segments):
		leds = []
		for s in segments:
			leds.append({'activity': s['activity'], 'amount': (s['duration']/total) * NUMBER_OF_LEDS})

		if leds:
			return leds
		else:
			return [{'activity': '-', 'amount': NUMBER_OF_LEDS}]

	'''
		Get message to send to Arduino
	'''
	def getMessageToSend(self):
		pass