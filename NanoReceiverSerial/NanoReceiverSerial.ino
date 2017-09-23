// setting up variables
int keyInput;       // variable for serial input
char* horizontalState; // state of the horizontal motors
char* verticalState; // state of the vertical motors
int lampState; //state of the lamp

/* motor configuration is as follow:
 * motor A is the starboard top side, connected to motor driver I on A side
 * motor B is the port top side, connected to motor driver I on B side
 * motor C is the starboard bottom side, connected to motor driver II on A side
 * motor D is the port bottom side, connected to motor driver II on B side
 * motor driver I is on starboard side, motor driver II is on port side
 */

// this block is for motor driver I
const int pwmA = 6; // ENA pin
const int pwmB = 9; // ENB pin
const int inA1 = 2; // IN1 pin
const int inA2 = 3; // IN2 pin
const int inB3 = 4; // IN3 pin
const int inB4 = 5; // IN4 pin

// this block is for motor driver II
const int pwmC = 10; // ENA pin
const int pwmD = 11; // ENB pin
const int inC1 = 14; // IN1 pin
const int inC2 = 15; // IN2 pin
const int inD3 = 16; // IN3 pin
const int inD4 = 17; // IN4 pin

// lamp toggle, connected with a relay
const int lamp = 13; 

void setup() {                    // put your setup code here, to run once:

Serial.begin(2000000); // serial baud rate, make sure this is the same with Serial Monitor
Serial.setTimeout(1); // gotta go fast

// this block is for motor driver I
pinMode(pwmA, OUTPUT);
pinMode(pwmB, OUTPUT);
pinMode(inA1, OUTPUT);
pinMode(inA2, OUTPUT);
pinMode(inB3, OUTPUT);
pinMode(inB4, OUTPUT);

digitalWrite(inA1, LOW);
digitalWrite(inA2, LOW);
digitalWrite(inB3, LOW);
digitalWrite(inB4, LOW);
analogWrite(pwmA, 0);
analogWrite(pwmB, 0);

// this block is for motor driver II
pinMode(pwmC, OUTPUT);
pinMode(pwmD, OUTPUT);
pinMode(inC1, OUTPUT);
pinMode(inC2, OUTPUT);
pinMode(inD3, OUTPUT);
pinMode(inD4, OUTPUT);

digitalWrite(inC1, LOW);
digitalWrite(inC2, LOW);
digitalWrite(inD3, LOW);
digitalWrite(inD4, LOW);
analogWrite(pwmC, 0);
analogWrite(pwmD, 0);

// this block is for lamp trigger
pinMode(lamp, OUTPUT);

digitalWrite(lamp, LOW);

/* all output pins are set as OUTPUT and LOW
 * each run as to ensure there is no unexpected behavior 
 */

Serial.println("READY");
Serial.println("-----");
delay(100);
mStop();
motorState();
}

void loop() {                     // put your main code here, to run repeatedly:
  receiveOneCharacter();
  conditionsCase();
}

void conditionsCase(){                // this block contain list of maneuvers
  switch (keyInput){
    case '0':         // stopping all motors
      mStop();
      break;
  // ===      
    case 'q':         // this block is for motor driver I
      mForwardLeft();
      break;
    case 'w':
      mForward();
      break;
    case 'e':
      mForwardRight();
      break;
  // ---
    case 'a':
      mYawLeft();
      break;
    case 's':
      mStopH();
      break;
    case 'd':
      mYawRight();
      break;
  // ---
    case 'z':
      mBackwardLeft();
      break;
    case 'x':
      mBackward();
      break;
    case 'c':
      mBackwardRight();
      break;
  // ===
    case 'i':           // this block is for motor driver II
      mUp();
      break;
  // ---
    case 'j':
      mRollLeft();
      break;
    case 'k':
      mStopV();
      break;
    case 'l':
      mRollRight();
      break;
  // ---
    case ',':
      mDown();
      break;
  // ===
    case '1':         // this is for the lamp, it is number 1 (one) by the way, not an l (L)
      lampOn();
      break;
    case '2':
      lampOff();
      break; 
}
}

void receiveOneCharacter(){       // reading the input from serial monitor, can only parse the first character sent
  keyInput = Serial.read();

}

void motorState(){                // displaying the state of all outputs and maneuver configuration, useful for debugging
  Serial.print(horizontalState);  // result is displayed in format:
  Serial.print(" | ");            // H motor manv | V motors manv   [pwmA] inA1 inA2 inB3 inB4 [pwmB]|[pwmC] inC1 inC2 inD3 inD4 [pwmD]
  Serial.print(verticalState);    // example:
  // ---                          // Forward | Down   [1]1010[1]|[1]0101[1]
  Serial.print("   ");
  // ---
  Serial.print("[");
  Serial.print(bitRead(PIND,6));
  Serial.print("]");
  Serial.print(bitRead(PIND,2));
  Serial.print(bitRead(PIND,3));
  Serial.print(bitRead(PIND,4));
  Serial.print(bitRead(PIND,5));
  Serial.print("[");
  Serial.print(bitRead(PINB,1));
  Serial.print("]");
  // ---
  Serial.print(" | ");
  // ---
  Serial.print("[");
  Serial.print(bitRead(PINB,2));
  Serial.print("]");
  Serial.print(bitRead(PINC,0));
  Serial.print(bitRead(PINC,1));
  Serial.print(bitRead(PINC,2));
  Serial.print(bitRead(PINC,3));
  Serial.print("[");
  Serial.print(bitRead(PINB,3));
  Serial.println("]");
  Serial.println("-----");
}

// ===

void mStop(){                     // stopping all motors
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  horizontalState = "Stop";
  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD3, LOW);
  digitalWrite(inD4, LOW);
  analogWrite(pwmC, 0);
  analogWrite(pwmD, 0);
  verticalState = "Stop";
}

// ===

void mForwardLeft(){              // only the horizontal starboard motor is pushing forward
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Forward Left";
  motorState();
}

void mForward(){                  // both horizontal motors are pushing forward
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Forward";
  motorState();
}

void mForwardRight(){             // only the horizontal port motor is pushing forward
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Forward Right";
  motorState();
}

void mYawLeft(){                  // both horizontal motors are rotating against each other, ROV is heading towards left
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Yaw Left";
  motorState();
}

void mStopH(){                    // stopping all horizontal motors
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  horizontalState = "Stop";
  motorState();
}

void mYawRight(){                 // both horizontal motors are rotating against each other, ROV is heading towards right
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Yaw Right";
  motorState();
}

void mBackwardLeft(){             // only the horizontal starboard motor is pushing backward
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Backward Left";
  motorState();
}

void mBackward(){                 // both horizontal motors are pushing backward
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Backward";
  motorState();
}

void mBackwardRight(){            // only the horizontal port motor is pushing backward
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  horizontalState = "Backward Right";
  motorState();
}

// ===

void mUp(){                       // both vertical motors are pushing upward
  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD3, HIGH);
  digitalWrite(inD4, LOW);
  analogWrite(pwmC, 255);
  analogWrite(pwmD, 255);
  verticalState = "Up";
  motorState();
}

void mRollLeft(){                 // both vertical motors are rotating against each other, ROV is banking left
  digitalWrite(inC1, HIGH);
  digitalWrite(inC2, LOW);
  digitalWrite(inD3, LOW);
  digitalWrite(inD4, HIGH);
  analogWrite(pwmC, 255);
  analogWrite(pwmD, 255);
  verticalState = "Roll Left";
  motorState();
}

void mStopV(){                    // stopping all vertical motors
  digitalWrite(inC1, LOW);
  digitalWrite(inC2, LOW);
  digitalWrite(inD3, LOW);
  digitalWrite(inD4, LOW);
  analogWrite(pwmC, 0);
  analogWrite(pwmD, 0);
  verticalState = "Stop";
  motorState();
}

void mRollRight(){                // both vertical motors are rotating against each other, ROV is banking right
  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD3, HIGH);
  digitalWrite(inD4, LOW);
  analogWrite(pwmC, 255);
  analogWrite(pwmD, 255);
  verticalState = "Roll Right";
  motorState();
}

void mDown(){                     // both vertical motors are pushing downward
  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);
  digitalWrite(inD3, LOW);
  digitalWrite(inD4, HIGH);
  analogWrite(pwmC, 255);
  analogWrite(pwmD, 255);
  verticalState = "Down";
  motorState();
}

// ===

void lampOn(){
  digitalWrite(lamp, HIGH);
  Serial.println("Lamp is ON");
  Serial.println("-----");
}

void lampOff(){
  digitalWrite(lamp, LOW);
  Serial.println("Lamp is OFF");
  Serial.println("-----");
}

/*
void lampTrigger(){               // lamp toggle
  lampState = digitalRead(lamp);

  if (lampState == HIGH){
    digitalWrite(lamp, LOW);
    Serial.println("Lamp is OFF");
    Serial.println("-----");
  }  
  else {
    digitalWrite(lamp, HIGH);
    Serial.println("Lamp is ON");
    Serial.println("-----");
  }
}
*/
