from __future__ import print_function
from werkzeug.utils import secure_filename
from flask import Flask, render_template, request, session

import math
import subprocess
import os
import sys
import serial
import json
import time
import csv

pairs = ""
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)
"""
with open('static/' + f.filename, 'r') as fp:
	csvreader = csv.reader(fp)
	for row in csvreader:
		pairs = json.dumps(row)	
		print(pairs)
		ser.write(pairs.encode('ascii'))
		time.sleep(.05)
"""
#f = open('data.json')
f = open('ndata.json')
data = json.load(f)
f.close()

for i in data['values']:
	print(i)
	pairs = json.dumps(i)
	ser.write(pairs.encode('ascii'))
	#ser.write(i)
	time.sleep(.5)
"""
pairs = json.dumps(row)	
//print(pairs)
ser.write(pairs.encode('ascii'))
time.sleep(.05)
"""

