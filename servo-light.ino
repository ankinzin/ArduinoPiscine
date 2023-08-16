#include <Servo.h>


Servo myservo;  // create servo object to control a servo
Servo myservoDuo;

int right;    // variable to read the value from the analog pin
int center;
int left;
int servo = 90;
int potpin_right = 0;  // analog pin used to connect the potentiometer
int potpin_center = 1;
int potpin_left = 2;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoDuo.attach(10);
  Serial.begin(9600);
  myservo.write(90);
  myservoDuo.write(90);
  delay(3000);
}

void loop() {
  right = analogRead(potpin_right);            // reads the value of the potentiometer (value between 0 and 1023)
  center = analogRead(potpin_center);
  left = analogRead(potpin_left);
  /*
   * the darker the lower the registered value
  */ 
  /*printing out the values*/
  Serial.println("A0 right=");
  Serial.println(right);
  Serial.println("\n");
  delay(100); 
  Serial.println("A1 center=");
  Serial.println(center);
  Serial.println("\n");
  delay(100); 
  Serial.println("A2 left=");
  Serial.println(left);
  Serial.println("\n");
  /*comparison and setting the data to be sent to the servo*/
  if (center > right && center > left) {
  }
  else if(right > left && servo > 0) {
    servo = servo - 10;
  }
  else if(left > right && servo < 180) {
    servo = servo + 10;
  }
  myservo.write(servo);
  myservoDuo.write(servo);
  delay(500);                           // waits for the servo to get there
}