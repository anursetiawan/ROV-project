// Relay I, for thruster A and B
const int in1A = 6;
const int in2A = 7;
const int in3A = 8;
const int in4A = 9;

//Relay II, for thruster C and D
const int in1B = 2;
const int in2B = 3;
const int in3B = 4;
const int in4B = 5;

// Relay III, for lamp
const int R1 = 10;
int lampState;


void setup() {

	pinMode(in1A, OUTPUT);
	pinMode(in2A, OUTPUT);
	pinMode(in3A, OUTPUT);
	pinMode(in4A, OUTPUT);

	pinMode(in1B, OUTPUT);
	pinMode(in2B, OUTPUT);
	pinMode(in3B, OUTPUT);
	pinMode(in4B, OUTPUT);

	pinMode(R1, OUTPUT);

	digitalWrite(in1A, HIGH);
	digitalWrite(in2A, HIGH);
	digitalWrite(in3A, HIGH);
	digitalWrite(in4A, HIGH);

	digitalWrite(in1B, HIGH);
	digitalWrite(in2B, HIGH);
	digitalWrite(in3B, HIGH);
	digitalWrite(in4B, HIGH);

	digitalWrite(R1, LOW);

	Serial.begin(9600);

	Serial.println(" ");
	Serial.println(" ");
	Serial.println("START");
	serialDebug();
	Serial.println(" ");
	digitalWrite(13, HIGH);
	Serial.println("10");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("9");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("8");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("7");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("6");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("5");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("4");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("3");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("2");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
	digitalWrite(13, HIGH);
	Serial.println("1");
	delay(500);
	digitalWrite(13, LOW);
	delay(500);


	// Wait 2 minutes during installation
//	delay(120000);
}

void loop() {

	// Run. Switch. Repeat

	lampToggle();

	lampState = digitalRead(R1);
	if (lampState == HIGH) {
		digitalWrite(13, HIGH);
	} else {
		digitalWrite(13, LOW);
	}

	// Go forward for 5 seconds
	goForward();
	serialDebug();
	delay(2000);
	relayAStop();
	delay(500);

	// Go backward for 5 seconds
	goBackward();
	serialDebug();
	delay(2000);
	relayAStop();
	delay(500);	

	// Go upward for 5 seconds
	goUpward();
	serialDebug();
	delay(2000);
	relayBStop();
	delay(500);

	// Go downward for 5 seconds
	goDownward();
	serialDebug();
	delay(2000);
	relayBStop();
	delay(500);

	// Yaw left for 5 seconds
	yawLeft();
	serialDebug();
	delay(2000);
	relayAStop();
	delay(500);	

	// Yaw right for 5 seconds
	yawRight();
	serialDebug();
	delay(2000);
	relayAStop();
	delay(500);	

	// Roll left for 5 seconds
	rollLeft();
	serialDebug();
	delay(2000);
	relayBStop();
	delay(500);

	// Roll right for 5 seconds
	rollRight();
	serialDebug();
	delay(2000);
	relayBStop();
	delay(500);

	Serial.println(" ");
	Serial.println("NEW LOOP");
	Serial.println(" ");

}

void goForward() {
	digitalWrite(in1A, LOW);
	digitalWrite(in2A, HIGH);
	digitalWrite(in3A, LOW);
	digitalWrite(in4A, HIGH);
}

void goBackward() {
	digitalWrite(in1A, HIGH);
	digitalWrite(in2A, LOW);
	digitalWrite(in3A, HIGH);
	digitalWrite(in4A, LOW);
}

void goUpward() {
	digitalWrite(in1B, LOW);
	digitalWrite(in2B, HIGH);
	digitalWrite(in3B, LOW);
	digitalWrite(in4B, HIGH);
}

void goDownward() {
	digitalWrite(in1B, HIGH);
	digitalWrite(in2B, LOW);
	digitalWrite(in3B, HIGH);
	digitalWrite(in4B, LOW);
}

void yawLeft() {
	digitalWrite(in1A, LOW);
	digitalWrite(in2A, HIGH);
	digitalWrite(in3A, HIGH);
	digitalWrite(in4A, LOW);
}

void yawRight() {
	digitalWrite(in1A, HIGH);
	digitalWrite(in2A, LOW);
	digitalWrite(in3A, LOW);
	digitalWrite(in4A, HIGH);
}

void rollLeft() {
	digitalWrite(in1B, LOW);
	digitalWrite(in2B, HIGH);
	digitalWrite(in3B, HIGH);
	digitalWrite(in4B, LOW);
}

void rollRight() {
	digitalWrite(in1B, HIGH);
	digitalWrite(in2B, LOW);
	digitalWrite(in3B, LOW);
	digitalWrite(in4B, HIGH);
}

void relayAStop() {
	digitalWrite(in1A, HIGH);
	digitalWrite(in2A, HIGH);
	digitalWrite(in3A, HIGH);
	digitalWrite(in4A, HIGH);
}

void relayBStop() {
	digitalWrite(in1B, HIGH);
	digitalWrite(in2B, HIGH);
	digitalWrite(in3B, HIGH);
	digitalWrite(in4B, HIGH);
}

void lampToggle() {
	digitalWrite(R1, LOW);
	delay(1000);
	digitalWrite(R1, HIGH);
}

void serialDebug() {
	Serial.print("Relay A : ");
	Serial.print("[");
	Serial.print("X");
	Serial.print("]");
	Serial.print(bitRead(PIND,6));
	Serial.print(bitRead(PIND,7));
	Serial.print(bitRead(PINB,0));
	Serial.print(bitRead(PINB,1));
	Serial.print("[");
	Serial.print("X");
	Serial.print("]");
	Serial.print(" | ");
	Serial.print("Relay B: ");
	Serial.print("[");
	Serial.print("X");
	Serial.print("]");
	Serial.print(bitRead(PIND,2));
	Serial.print(bitRead(PIND,3));
	Serial.print(bitRead(PIND,4));
	Serial.print(bitRead(PIND,5));
	Serial.print("[");
	Serial.print("X");
	Serial.println("]");
}