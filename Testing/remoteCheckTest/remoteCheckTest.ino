const int remoteCheck = 2; // high when disconnected
const int disMode = 3; // high when on test mode
bool remoteState = HIGH;
bool lastRemoteState = LOW;
bool disModeState = HIGH;
bool lastDisModeState = LOW;

void setup() {
	pinMode(remoteCheck, INPUT_PULLUP);
	pinMode(disMode, INPUT_PULLUP); 

	Serial.begin(9600);
}

void loop() {
	remoteState = digitalRead(remoteCheck);
	disModeState = digitalRead(disMode);

	if (remoteState == HIGH) {
		if (remoteState != lastRemoteState || disModeState != lastDisModeState) {
			if (disModeState == HIGH) {
				Serial.println("Remote Disconnected: Rest Mode");
			}

			if (disModeState == LOW) {
				Serial.println("Remote Disconnected: Test Mode");
			}
		}
	}

	if (remoteState == LOW) {
		if (remoteState != lastRemoteState) {
			Serial.println("Remote Connected");
		}
	}

	lastRemoteState = remoteState;
	lastDisModeState = disModeState;

	delay(100);
}