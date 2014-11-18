#!/usr/bin/env python
# -*- coding: utf-8 -*-

import datetime

SHORTNAMES = {'walking': 0, 'cycling': 1, 'running': 2}
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
		# print self.data

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


	'''
		New data processor
	'''
	def newDataProcessor(self):

		# Prep
		tot = 0
		avg = {'walking': {'count': 0, 'calc': 0.0}, 'running': {'count': 0, 'calc': 0.0}, 'transport': {'count': 0, 'calc': 0.0}}

		print self.data

		for row in self.data:
			for summary in row['summary']:
				avg[str(summary['activity'])]['count'] += 1
				avg[str(summary['activity'])]['calc'] += summary['duration']

		for i in avg:
			try:
				avg[i]['calc'] = avg[i]['calc']/avg[i]['count']
			except Exception, e:
				avg[i]['calc'] = 0.0

		biggest = {'duration': 0.0}
		for i in self.data[-2]['summary']:
			if i['duration'] > biggest['duration']:
				biggest = i

		print('val: ' + str(biggest['duration']))
		print('avg: ' + str(avg[biggest['activity']]['calc']))

		msg = str(SHORTNAMES[biggest['activity']]) + ',' + str(int((biggest['duration']/avg[biggest['activity']]['calc'])*100))

		# f = 49
		# x = "%.2f" % f

		return msg

	'''
		Get yesterday type, duration and pulse
	'''
	def getDuration(self):
		yesterday = self.data[-2]
		total_duration = 0
		biggest_num = 0
		biggest_title = None
		steps = 0

		# print yesterday

		for i in yesterday['summary']:
			if i['group'] in SHORTNAMES:
				total_duration += i['duration']
				if i['duration'] > biggest_num:
					biggest_num = i['duration']
					biggest_title = i['group']
					try:
						steps = i['steps']
					except Exception, e:
						steps = 0

		freq = 0
		if steps is not 0:
			freq = int((steps/(total_duration/60))/3)

		data_str = str(SHORTNAMES[biggest_title]) + ',' + str(int(total_duration)) + ',' + str(freq) + ',' + str(yesterday['date'])

		return data_str

