unsigned int swStatus = 1;
unsigned int greenLed = 3;
unsigned int redLed = 4;
unsigned int blueLed = 5;
unsigned int button = 2;
unsigned int interval = 0;

unsigned long previousTime = 0;
bool flashing = false;

void setup() {
	pinMode(greenLed, OUTPUT);
	pinMode(redLed, OUTPUT);
	pinMode(blueLed, OUTPUT);
	pinMode(button, INPUT);
}

void loop() {
	unsigned long currentTime = millis();

	if (digitalRead(button) == HIGH)
	{
		flashing = !flashing;
	}

	if (flashing)
	{
		digitalWrite(greenLed, LOW);

		if (currentTime - previousTime >= 2000 && interval % 2 == 0 ) {
			previousTime = currentTime;
			digitalWrite(redLed, !digitalRead(redLed));
			digitalWrite(blueLed, LOW);
			interval ++;
		} 
		if (currentTime - previousTime >= 2000 && interval % 2) {
			previousTime = currentTime;
			digitalWrite(blueLed, !digitalRead(blueLed));
			digitalWrite(redLed, LOW);
			interval ++;
		} 
	}
	else
	{
		digitalWrite(greenLed, HIGH);
		digitalWrite(redLed, LOW);
		digitalWrite(blueLed, LOW);
	}
}
