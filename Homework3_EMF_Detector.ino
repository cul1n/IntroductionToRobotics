const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int antennaPin = A5;
const int buzzerPin = 10;

const int buzzerFrequency = 150;
const int buzzerDuration = 200;

const int segSize = 8;
const int noOfDigits = 10;
bool dpState = LOW;

const int sample = 300;
const int maxValue = 100;
float value;
int reading;

unsigned long average;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

bool digitMatrix[noOfDigits][segSize - 1] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit, bool decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(pinDP, decimalPoint);
}

void setup() {
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(antennaPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {             
  for(int i = 0; i < sample; i++){
     reading = analogRead(antennaPin);
     average += reading;
  }
  
  value = average / sample;

  value = constrain(value, 0, maxValue);                                                   
  value = map(value, 0, maxValue + 1, 0, noOfDigits);                                         
  
  displayNumber(value, LOW);
  average = 0;
  
  tone(buzzerPin, buzzerFrequency * value, buzzerDuration);

  delay(400);
}
