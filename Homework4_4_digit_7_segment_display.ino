#include <EEPROM.h>

const int pinSW = 3;
const int pinX = A0;
const int pinY = A1;

int xValue = 0;
int yValue = 0;
bool joyMoved = false;
int minThreshold = 300;
int maxThreshold = 700;

const int dataPin = 12; // DS
const int latchPin = 11; // STCP
const int clockPin = 10; // SHCP;

const int seg01 = 7;
const int seg02 = 6;
const int seg03 = 5;
const int seg04 = 4;

const int displayCount = 4;
const int numberOfDigits = 10;

const int displayDigits[displayCount] = {
  seg01, seg02, seg03, seg04
};

int currentDigits[displayCount] = {
  0, 0, 0, 0
};

int dpPosition = 3;
volatile bool currentState = LOW;
unsigned long lastBlink = millis();
const int blinkDelay = 300;
bool blinker = LOW;

const int delayStateChange = 100;
unsigned long lastStateChange = millis();

int digitArray[numberOfDigits] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

void setup(){ 
  for (int i = 0; i < displayCount; i++) {
    currentDigits[i] = EEPROM.read(i);
  }
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), stateChange, FALLING);
  
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < displayCount; i++){
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop(){
  blinkerController();
  writeNumber(currentDigits, dpPosition, blinker);
  joyStickController();
  saveInMemory();
}

void writeNumber(int numbers[], int dpPosition, bool dpState){
  for (int displayDigit = 0; displayDigit < displayCount; displayDigit++){
    showDigit(displayDigit);
    if (displayDigit == displayCount - dpPosition - 1 && dpState == HIGH){
      writeReg(digitArray[numbers[displayCount - displayDigit - 1]] + 1);
    }
    else {
      writeReg(digitArray[numbers[displayCount - displayDigit - 1]]); 
    }
    delay(3);
  }
}
void showDigit(int digit){
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[digit], LOW);
}

void writeReg(int digit){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void joyStickController(){
  if (currentState == LOW){
    yValue = analogRead(pinY);
    
    if (yValue < minThreshold && joyMoved == false){
      if (dpPosition){
        dpPosition--;
      }
      else {
        dpPosition = 3;
      }
      joyMoved = true;
    }
    
    if (yValue > maxThreshold && joyMoved == false){
      if (dpPosition != 3){
        dpPosition++;
      }
      else {
        dpPosition = 0;
      }
      joyMoved = true;
    }
  
    if (yValue >= minThreshold && yValue <= maxThreshold){
      joyMoved = false;
    }
  }
  
  else if (currentState == HIGH){
    xValue = analogRead(pinX);
    
    if (xValue < minThreshold && joyMoved == false){
      if (currentDigits[dpPosition]){
        currentDigits[dpPosition]--;
      }
      else {
       currentDigits[dpPosition] = 9;
      }
      joyMoved = true;
    }
    
    if (xValue > maxThreshold && joyMoved == false){
      if (currentDigits[dpPosition] != 9){
        currentDigits[dpPosition]++;
      }
      else {
        currentDigits[dpPosition] = 0;
      }
      joyMoved = true;
    }
  
    if (xValue >= minThreshold && xValue <= maxThreshold){
      joyMoved = false;
    }

  }
}

void blinkerController(){
  if (millis() - lastBlink > blinkDelay){
    blinker = !blinker;
    lastBlink = millis();
  }
  if (currentState == HIGH) {
    blinker = HIGH;
  }
}

void stateChange(){
  if (millis() - lastStateChange >= delayStateChange){
    currentState = !currentState; 
    lastStateChange = millis();
  }
}

void saveInMemory(){
  for (int i = 0; i < displayCount; i++) {
    EEPROM.write(i, currentDigits[i]);
  }
}
