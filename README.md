An piece of code meant to be compiled and uploaded to Arduino UNO R3. 

By default the led is lighting continuous green.

By pressing a button you switch the mode in which the controller is working.

The second mode is the yellow and red led blinking every second.

Third mode yellow and red blink every two seconds.

The millis function is a timestamp and allows to check for a button press. We needed to 
avoid using delay to get the button working.

The pressing of the button is recognised by the depressing of the button. Used two stated
divided by a 25 miliseconds and changes the mode.

There could be an issue when someone presses the button over the number of values of the 
valueToIncrease variable. But that would take a lot of button pressing.