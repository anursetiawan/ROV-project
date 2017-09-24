const int YButton = 2;
const int AButton = 4;
const int XButton = 5;
const int BButton = 3;
const int menuButton = 6;
const int viewButton = 7;
const int joystickButton = 8;
const int joystickAxisX = A0;
const int joystickAxisY = A1;
const int buttons[] = {YButton, AButton, XButton, BButton, menuButton, viewButton, joystickButton};

int xValue;
int yValue;

char* joystickValue;
char* buttonValue;
char* menuValue = "2";

bool lampState = LOW;

void setup() {
  // put your setup code here, to run once:
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(1000); // gotta go fast
}

void loop() {

  xRegion();
  yRegion();

  joystickState();
  buttonState();
  menuState();
  
//  Serial.print(xValue), Serial.print(" | "), Serial.println(yValue);
  delay(100);

}

void xRegion() {
  
  if (analogRead(joystickAxisX) > 575) {
    xValue = 1;
  } else if (analogRead(joystickAxisX) < 447) {
    xValue = -1;
  } else {
    xValue = 0;
  }

}

void yRegion() {
  
  if (analogRead(joystickAxisY) > 575) {
    yValue = 1;
  } else if (analogRead(joystickAxisY) < 447) {
    yValue = -1;
  } else {
    yValue = 0;
  }

}

void joystickState() {
  if (xValue == -1 && yValue == 1) {
    joystickValue = "q";
  } else if (xValue == 0 && yValue == 1) {
    joystickValue = "w";
  } else if (xValue == 1 && yValue == 1) {
    joystickValue = "e";
  } else if (xValue == -1 && yValue == 0) {
    joystickValue = "a";
  } else if (xValue == 1 && yValue == 0) {
    joystickValue = "d";
  } else if (xValue == -1 && yValue == -1) {
    joystickValue = "z";
  } else if (xValue == 0 && yValue == -1) {
    joystickValue = "x";
  } else if (xValue == 1 && yValue == -1) {
    joystickValue = "c";
  } else {
    joystickValue = "s";
  }

  Serial.print(joystickValue);
  
}

void buttonState() {
  if (digitalRead(YButton) == 0) {
    buttonValue = "i";
  } else if (digitalRead(XButton) == 0) {
    buttonValue = "j";
  } else if (digitalRead(AButton) == 0) {
    buttonValue = ",";
  } else if (digitalRead(BButton) == 0) {
    buttonValue = "l";
  } else {
    buttonValue = "k";
  }

  Serial.print(buttonValue);
}

void menuState() {
  if (digitalRead(menuButton) == 0) {
    delay(100);
    if (lampState == LOW) {
      menuValue = "1";
      lampState = HIGH;
    } else {
      menuValue = "2";
      lampState = LOW;
    }
  }

  Serial.println(menuValue);
}

void serialDebug() {
  Serial.print("Y = "),Serial.print(digitalRead(YButton)),Serial.print(" | ");
  Serial.print("A = "),Serial.print(digitalRead(AButton)),Serial.print(" | ");
  Serial.print("X = "),Serial.print(digitalRead(XButton)),Serial.print(" | ");
  Serial.print("B = "),Serial.print(digitalRead(BButton)),Serial.print(" | ");
  Serial.print("Menu = "),Serial.print(digitalRead(menuButton)),Serial.print(" | ");
  Serial.print("View = "),Serial.print(digitalRead(viewButton)),Serial.print(" | ");
  Serial.print("Joystick = "),Serial.print(digitalRead(joystickButton)),Serial.print(" | ");
  Serial.print("X = "),Serial.print(map(analogRead(joystickAxisX), 0, 1023, 0, 100)), Serial.print("%"), Serial.print(" | ");
  Serial.print("Y = "),Serial.print(map(analogRead(joystickAxisY), 0, 1023, 0, 100)), Serial.println("%");
}

