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
		f = request.files['file']
		if f.filename !='':
			f.save("/home/pi/Projects/plotter/static/" + f.filename)
		return 'file uploaded'

		pairs = ""
		ser = serial.Serial('/dev/ttyUSB0', 9600)
		time.sleep(2)
		with open(f.filename, 'r') as fp:
			csvreader = csv.reader(fp)
			for row in csvreader:
				pairs = json.dumps(row)	
				ser.write(pairs.encode('ascii'))
				time.sleep(.05)

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8000, debug = True)
