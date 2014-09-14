#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import serial
import json

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

	# print m.getSummary('2014-W10')
	
	c = Comm()
	c.send('1')

if __name__ == "__main__":
	main()