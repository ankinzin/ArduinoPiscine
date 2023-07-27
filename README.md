 <img src="https://camo.githubusercontent.com/a9e049ade1147226016feb1ab0024b7e09cf5e6ce7921aa9e7326942f98c71dd/687474703a2f2f636f6e74656e742e61726475696e6f2e63632f6272616e642f61726475696e6f2d636f6c6f722e737667" width="500" height="450" alt="Image Preview">

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
