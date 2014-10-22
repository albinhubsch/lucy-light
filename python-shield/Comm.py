#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import json

'''
	Class Comm
	Use for communication with the arduino
'''
class Comm():
	
	'''
		Constructor
	'''
	def __init__(self):
		self.speed = 9600
		self.con = '/dev/tty.usbmodem1411'
		self.ser = serial.Serial(self.con, self.speed)

	'''
		Send
	'''
	def send(self, data):
		print 'Sending message: ',data
		self.ser.write(data+'\n')

	def read(self):
		self.ser.readline()