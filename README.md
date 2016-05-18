# arduinoPOS_Screen
Arduino project to use a Point of Sale screen with a modified Chromis POS branch https://github.com/RndMnkIII/chromispos

This is a proof of concept, not a final release or stable release software. I assume no liability for software defects or malfunctions. Use it as an experimental software at your own risk.

I've used a Arduino pro mini ATMega328 5v connect to an Ft232bl FT232 USB TO TTL serial to USB converter to receive serial data from
a Point of Sale computer running Chromis POS. To display the data I've used a  LCD with 4x20 characters based on the Hitachi HD44780 driver.

![Schematic](https://github.com/RndMnkIII/arduinoPOS_Screen/blob/master/schematic.jpg)

You'll need to install before the LiquidCrystalFast library:
https://github.com/Swap-File/tron-suit/tree/master/Helmet/Software/Libraries/LiquidCrystalFast
with the following tweaks: 
https://github.com/RndMnkIII/LiquidCrystalFast_Progmemfix

The arduino is programmed to loop all time reading the characters received by the usb virtual serial port.

You need to install the FTDI drivers from: http://www.ftdichip.com/Drivers/VCP.htm

To configure this serial port I need to configure the serial port before start Chromis POS, for example under Windows OS:
adding in the start.bat file the following line before start Chromis, asuming the COM10 port is asigned to Arduino:
MODE COM10 BAUD=9600 PARITY=n DATA=8 STOP=1

I've tweaked the DeviceDisplaySurePOS.java class in Chromis POS source code to modify initVisor(), repaintLines(), repaint4Lines() methods to use my custom control characters and to increase the display lines to four.



And configuring Chromis POS for use it:<br/>
ClientVisor: SurePOS<br/>
Mode: serial<br/>
Port: COM10<br/>
Save and Restart
