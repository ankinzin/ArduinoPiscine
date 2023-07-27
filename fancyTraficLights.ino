const int buttonPin = 2;
const int ledGreen = 5;
const int ledYellow = 4;
const int ledRed = 3;
const int task1Interval = 1000;
const int task2Interval = 1000;
const int task3Interval = 2000;
const int task4Interval = 2000;
const int task5Interval = 500;
const int task6Interval = 500;
const int task7Interval = 2000;
const int task8Interval = 2000;
unsigned long lastTask1Time = 0;
unsigned long lastTask2Time = 0;
unsigned long lastTask3Time = 0;
unsigned long lastTask4Time = 0;
unsigned long lastTask5Time = 0;
unsigned long lastTask6Time = 0;
unsigned long lastTask7Time = 0;
unsigned long lastTask8Time = 0;
int valueToIncrease = 0;
bool buttonState = HIGH;
bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH){
    valueToIncrease++;
  }
  lastButtonState = buttonState;
  if(valueToIncrease % 4 == 1){
     digitalWrite(ledGreen,HIGH);
     digitalWrite(ledYellow,LOW);
     digitalWrite(ledRed,LOW);
  } 
  else if(valueToIncrease % 4 == 2){
    if (millis() - lastTask1Time >= task1Interval) {
        lastTask1Time = millis();
        digitalWrite(ledGreen,LOW);
        digitalWrite(ledYellow,LOW);
        digitalWrite(ledRed,LOW);
        if (buttonState == LOW && lastButtonState == HIGH){
        valueToIncrease++;
        }
      }
    else if (millis() - lastTask2Time >= task2Interval) {
        lastTask2Time = millis();
        digitalWrite(ledGreen,LOW);
        digitalWrite(ledYellow,HIGH);
        digitalWrite(ledRed,HIGH);
        if (buttonState == LOW && lastButtonState == HIGH){
          valueToIncrease++;
        }
    }   
  }
  else if(valueToIncrease % 4 == 3){
      if (millis() - lastTask3Time >= task3Interval) {
      lastTask3Time = millis();
      digitalWrite(ledGreen,LOW);
      digitalWrite(ledYellow,LOW);
      digitalWrite(ledRed,LOW);
      if (buttonState == LOW && lastButtonState == HIGH){
        valueToIncrease++;
    }
  }
   else if (millis() - lastTask4Time >= task4Interval) {
      lastTask4Time = millis();
      digitalWrite(ledGreen,LOW);
      digitalWrite(ledYellow,HIGH);
      digitalWrite(ledRed,HIGH);
      if (buttonState == LOW && lastButtonState == HIGH){
       valueToIncrease++;
      }
    }
  }
  else if(valueToIncrease % 4 == 0){
      if (millis() - lastTask5Time >= task5Interval) {
        lastTask5Time = millis();
        digitalWrite(ledGreen,LOW);
        digitalWrite(ledYellow,HIGH);
      if (buttonState == LOW && lastButtonState == HIGH){
       valueToIncrease++;
      }
     }
      else if (millis() - lastTask6Time >= task6Interval) {
      lastTask6Time = millis();
      digitalWrite(ledGreen,LOW);
      digitalWrite(ledYellow,LOW);
      if (buttonState == LOW && lastButtonState == HIGH){
        valueToIncrease++;
      }
  if (millis() - lastTask7Time >= task7Interval) {
      lastTask7Time = millis();
      digitalWrite(ledGreen,LOW);
      digitalWrite(ledRed,HIGH);
      if (buttonState == LOW && lastButtonState == HIGH){
        valueToIncrease++;
    }
  }
  else if (millis() - lastTask8Time >= task8Interval) {
      lastTask8Time = millis();
      digitalWrite(ledGreen,LOW);
      digitalWrite(ledRed,LOW);
      if (buttonState == LOW && lastButtonState == HIGH){
          valueToIncrease++;
      }
      }
    }
  }
  delay(25);
}