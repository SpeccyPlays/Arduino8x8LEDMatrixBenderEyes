/*
  LED bender eyes
uses 2 8x8 led matrixes controlled by max7219s
  created 9-10-2021 (2021-10-8)
  by Benajmin Gibbs
modified 9-10-2021
v2.0
updated but the way ive coded eye movement means i cant show another expression
v2.1
updating eye movement to fix above
v3.0
completely rewriting to have the outside eye in arrays rather than previous bitshifting
eyes will be independant
*/
#include "LedControl.h"

int loadPin = 9;          // cs pin
int clockPin = 8;          // clk
int dataPin = 10;           // din pin
LedControl lc = LedControl(10,8,9,2);
bool firstRun = true;
// bitmaps
const byte outsideEyeNormal[] = {
  B00111100, B01000010, B10000001, B10000001, B10000001, B10000001, B01000010, B00111100
};
const byte outsideEyeAngry[] = {
  B00111100, B01000010, B10000001, B10000001, B10000001, B10000010, B01000100, B00111000
};
const byte outsideEyeQuizzical[] = {
  B00111100, B01000010, B10000010, B10000010, B10000100, B10000100, B01000100, B00111000
};
const byte outsideEyeNarrow[] = {
  B00011000, B00100100, B00100100, B00100100, B00100100, B00100100, B00100100, B00011000
};
const byte blinking[] ={
  B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000
};
const byte outsideEyeWide[] = {
  B01111110, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B01111110
};

int pause = 1000;
int winkBlinkPause = 200;
void setup() {
lc.shutdown(0,false);
lc.setIntensity(0, 2);
lc.shutdown(1,false);
lc.setIntensity(1, 2);
randomSeed(analogRead(0));
}
void loop() {
outlineNormal();
delay(pause);
int randomNumber = random(1, 13);
	switch(randomNumber){
	case 1:
	doubleBlink();
	break;
	case 2:
	shifty();
	break;
	case 3:
	outlineNarrow();
	break;
	case 4:
	outlineAngry();
	break;
	case 5:
	eyesLeft(pause);
	break;
	case 6:
	eyesRight(pause);
	break;
	case 7:
	eyesUp();
	break;
	case 8:
	eyesDown;
	break;
	case 9:
	blink();
	break;
	case 10:
	wink();
	break;
	case 11:
	outlineWide();
	break;
	case 12:
	quizzical();
	break;
	}
}

void shifty(){
outlineNarrow();
for (int i = 0; i <= 2; i++){
		eyesLeft(200);
		eyesCenter();
		eyesRight(200);
		eyesCenter();
	}
}

void outlineNormal(){
	for (int board = 0; board <= 1; board++){
		for (int i = 0; i <= 7; i++){
		lc.setRow(board, i, outsideEyeNormal[i]);
		}
	}
eyesCenter();
delay(pause);
}

void outlineWide(){
	for (int board = 0; board <= 1; board++){
		for (int i = 0; i <= 7; i++){
		lc.setRow(board, i, outsideEyeWide[i]);
		}
	}
eyesCenter();
delay(pause);
}
		
void outlineAngry(){
	for (int i = 0; i <= 7; i++){
		lc.setRow(0, i, outsideEyeAngry[i]);
	}
	int r = 7;
	for (int i = 0; i <= 7; i++){
		lc.setRow(1, i, outsideEyeAngry[r]);
		r--;
	}
eyesCenter();
delay(pause);
}

void outlineNarrow(){
	for (int board = 0; board <= 1; board++){
		for (int i = 0; i <= 7; i++){
			lc.setRow(board, i, outsideEyeNarrow[i]);
		}
	eyesCenter();
	}
delay(pause);
}

void blink(){
	for (int board = 0; board <= 1; board++){
		for (int i = 0; i <= 7; i++){
			lc.setRow(board, i, blinking[i]);
			}
	}
delay(winkBlinkPause);
}

void doubleBlink(){
blink();
outlineNormal();
blink();
}

void wink(){
	for (int i = 0; i <= 7; i++){
		lc.setRow(1, i, blinking[i]);
	}
delay(winkBlinkPause);
}

void quizzical(){
	for (int i = 0; i <= 7; i++){
		lc.setRow(0, i, outsideEyeQuizzical[i]);
		lc.setRow(1, i, outsideEyeNormal[i]);
	}
eyesCenter();
delay(pause);
}

void eyesLeft(int eyePause){
eyesCenter();
for (int board = 0; board <= 1; board++){
lc.setLed(board, 4, 3, false);
lc.setLed(board, 4, 4, false);
lc.setLed(board, 3, 3, true);
lc.setLed(board, 3, 4, true);
lc.setLed(board, 2, 3, true);
lc.setLed(board, 2, 4, true);
	}
delay(eyePause);
}

void eyesRight(int eyePause){
eyesCenter();
for (int board = 0; board <= 1; board++){
lc.setLed(board, 3, 3, false);
lc.setLed(board, 3, 4, false);
lc.setLed(board, 4, 3, true);
lc.setLed(board, 4, 4, true);		
lc.setLed(board, 5, 3, true);
lc.setLed(board, 5, 4, true);
	}
delay(eyePause);
}
				
void eyesCenter(){
	for (int board = 0; board <= 1; board++){
		lc.setLed(board, 5, 3, false);
		lc.setLed(board, 5, 4, false);
		lc.setLed(board, 4, 3, true);
		lc.setLed(board, 4, 4, true);
		lc.setLed(board, 3, 3, true);
		lc.setLed(board, 3, 4, true);
		lc.setLed(board, 2, 3, false);
		lc.setLed(board, 2, 4, false);
	}
}

void eyesDown(){
eyesCenter();
for (int board = 0; board <= 1; board++){
		lc.setLed(board, 3, 4, false);
		lc.setLed(board, 4, 4, false);
		lc.setLed(board, 3, 3, true);
		lc.setLed(board, 4, 3, true);
		lc.setLed(board, 3, 2, true);
		lc.setLed(board, 4, 2, true);
	}
delay(pause);
}
void eyesUp(){
eyesCenter();
for (int board = 0; board <= 1; board++){
		lc.setLed(board, 3, 3, false);
		lc.setLed(board, 4, 3, false);
		lc.setLed(board, 3, 4, true);
		lc.setLed(board, 4, 4, true);
		lc.setLed(board, 3, 5, true);
		lc.setLed(board, 4, 5, true);
	}
delay(pause);
}