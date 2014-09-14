#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests

'''
	Moves class
'''
class Moves():

	'''
		Class constructor
	'''
	def __init__(self, keys):
		self.keys = keys

		self.api_url = 'https://api.moves-app.com/api/1.1'
		self.token = '?access_token=' + self.keys['access_token']

	'''
		Return user information
	'''
	def getProfile(self):
		root = '/user/profile'
		return requests.get(self.api_url + root + self.token).json()

	'''
		Return summary given a date type

		examples
			day - yyyyMMdd
			week - 2013-W09
			month - yyyyMM
	'''
	def getSummary(self, date):
		root = '/user/summary/daily/'
		return requests.get(self.api_url + root + date + self.token).json()

	'''
		Return summary given a date range

		examples
			from - yyyyMMdd
			to - yyyyMMdd
	'''
	def getRangeSummary(self, fromdate, todate):
		root = '/user/summary/daily/'
		return requests.get(self.api_url + root + '?from='+ fromdate + '?to=' + todate + self.token).json()