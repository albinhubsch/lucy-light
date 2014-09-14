#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import serial
import json
import time
import datetime

from Moves import Moves
from Comm import Comm

'''
	Main program
'''
def main():

	# Get the application data
	f = open('.access_token', 'r')
	keydata = json.loads(f.read())

	# Initiate the moves object
	m = Moves(keydata)

	# print m.getRangeSummary('20140801', '20140810')
	
	# Initiate the com link with arduino
	c = Comm()

	# c.send('1')

	while True:
		print('hejs')

		currentDate = datetime.datetime.now().strftime('%Y%m%d')
		oldDate = (datetime.datetime.now() - datetime.timedelta(days=31)).strftime('%Y%m%d')

		print currentDate
		print oldDate

		# Sleep 30s
		time.sleep(30)

if __name__ == "__main__":
	main()