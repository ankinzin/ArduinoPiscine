unsigned int swStatus = 1;
unsigned int greenLed = 3;
unsigned int redLed = 4;
unsigned int blueLed = 5;
unsigned int button = 2;

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
		delay(150);
	}

	if (flashing)
	{
		digitalWrite(greenLed, LOW);

		if (currentTime - previousTime >= 1000)
		{
			previousTime = currentTime;
			digitalWrite(redLed, !digitalRead(redLed));
			digitalWrite(blueLed, !digitalRead(blueLed));
		} 
	}
	else
	{
		digitalWrite(greenLed, HIGH);
		digitalWrite(redLed, LOW);
		digitalWrite(blueLed, LOW);
	}
}
