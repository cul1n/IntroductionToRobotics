const int buttonPin = 2;
const int buzzerPin = 3;
const int redCarLed = 13;
const int yellowCarLed = 12;
const int greenCarLed = 11;
const int redCrossingLed = 10;
const int greenCrossingLed = 9;

bool buttonState = LOW;
bool lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

int currentState = 1;
bool wasButtonPressed = false;

unsigned long timer = 0;
unsigned int firstDelay = 10000;
unsigned int secondDelay = 3000;
unsigned int thirdDelay = 10000;
unsigned int fourthDelay = 5000;

unsigned int blinkerDelay = 250;
unsigned long blinkerTimer = 0;
unsigned int buzzerDelay = 1000;
unsigned long buzzerTimer = 0;
int buzzerFrequency = 750; 
int buzzerDuration = 100;
bool blinker = LOW;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redCarLed, OUTPUT);
  pinMode(yellowCarLed, OUTPUT);
  pinMode(greenCarLed, OUTPUT);
  pinMode(redCrossingLed, OUTPUT);
  pinMode(greenCrossingLed, OUTPUT);
  state1();
  Serial.begin(9600);
}

void loop() {
  buttonManager();
  stateManager();
  blinkingManager();
}

// Checks if button has been pressed
void buttonManager() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      // If the current state is not 1, the button should not yield any action.
      if (buttonState == LOW && wasButtonPressed == false && currentState == 1) {
        timer = millis();
        wasButtonPressed = true;
      }
    }
  }
  lastButtonState = reading;
}

// Switches between states if the timer reaches the intended delay.
void stateManager() {
  if (currentState == 1 && wasButtonPressed && millis() - timer > firstDelay) {
    wasButtonPressed = false;
    currentState = 2;
    timer = millis();
    state2();
  }
  
  else if (currentState == 2 && millis() - timer > secondDelay) {
    timer = millis();
    buzzerTimer = millis();
    currentState = 3;
    state3();
  }

  else if (currentState == 3 && millis() - timer > thirdDelay) {
    timer = millis();
    blinkerTimer = millis();
    currentState = 4;
    state4();
  }

  else if (currentState == 4 && millis() - timer > fourthDelay) {
    timer = millis();
    blinker = LOW;
    currentState = 1;
    state1();
  }
  
}

void state1() {
  digitalWrite(greenCarLed, HIGH);
  digitalWrite(yellowCarLed, LOW);
  digitalWrite(redCarLed, LOW);
  digitalWrite(redCrossingLed, HIGH);
  digitalWrite(greenCrossingLed, LOW);
}

void state2() {
  digitalWrite(greenCarLed, LOW);
  digitalWrite(yellowCarLed, HIGH);
  digitalWrite(redCarLed, LOW);
  digitalWrite(redCrossingLed, HIGH);
  digitalWrite(greenCrossingLed, LOW);
}

void state3() {
  digitalWrite(greenCarLed, LOW);
  digitalWrite(yellowCarLed, LOW);
  digitalWrite(redCarLed, HIGH);
  digitalWrite(redCrossingLed, LOW);
  digitalWrite(greenCrossingLed, HIGH);
}

void state4() {
  digitalWrite(greenCarLed, LOW);
  digitalWrite(yellowCarLed, LOW);
  digitalWrite(redCarLed, HIGH);
  digitalWrite(redCrossingLed, LOW);
  digitalWrite(greenCrossingLed, HIGH);
}

void blinkingManager() {
  // In the case of state 3, the buzzer starts playing. 
  if (currentState == 3) {
    if(millis() - buzzerTimer > buzzerDelay) {
      tone(buzzerPin, buzzerFrequency, buzzerDuration);
      buzzerTimer = millis();
    }
  }
  // In the case of state 4, the green light intended for crossing starts blinking.
  else if (currentState == 4) {
    if (millis() - blinkerTimer > blinkerDelay) {
      if (blinker == LOW) {
        // The buzzer is faster than in state 3 and it is played every time the green light blinks.
        tone(buzzerPin, buzzerFrequency, buzzerDuration);
      }
      blinker = !blinker; 
      blinkerTimer = millis();
    }
    digitalWrite(greenCrossingLed, blinker);
  }
}
