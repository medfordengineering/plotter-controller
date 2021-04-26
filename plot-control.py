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

app = Flask(__name__)
app.secret_key = "hello"

@app.route('/', methods=['GET', 'POST'])
def index():
	if request.method == 'POST':
	ser = serial.Serial('/dev/ttyUSB0', 9600)
	time.sleep(2)
		d = request.get_json();
		d = json.loads(d)
		x = zip(d['x'], d['y'])
		print('s')
		print(next(x)[0])
		print(next(x))
		
#print(tuple(x))
#for i in d['x']:
#print(i )
#dicts = {
#"xy": [d['x'][i-1], d['y'][i-1]]
#}
		#pairs = json.dumps(dicts)
			#ser.write(pairs)
#time.sleep(.05)
#print(dicts);
		"""
		f = request.files['file']
		if f.filename !='':
			f.save("/home/pi/Projects/plotter/plotter-controller/static/" + f.filename)

		pairs = ""
		ser = serial.Serial('/dev/ttyUSB0', 9600)
		time.sleep(2)
		with open('static/' + f.filename, 'r') as fp:
			csvreader = csv.reader(fp)
			for row in csvreader:
				pairs = json.dumps(row)	
				print(pairs)
				ser.write(pairs.encode('ascii'))
				time.sleep(.05)
		"""
	return 'file uploaded'
if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8000, debug = True)
