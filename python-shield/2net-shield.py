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

		# Load date interval
		currentDate = datetime.datetime.now().strftime('%Y%m%d')
		oldDate = (datetime.datetime.now() - datetime.timedelta(days=30)).strftime('%Y%m%d')

		data = m.getRangeSummary(oldDate, currentDate)
		processor = DataProcessor(data)

		msg = processor.getDuration()

		print msg

		c.send(msg)

		# Sleep program untill next check
		time.sleep(30)



if __name__ == "__main__":
	main()