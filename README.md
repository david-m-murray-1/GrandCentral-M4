# GrandCentral-M4
Adafruit Grand Central M4.  DSP, display, and CS4271/CS4272 programs.

The first issue is with the COM ports and the Grand Central.  Before uploading, press the reset button twice in quick succession.  Then change to the newly available port.  Rebooting the PC seems to be the best fix for this problem.  I am going to use an Atmel ICE debugger on the JTAG pins to upload code from now on and forgo the use of the COM ports except when using the serial monitor.  In addition, I will use a third party serial monitor.  The error: "Error while setting serial port parameters: 115,200 N 8 1" arises when trying to connect to the serial monitor, currently. 

Second, the program freezes before entering the main loop when using Adafruit_ili9341.h and PWM (timer based interrupt).  void setup() executes fine, but the program freezes at the end of setup.

A third issue is with the serial monitor when using the Adafruit_ili9341.h and XPT2046_Touchscreen.h libraries together -- issue #1 rises from the dead here.
