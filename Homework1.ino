const int redPotPin = A0;
const int redLedPin = 9;
int redPotValue = 0;
int redLedValue = 0;

const int greenPotPin = A1;
const int greenLedPin = 10;
int greenPotValue = 0;
int greenLedValue = 0;

const int bluePotPin = A2;
const int blueLedPin = 11;
int bluePotValue = 0;
int blueLedValue = 0;

const int minPotValue = 0;
const int maxPotValue = 1023;
const int minLedValue = 0;
const int maxLedValue = 255;

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(redLedPin, OUTPUT);

  pinMode(bluePotPin, INPUT);
  pinMode(blueLedPin, OUTPUT);
   
  pinMode(greenPotPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  redPotValue = analogRead(redPotPin);
  redLedValue = map(redPotValue, minPotValue, maxPotValue, minLedValue, maxLedValue);

  bluePotValue = analogRead(bluePotPin);
  blueLedValue = map(bluePotValue, minPotValue, maxPotValue, minLedValue, maxLedValue);

  greenPotValue = analogRead(greenPotPin);
  greenLedValue = map(greenPotValue, minPotValue, maxPotValue, minLedValue, maxLedValue);

  analogWrite(redLedPin, redLedValue);
  analogWrite(blueLedPin, blueLedValue);
  analogWrite(greenLedPin, greenLedValue);
}
