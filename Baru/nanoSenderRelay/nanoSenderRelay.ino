unsigned long currentMillis;

int xLValue;
int yLValue;
int xRValue;
int yRValue;
char* joystickLeftValue;
char* joystickRightValue;
char* joystickLeftButtValue;
char* joystickRightButtValue;
char* butt1Value;
char* butt2Value;
char* butt3Value;

// System D: Serial and debugging
	unsigned long debugPreviousMillis = 0;
	unsigned long debugTimeElapsed;
	const int debugInterval = 1000;

	const int startBlinkDelay = 150;

	bool lampState = HIGH;
	// bool lampButtonState;
	// bool lastLampButtonState = HIGH;
	// bool lampButtonReading;
	// unsigned long lastLampDebounceTime = 0;

	// unsigned long debounceDelay = 50;

	bool loadState = HIGH;

// System A
	unsigned long controlPreviousMillis = 0;
	unsigned long controlTimeElapsed;
	const int controlInterval = 200;
void setup() {
	// System A: Remote
	// const char* pinName[] = {"jLSel", "led1", "jRSel", "led2", "led3", "butt1", "butt2", "led4", "led5", "led6", "butt3", "jRVert", "JRHorz", "jLVert", "jRHorz"};
	// const char* pinNumber[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "A4", "A5", "A6", "A7"};
	// for (int a = 0; a < 21; a++) {
	// 	const char* pinName[a] = pinNumber[];
	// }

	// const char* inputPinMode[] = { "A4", "A5", "A6", "A7"};
	// for (int a = 0; a < 4; a++) {
	// 	pinMode(inputPinMode[a], INPUT);
	// }

	// const int inputPullupPinMode[] = {2, 4, 7, 8, 12};
	// for (int a = 0; a < 5; a++) {
	// 	pinMode(inputPullupPinMode[a], INPUT_PULLUP);
	// }

	// const int ledOutputPinMode[] = {3, 5, 6, 9, 10, 11};
	// for (int a = 0; a < 6; a++) {
	// 	pinMode(ledOutputPinMode[a], OUTPUT);
	// }

	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
	pinMode(A6, INPUT);
	pinMode(A7, INPUT);

	pinMode(2, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(7, INPUT_PULLUP);
	pinMode(8, INPUT_PULLUP);
	pinMode(12, INPUT_PULLUP);
	
	// const int ledPins[] = {3, 5, 6, 9, 10, 11};
	// for (int a = 0; a < 6; a++) {
	// 	pinMode(ledPins[a], OUTPUT);
	// 	digitalWrite(ledPins[a], LOW);
	// 	delay(100);
	// 	digitalWrite(ledPins[a], HIGH);
	// }

	// for (int a = 5; a = 1; a++) {
	// 	digitalWrite(ledPins[a], LOW);
	// 	delay(100);
	// 	digitalWrite(ledPins[a], HIGH);
	// }

	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);	

	digitalWrite(3, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, LOW);
	delay(200);

	digitalWrite(3, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, LOW);
	digitalWrite(11, HIGH);
	delay(200);
	
	digitalWrite(3, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(9, LOW);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	delay(200);
	
	digitalWrite(3, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	delay(200);
	
	digitalWrite(3, HIGH);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	delay(200);
	
	digitalWrite(3, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	delay(200);
	
	digitalWrite(3, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	delay(200);
	
	// System D
	Serial.begin(9600);
	Serial.println("Ready");
}

void loop() {
	currentMillis = millis();

	debugTimeElapsed = currentMillis - debugPreviousMillis;
	if (debugTimeElapsed >= debugInterval) {
		debugPreviousMillis = currentMillis;
		// serialDebug(); // Disable this when not debugging
		blinkWithoutDelay();
	}

	controlTimeElapsed = currentMillis - controlPreviousMillis;
	if (controlTimeElapsed >= controlInterval) {
		controlPreviousMillis = currentMillis;
		// serialDebug(); // Disable this when not debugging
		joystickLeftRegion();
		joystickRightRegion();
		joystickLeftState();
		joystickRightState();
		buttonState();
		Serial.print(joystickLeftValue);
		Serial.print(joystickRightValue);
		Serial.print(joystickLeftButtValue);
		Serial.print(joystickRightButtValue);
		Serial.print(butt1Value);
		Serial.print(butt2Value);
		Serial.println(butt3Value);
	}
}

void joystickLeftRegion() {
	// HORZ
	if (analogRead(A7) < 447) {
		xLValue = -1;
	} else if (analogRead(A7) > 575) {
		xLValue = 1;
	} else {
		xLValue = 0;
	}

	// VERT
	if (analogRead(A6) < 447) {
		yLValue = -1;
	} else if (analogRead(A6) > 575) {
		yLValue = 1;
	} else {
		yLValue = 0;
	}
}

void joystickRightRegion() {
	// HORZ
	if (analogRead(A5) < 447) {
		xRValue = -1;
	} else if (analogRead(A5) > 575) {
		xRValue = 1;
	} else {
		xRValue = 0;
	}

	// VERT
	if (analogRead(A4) < 447) {
		yRValue = -1;
	} else if (analogRead(A4) > 575) {
		yRValue = 1;
	} else {
		yRValue = 0;
	}
}

void joystickLeftState() {
	if (xLValue == -1 && yLValue == 1) {
		joystickLeftValue = "Z";
	} else if (xLValue == 0 && yLValue == 1) {
		joystickLeftValue = "X";
	} else if (xLValue == 1 && yLValue == 1) {
		joystickLeftValue = "C";
	} else if (xLValue == -1 && yLValue == 0) {
		joystickLeftValue = "A";
	} else if (xLValue == 0 && yLValue == 0) {
		joystickLeftValue = "S";
	} else if (xLValue == 1 && yLValue == 0) {
		joystickLeftValue = "D";
	} else if (xLValue == -1 && yLValue == -1) {
		joystickLeftValue = "Q";
	} else if (xLValue == 0 && yLValue == -1) {
		joystickLeftValue = "W";
	} else if (xLValue == 1 && yLValue == -1) {
		joystickLeftValue = "E";
	} else {
		joystickLeftValue = "S";
	}
}

void joystickRightState() {
	if (xRValue == -1 && yRValue == 1) {
		joystickRightValue = "M";
	} else if (xRValue == 0 && yRValue == 1) {
		joystickRightValue = "<";
	} else if (xRValue == 1 && yRValue == 1) {
		joystickRightValue = ">";
	} else if (xRValue == -1 && yRValue == 0) {
		joystickRightValue = "J";
	} else if (xRValue == 0 && yRValue == 0) {
		joystickRightValue = "K";
	} else if (xRValue == 1 && yRValue == 0) {
		joystickRightValue = "L";
	} else if (xRValue == -1 && yRValue == -1) {
		joystickRightValue = "U";
	} else if (xRValue == 0 && yRValue == -1) {
		joystickRightValue = "I";
	} else if (xRValue == 1 && yRValue == -1) {
		joystickRightValue = "O";
	} else {
		joystickRightValue = "K";
	}
}

void buttonState() {
	// lampButtonReading = digitalRead(2);

	// if (lampButtonReading != lastLampButtonState) {
	// 	lastLampDebounceTime = millis();;
	// }

	// if ((millis() - lastLampDebounceTime) > debounceDelay) {
	// 	if (lampButtonReading != lampButtonState) {
	// 		lampButtonState = lampButtonReading;

	// 		if (digitalRead(2) == LOW) {
	// 			joystickLeftButtValue = "!";
	// 			lampState = !lampState;
	// 		} else {
	// 			joystickLeftButtValue = "1";
	// 		}
	// 	}
	// }
	if (digitalRead(2) == LOW) {
		joystickLeftButtValue = "!";
		lampState = !lampState;
	} else {
		joystickLeftButtValue = "1";
	}
	digitalWrite(5, lampState);

	if (digitalRead(4) == LOW) {
		joystickRightButtValue = "@";
		loadState = !loadState;
	} else {
		joystickRightButtValue = "2";
	}
	digitalWrite(3, loadState);

	if (digitalRead(7) == LOW) {
		butt3Value = "R";
	} else {
		butt3Value = "r";
	}

	if (digitalRead(8) == LOW) {
		butt2Value = "T";
	} else {
		butt2Value = "t";
	}

	if (digitalRead(12) == LOW) {
		butt1Value = "Y";
	} else {
		butt1Value = "y";
	}
}

// void serialDebug() {
	// Serial.println("");
	// Serial.println("Joystick L:   | Joystick R:");

	// const char* joystickSerial[] = {""["", "digitalRead(2)", "digitalRead(A6), ""] | ["", "digitalRead(A4)", "digitalRead(A5)"};
	// for (int i = 0; i < 6; a++) {
	// 	Serial.print(joystickSerial[a]);
	// }

	// Serial.print("[");
	// Serial.print(digitalRead(2));
	// Serial.print("][");
	// Serial.print(xLValue);
	// Serial.print("][");
	// Serial.print(yLValue);
	// Serial.print("][");
	// Serial.print(joystickLeftValue);
	// Serial.print("] | [");
	// Serial.print(digitalRead(4));
	// Serial.print("][");
	// Serial.print(xRValue);
	// Serial.print("][");
	// Serial.print(yRValue);
	// Serial.print("][");
	// Serial.print(joystickRightValue);
	// Serial.println("]");
	// Serial.println("Buttons:    | LEDs:");
	// Serial.print("[");
	// Serial.print(digitalRead(7));
	// Serial.print(digitalRead(8));
	// Serial.print(digitalRead(12));
	// Serial.print("] | [");
	// // D0-7 = PIND 0-7
	// Serial.print(bitRead(PIND, 3));
	// Serial.print(bitRead(PIND, 5));
	// Serial.print(bitRead(PIND, 6));
	// // D8-13 = PINB 0-5
	// Serial.print(bitRead(PINB, 1)); // D8 = PINB, 1
	// Serial.print(bitRead(PINB, 2)); // D9 = PINB, 1
	// Serial.print(bitRead(PINB, 3)); // D10 = PINB, 1
	// Serial.println("]");
// }

void blinkWithoutDelay() {
	if (digitalRead(11) == LOW) {
		digitalWrite(3, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
	} else {
		digitalWrite(3, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(10, HIGH);
		digitalWrite(11, LOW);
	}
}
