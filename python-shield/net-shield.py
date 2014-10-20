#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import serial
import json
import time
import datetime

from Moves import Moves
from Comm import Comm
from DataProcessor import DataProcessor

'''
	Main program
'''
def main():

	# Get the application data
	f = open('.access_token', 'r')
	keydata = json.loads(f.read())

	# Initiate the moves object
	m = Moves(keydata)
	
	# Initiate the com link with arduino
	c = Comm()

	# c.send('bootup')

	# time.sleep(5);

	# Run program loop
	while True:

		# Load date interval
		currentDate = datetime.datetime.now().strftime('%Y%m%d')
		oldDate = (datetime.datetime.now() - datetime.timedelta(days=30)).strftime('%Y%m%d')

		data = m.getRangeSummary(oldDate, currentDate)
		processor = DataProcessor(data)

		msg = processor.newDataProcessor()

		# leds = processor.generateDayColor()
		state = 0

		# inp = raw_input('input something')
		# print('Typed' + inp)

		if processor.checkMoving():
			state = 1

		# msg = ''

		# for l in leds:
		# 	msg = msg + l['activity'] + ':' + str(l['amount']) + ','

		# msg = msg + 'state:' + state

		# print leds
		msg = str(1) + ',' + msg

		print(msg)

		c.send(msg)

		# Sleep program untill next check
		time.sleep(30)

if __name__ == "__main__":
	main()