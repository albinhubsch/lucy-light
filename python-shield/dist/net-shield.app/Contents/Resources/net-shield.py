#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import serial
import json
import time
import datetime
import requests

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

	loops = 0

	# Run program loop
	while True:

		state = 0

		if loops is 0:
			# Load date interval
			currentDate = datetime.datetime.now().strftime('%Y%m%d')
			oldDate = (datetime.datetime.now() - datetime.timedelta(days=30)).strftime('%Y%m%d')

			data = m.getRangeSummary(oldDate, currentDate)
			processor = DataProcessor(data)

			raw = processor.newDataProcessor()

			if processor.checkMoving():
				state = 1


		# Check realtime
		realtime = datetime.datetime.strptime(requests.get('http://studier.albinhubsch.se/lucy-light').text, "%Y-%m-%d %H:%M:%S")
		now = datetime.datetime.now()

		if realtime + datetime.timedelta(minutes=10) > now:
			state = 1


		msg = str(state) + ',' + raw

		c.send(msg)

		if loops < 10:
			loops += 1
		else:
			loops = 0

		# Sleep program untill next check
		time.sleep(6)



if __name__ == "__main__":
	main()