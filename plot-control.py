from __future__ import print_function
from werkzeug.utils import secure_filename
from flask import Flask, render_template, request, session

import serial
import json
import time

app = Flask(__name__)
app.secret_key = "hello"
@app.route('/', methods=['GET', 'POST'])
def index():
	if request.method == 'POST':
		data = request.get_json();
		ser = serial.Serial('/dev/ttyUSB0', 9600)
		time.sleep(2)
		for key, value in data.items():
			pairs = {key:value}
			pairs = json.dumps(pairs)
			print(pairs)
			ser.write(pairs.encode('ascii'))
			time.sleep(.1)
		ser.close()
		return 'file uploaded'

@app.route('/control', methods=['POST'])
def control():
	if request.method == 'POST':
		d = request.values
		print(d)
	return 'OK'

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8000, debug = True)

