<p align="center">
	<img src="http://content.arduino.cc/brand/arduino-color.svg" width="50%" />
</p>
<h4>Arduino is an open-source physical computing platform based on a simple I/O
board and a development environment that implements the Processing/Wiring
language. Arduino can be used to develop stand-alone interactive objects or
can be connected to software on your computer (e.g. Flash, Processing and MaxMSP).
The boards can be assembled by hand or purchased preassembled; the open-source
IDE can be downloaded for free at [https://arduino.cc](https://www.arduino.cc/en/Main/Software)</h4>
A piece of code meant to be compiled and uploaded to Arduino UNO R3. 

By default the led is lighting continuous green.

By pressing a button you switch the mode in which the controller is working.

The second mode is the yellow and red led blinking every second.

Third mode yellow and red blink every two seconds.

The millis function is a timestamp and allows to check for a button press. We needed to 
avoid using delay to get the button working.

The pressing of the button is recognised by the pressing of the buttonmultiple times.
Used two stated divided by a 25 miliseconds and changes the mode.

There could be an issue when someone presses the button over the number of values of the 
valueToIncrease variable. But that would take a lot of button pressing.
