#include <ArduinoJson.h>
#define XSTP 13
#define XDIR 12
#define YSTP 9
#define YDIR 8
#define TSTP 11
#define TDIR 10

#define SCRL 4  //Scroll driver
#define SSTP 3  //Scroll sensor

#define XLIM 5
#define YLIM 7
#define TLIM 6

#define driveDelay 400
#define tapDelay 500 
#define testDelay 1500
#define tapDistance 10

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }

#define dir(d) ((d) == (-1) ? (0) : (1)) //CHECK THIS FOR CONVERSION

#define POS   +1
#define NEG   -1

#define DOWN 0	
#define UP 	1	

StaticJsonDocument<100> doc;

int aX;
int aY;

int i;

void stepperX(int dir) {
  if (dir == POS)
    digitalWrite(XDIR, HIGH);
  else
    digitalWrite(XDIR, LOW);

  digitalWrite(XSTP, HIGH);
  delayMicroseconds(driveDelay);
  digitalWrite(XSTP, LOW);
  delayMicroseconds(driveDelay);
}

void stepperY(int dir) {
  if (dir == POS)
    digitalWrite(YDIR, HIGH);
  else
    digitalWrite(YDIR, LOW);

  digitalWrite(YSTP, HIGH);
  delayMicroseconds(driveDelay);
  digitalWrite(YSTP, LOW);
  delayMicroseconds(driveDelay);
}

void plotHome() {
  while (digitalRead(XLIM) == false) {
    stepperX(NEG);
  }
  while (digitalRead(YLIM) == false) {
    stepperY(NEG);
  }
}

void tap() {
  digitalWrite(TDIR, DOWN);

  for (int x = 0; x < tapDistance; x++) {
    digitalWrite(TSTP, HIGH);
    delayMicroseconds(tapDelay);
    digitalWrite(TSTP, LOW);
    delayMicroseconds(tapDelay);
  }
 	digitalWrite(TDIR, UP);

  for (int x = 0; x < tapDistance; x++) {
    digitalWrite(TSTP, HIGH);
    delayMicroseconds(tapDelay);
    digitalWrite(TSTP, LOW);
    delayMicroseconds(tapDelay);
  }
//
//  tapHome();
}

void tapHome() {
  digitalWrite(TDIR, UP);
  while (digitalRead(TLIM) == false) {
    digitalWrite(TSTP, HIGH);
    delayMicroseconds(tapDelay);
    digitalWrite(TSTP, LOW);
    delayMicroseconds(tapDelay);
  }
}

void loadPen() {
	tapHome();
	digitalWrite(TDIR, DOWN);

  for (int x = 0; x < tapDistance; x++) {
    digitalWrite(TSTP, HIGH);
    delayMicroseconds(tapDelay);
    digitalWrite(TSTP, LOW);
    delayMicroseconds(tapDelay);
  }
}


void plotDelta(int dx, int dy)
{
  int error = 0;
  int d1 = dx;
  int d2 = dy;
  int limit = abs(dx);

  int sx = POS;
  int sy = POS;

  if (dx <= 0) sx = NEG;
  if (dy <= 0) sy = NEG;

  if (abs(dx) < abs(dy)) {
    limit = abs(dy);
    d1 = dy;
    d2 = dx;
  }

  for (int x = 0; x < limit; x++) {
    if (abs(dx) >= abs(dy)) {
      stepperX(sx);
      aX += sx;
    }
    else {
      stepperY(sy);
      aY += sy;
    }
    error = abs(error + abs(d2));
    if ((2 * error) >= abs(d1)) {
      error = error - abs(d1);
      if (abs(dx) >= abs(dy)) {
        stepperY(sy);
        aY += sy;
      }
      else {
        stepperX(sx);
        aX += sx;
      }
    }
  }
}

void plotCord(int x, int y) {
  x = (x - aX);
  y = (y - aY);
  plotDelta(x, y);
}



void setup() {
  Serial.begin(9600);
  pinMode(XSTP, OUTPUT);
  pinMode(XDIR, OUTPUT);
  pinMode(YSTP, OUTPUT);
  pinMode(YDIR, OUTPUT);
  pinMode(TSTP, OUTPUT);
  pinMode(TDIR, OUTPUT);
  pinMode(SCRL, OUTPUT);

  pinMode(XLIM, INPUT);
  pinMode(YLIM, INPUT);
  pinMode(TLIM, INPUT);

  digitalWrite(SCRL, LOW); //Turn off scrolling motor
//	loadPen();
	tapHome();
//	plotHome();
 	plotCord(500, 500);
	tap();
 	plotCord(1000, 1000);
	tap();
 	plotCord(1500, 1500);
	tap();
 	plotCord(2000, 2000);
	//tapHome();
	while(1);
}

void loop() {

	if (Serial.available()) {
			DeserializationError error = deserializeJson(doc, Serial);
			if (error) 
				Serial.print("error");

			//plotCord(doc["xy"][0], doc["xy"][1]);
			plotCord(doc["c" + String(i)][0], doc["c" + String(i)][1]);
			//tap();
			i++;
	}
}


