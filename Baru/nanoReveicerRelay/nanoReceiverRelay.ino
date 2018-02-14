// Other variable convention
unsigned long currentMillis;
// unsigned long testPreviousMillis;
// unsigned long testTimeElapsed;
// const long testInterval = 60000;

// System A: Remote
// Checking whether remote is connected or not.
// If remote is not connected, it checks whether ROV is in test mode or rest mode.
// Test Mode: Wait 3 minutes, then run each movement set for 10 seconds each, sequentially.
// Rest Mode: ROV doesn't move at all.
const int remoteCheck = 2; 
const int modeSet = 3;

// System B: Driver
// Motor configuration is as follow:
// A is the starboard top side, connected to motor driver 1 on A side
// B is the port top side, connected to motor driver 1 on B side
// C is the starboard bottom side, connected to motor driver 2 on A side
// D is the port bottom side, connected to motor driver 2 on B side
// Driver 1 is on starboard side, driver 2 is on port side
// Driver 3 is for the lamp
// Driver 1 configuration, starting from in1:
const int driver1Pin[] = {4, 5, 6, 7};

// Driver 2 configuration, starting from in1:
const int driver2Pin[] = {8, 9, 10, 11};

// System C:
// Driver 3 configuration:
const int lampTrigger = 12;
const int loadTrigger = 13;

// System D: Serial and debugging
unsigned long debugPreviousMillis = 0;
unsigned long debugTimeElapsed;
const int debugInterval = 200;


void setup() {
	// System A
	// Set the checker pins as input with default to high with internal pullup resistor
	for (int a = 2; a < 4; a++) {
		pinMode(a, INPUT_PULLUP);
	}

	// System B
	// Set the rest of the pin except RX-TX as output
	for (int a = 3; a < 14; a++)	{
		pinMode(a, OUTPUT);
	}

	// Set the thrusters pin as HIGH to turn off
	for (int a = 3; a < 12; a++)	{
		digitalWrite(a, HIGH);
	}

	// System C
	// Main lamp to off
	digitalWrite(lampTrigger, LOW);

	// also the add-on load
	digitalWrite(loadTrigger, LOW);

	allStop();

	// System D
	Serial.begin(9600);
	Serial.println("");
	Serial.println("");
	Serial.println("---------");
	Serial.println("| READY |");
	Serial.println("---------");
}

void loop() {
	// Every half a second, print the state of pins
	currentMillis = millis();
	debugTimeElapsed = currentMillis - debugPreviousMillis;
	if (debugTimeElapsed >= debugInterval) {
		debugPreviousMillis = currentMillis;
		serialDebug();
	}

	// Check whether remote is connected or not, and the mode set

	// // Dummy connected remote
	// pinMode(remoteCheck, OUTPUT);
	// digitalWrite(remoteCheck, LOW);

	if (digitalRead(remoteCheck) == LOW) {
		movementSet();
	} else if (digitalRead(remoteCheck) == HIGH) {
		if (digitalRead(modeSet) == LOW) {
		restMode();
		} else if (digitalRead(modeSet) == HIGH) {
		testMode();
		}
	}
}

void movementSet() {
	int keyInput = Serial.read();
	switch (keyInput) {
		// System B
		// Driver 1 movement set
	    case 'Q':
	      forwardLeft();
	      break;
	    case 'W':
	      forward();
	      break;
	    case 'E':
	      forwardRight();
	      break;
	    case 'A':
	      yawLeft();
	      break;
	    case 'S':
	      allStop1();
	      break;
	    case 'D':
	      yawRight();
	      break;
	    case 'Z':
	      backwardLeft();
	      break;
	    case 'X':
	      backward();
	      break;
	    case 'C':
	      backwardRight();
	      break;

	    // Driver 2 movement set
	    case 'U':
	      upwardLeft();
	      break;
	    case 'I':
	      upward();
	      break;
	    case 'O':
	      upwardRight();
	      break;
	    case 'J':
	      rollLeft();
	      break;
	    case 'K':
	      allStop2();
	      break;
	    case 'L':
	      rollRight();
	      break;
	    case 'M':
	      downwardLeft();
	      break;
	    case '<':
	      downward();
	      break;
	    case '>':
	      downwardRight();
	      break;

	    // From joystick buttons
	    case '!':
	      lamp();
	      break;
	    case '@':
	      load();
	      break;
	    // case '#':
	    //   allStop3();
	    //   break;

	    // Stop everything
	    // case '0':
	    //   allStop();
	    //   break;

	    // From push buttons
	    case 'R':
	      // do something
	      break;
	    case 'r':
	      // do something
	      break;
	    case 'T':
	      // do something
	      break;
	    case 't':
	      // do something
	      break;
	    case 'Y':
	      // do something
	      break;
	    case 'y':
	      // do something
	      break;
	}
}

// System B
// Function of driver 1 movement set
void forwardLeft() {
	int pinState[] = {0, 1, 1, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void forward() {
	int pinState[] = {0, 1, 0, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void forwardRight() {
	int pinState[] = {1, 1, 0, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void yawLeft() {
	int pinState[] = {0, 1, 1, 0};
	multiWrite4Pin(driver1Pin, pinState);
}

void stopDriverI() {
	int pinState[] = {1, 1, 1, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void yawRight() {
	int pinState[] = {1, 0, 0, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void backwardLeft() {
	int pinState[] = {1, 0, 1, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void backward() {
	int pinState[] = {1, 0, 1, 0};
	multiWrite4Pin(driver1Pin, pinState);
}

void backwardRight() {
	int pinState[] = {1, 1, 0, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

// Function of driver 2 movement set
void upwardLeft() {
	int pinState[] = {0, 1, 1, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void upward() {
	int pinState[] = {0, 1, 0, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void upwardRight() {
	int pinState[] = {1, 1, 0, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void rollLeft() {
	int pinState[] = {0, 1, 1, 0};
	multiWrite4Pin(driver2Pin, pinState);
}

void stopDriverII() {
	int pinState[] = {1, 1, 1, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void rollRight() {
	int pinState[] = {1, 0, 0, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void downwardLeft() {
	int pinState[] = {1, 0, 1, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void downward() {
	int pinState[] = {1, 0, 1, 0};
	multiWrite4Pin(driver2Pin, pinState);
}

void downwardRight() {
	int pinState[] = {1, 1, 0, 1};
	multiWrite4Pin(driver2Pin, pinState);	
}

void allStop1() {
	int pinState[] = {1, 1, 1, 1};
	multiWrite4Pin(driver1Pin, pinState);
}

void allStop2() {
	int pinState[] = {1, 1, 1, 1};
	multiWrite4Pin(driver2Pin, pinState);
}

void allStop3() {
	digitalWrite(lampTrigger, LOW);
	digitalWrite(loadTrigger, LOW);
}
// Makes everything stop
void allStop() {
	int pinState[] = {1, 1, 1, 1};
	multiWrite4Pin(driver1Pin, pinState);
	multiWrite4Pin(driver2Pin, pinState);
	digitalWrite(lampTrigger, LOW);
	digitalWrite(loadTrigger, LOW);
}

// Function for writing 4 pin at once
void multiWrite4Pin(int number[], int state[]) {
	for (int a = 0; a < 4; a++) {
		digitalWrite(number[a], state[a]);
	}
}

// Trigger lamp on and off
void lamp() {
	if (digitalRead(lampTrigger) == LOW) {
		digitalWrite(lampTrigger, HIGH);
	} else {
		digitalWrite(lampTrigger, LOW);
	}
}

// Trigger lamp on and off
void load() {
	if (digitalRead(loadTrigger) == LOW) {
		digitalWrite(loadTrigger, HIGH);
	} else {
		digitalWrite(loadTrigger, LOW);
	}
}

void restMode() {
	allStop();
}

void testMode() {
	// testTimeElapsed = currentMillis - testPreviousMillis;
	// if (testTimeElapsed >= testInterval) {
		for (int a = 0; a < 20; a++) {
			digitalWrite(13, HIGH);
			delay(500);
			digitalWrite(13, LOW);
			delay(500);
		}

		for (int a = 0; a < 20; a++) {
			digitalWrite(13, HIGH);
			delay(250);
			digitalWrite(13, LOW);
			delay(250);
		}

		digitalWrite(lampTrigger, HIGH);
		delay(2000);
		digitalWrite(lampTrigger, LOW);
		
		allStop();
		delay(1000);
		digitalWrite(4, LOW);
		digitalWrite(5, HIGH);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(4, HIGH);
		digitalWrite(5, LOW);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(6, LOW);
		digitalWrite(7, HIGH);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(6, HIGH);
		digitalWrite(7, LOW);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(8, LOW);
		digitalWrite(9, HIGH);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(8, HIGH);
		digitalWrite(9, LOW);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(10, LOW);
		digitalWrite(11, HIGH);
		delay(2000);

		allStop();
		delay(1000);
		digitalWrite(10, HIGH);
		digitalWrite(11, LOW);
		delay(2000);

		allStop();
		delay(1000);
		forward();
		delay(2000);

		allStop();
		delay(1000);
		backward();
		delay(2000);

		allStop();
		delay(1000);
		yawLeft();
		delay(2000);

		allStop();
		delay(1000);
		yawRight();
		delay(2000);
		
		allStop();
		delay(1000);
		upward();
		delay(2000);
		
		allStop();
		delay(1000);
		downward();
		delay(2000);
		
		allStop();
		delay(1000);
		rollLeft();
		delay(2000);
		
		allStop();
		delay(1000);
		rollRight();
		delay(2000);

		allStop();
	}
// }

void serialDebug() {
	Serial.println("");
	Serial.println("Pin configuration:");
	Serial.print("[");
	Serial.print(digitalRead(remoteCheck));
	Serial.print("][");
	Serial.print(digitalRead(modeSet));
	Serial.print("][");
	for (int a = 0; a < 4;) {
		Serial.print(digitalRead(driver1Pin[a]));
		a++;
	}
	Serial.print("|");
	for (int a = 0; a < 4;) {
		Serial.print(digitalRead(driver2Pin[a]));
		a++;
	}
	Serial.print("][");
	Serial.print(digitalRead(lampTrigger));
	Serial.print("][");
	Serial.print(digitalRead(loadTrigger));
	Serial.println("]");

	if (digitalRead(remoteCheck) == LOW) {
		Serial.println("Remote Connected");
		// movementSet();
	} else if (digitalRead(remoteCheck) == HIGH) {
		if (digitalRead(modeSet) == LOW) {
			Serial.println("In Rest Mode");
			// restMode();
		} else if (digitalRead(modeSet) == HIGH) {
			Serial.println("In Test Mode");
			// testMode();
			// Serial.print("Time elapsed: ");
			// Serial.print(testTimeElapsed/1000);
			// Serial.println(" seconds");
		}
	}
}