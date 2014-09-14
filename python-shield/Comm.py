#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial

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

	'''
		Send
	'''
	def send(self, data):
		ser = serial.Serial(self.con, self.speed)
		ser.write(data)