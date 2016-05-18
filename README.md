# arduinoPOS_Screen
Arduino project to use a Point of Sale screen with Chromis POS

This is a proof of concept, not a final release or stable release software. I assume no liability for software defects or malfunctions. Use it as an experimental software at your own risk.

I've used a Arduino pro mini ATMega328 5v connect to an Ft232bl FT232 USB TO TTL serial to USB converter to receive serial data from
a Point of Sale computer running Chromis POS. To display the data I've used a  LCD with 4x20 characters based on the Hitachi HD44780 driver.

The arduino is programmed to loop all time reading the characters received by the usb virtual serial port.

To configure this serial port I need to configure the serial port before start Chromis POS, for example under Windows OS:
adding in the start.bat file the following line before start Chromis, asuming the COM10 port is asigned to Arduino:
MODE COM10 BAUD=9600 PARITY=n DATA=8 STOP=1

I've tweaked the DeviceDisplaySurePOS.java class to modify initVisor(), repaintLines(), repaint4Lines() methods to use my custom control characters and to increase the display lines to four.



And configuring Chromis POS for use it:
ClientVisor: SurePOS
Mode: serial
Port: COM10
Save and Restart
