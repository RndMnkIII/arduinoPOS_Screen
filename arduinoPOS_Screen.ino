/*****************************************************************
 * Project: arduinoPOS_Screen
 * Author: RndMnkIII
 * Description: using Arduino Pro Mini ATMega328 5V + FTDI Serial2USB + Hitachi HD44780 4x20 characters display
 * to create a Point of Sale Screen to use with Chromis POS
 */

/* You need install the files in my custom LiquidCrystalFasth library located at https://github.com/RndMnkIII/LiquidCrystalFast_Progmemfix or update if already installed
   in <User-directory>\Documents\Arduino\libraries\LiquidCrystalFast */
#include <LiquidCrystalFast.h>

/* Initialize library with the following pin usage:
 * LCD RS pin to digital pin 12
 * LCD WR pin to digital pin 10
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 */
LiquidCrystalFast lcd(12, 10, 11, 5, 4, 3, 2); 

/* Because I using a Hitachi HD44780 controller with the HCD44780UA00 japanese standard font
 *  I need to define custom characters for several NON STANDARD ASCII characters: € (euro currency simbol), 
 *  á (a acute), é(e acute), í(i acute), ó(o acute), ú(u acute),ü (small u diaeresis), ñ(small n tilde)
 *  The HCD44780UA02 controller use European standard font and don't needed custom characters for these except the euro symbol.
 */
const byte euro[8] PROGMEM = {
  B00110,
  B01001,
  B11100,
  B01000,
  B11100,
  B01001,
  B00110
};

const byte small_a_acute[8] PROGMEM = {
  0b00010,
  0b00100,
  0b00000,
  0b01110,
  0b00001,
  0b01111,
  0b10001,
  0b01111
};

const byte small_e_acute[8] PROGMEM = {
  0b00010,
  0b00100,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10000,
  0b01110
};  

const byte small_i_acute[8] PROGMEM = {
  0b00010,
  0b00100,
  0b00000,
  0b00100,
  0b01100,
  0b00100,
  0b00100,
  0b01110
};

const byte small_o_acute[8] PROGMEM = {
  0b00010,
  0b00100,
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

const byte small_u_diaeresis[8] PROGMEM = {
  0b01010,
  0b00000,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b01101
};

const byte small_u_acute[8] PROGMEM = {
  0b00010,
  0b00100,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b01101
};

const byte cap_n_tilde[8] PROGMEM = {
  0b01101,
  0b10010,
  0b00000,
  0b10001,
  0b11001,
  0b10101,
  0b10011,
  0b10001
};

//byte count=0;
//byte line=0;
 
void setup() //----( SETUP: RUNS ONCE )----/
{
Serial.begin(9600, SERIAL_8N1); // Used to type in characters
delay(100);

/* In this section I set the custom characters */
lcd.createChar(0, euro);
lcd.createChar(1,small_a_acute);
lcd.createChar(2,small_e_acute);
lcd.createChar(3,small_i_acute);
lcd.createChar(4,small_o_acute);
lcd.createChar(5,small_u_acute);
lcd.createChar(6,small_u_diaeresis);
lcd.createChar(7,cap_n_tilde);


lcd.begin(20,4); // initialize the lcd for 20 chars 4 lines and turn on backlight
lcd.setCursor(0,0); //Start at position of first line, first column.
lcd.clear(); //Clear the screen
}

void loop() //----( LOOP: RUNS CONSTANTLY )----/
{

// when characters arrive over the serial port...
if (Serial.available()) {
  // wait a bit for the entire message to arrive
  //delay(2);
  // clear the screen
  //lcd.clear();
  // read all the available characters
  while (Serial.available() > 0) {
    byte valor=Serial.read();
    switch(valor){
      //ignore the Carriage Return and Line Feed characters
      case 0xD:
        //lcd.write("CR");
        break;
      case 0xA:
        //lcd.write("LF");
        break;
        
      //I define a custom Command Character for Clear the LCD screen, this is used in Chromis POS.  
      case 0x10:
        lcd.clear();
        break;  
      
      //I define a custom Command Character for set the cursor in home position line 1 column 1 (line 0, column 0, using zero based indexing as the LiquidCrystal library) in the LCD screen, this is used in Chromis POS.  
      case 0x11:
        lcd.home();
        //lcd.setCursor(0,0);
        //count=0;
        break;
        
      //I define a custom Command Character for set the cursor in line 2 position (line 1, column 0) in the LCD screen, this is used in Chromis POS.  
      case 0x12:
        lcd.setCursor(0,1);
        break;

      //I define a custom Command Character for set the cursor in line 3 position (line 2, column 0) in the LCD screen, this is used in Chromis POS.    
      case 0x13:
        lcd.setCursor(0,2);
        break;  

      //I define a custom Command Character for set the cursor in line 4 position (line 3, column 0) in the LCD screen, this is used in Chromis POS.    
      case 0x14:
        lcd.setCursor(0,3);
        break;  

      //bypass values: unicode constants UTF-8 multibyte characters 
      case 0xc3:
      case 0xe2:
      case 0x82:
        //bypass
        break;
        
      //euro simbol  
      case 0xac: //Unicode UTF-8
        lcd.write(byte(0));
        break;

      //a tilde
      case 0xa1: //Unicode UTF-8
      case 0xe1: //ASCII 
        lcd.write(byte(1));
        break;

      //e tilde
      case 0xa9: //Unicode UTF-8
      case 0xe9: //ASCII 
        lcd.write(byte(2));
        break;

      //i tilde
      case 0xad: //Unicode UTF-8
      case 0xed: //ASCII 
        lcd.write(byte(3));
        break;        

      //o tilde
      case 0xb3: //Unicode UTF-8
      case 0xf3: //ASCII 
        lcd.write(byte(4));
        break;   

      //u tilde
      case 0xba: //Unicode UTF-8
      case 0xfa: //ASCII 
        lcd.write(byte(5));
        break; 

      //u diaeresis        
      case 0xbc: //Unicode UTF-8
      case 0xfc: //ASCII 
        lcd.write(byte(6));
        break;

      //small n tilde, N tilde translated as small n tilde       
      case 0xb1: //Unicode UTF-8
      case 0xf1: //ASCII 
      case 0x91: //Unicode UTF-8
      case 0xd1: //ASCII 
        lcd.write(byte(7));
        break;        

      //A tilde, bypass tilde use A
      case 0x81:
      case 0xc1: //ASCII 
        lcd.write('A');
        break;           

      //E tilde, bypass tilde use E
      case 0x89:
      case 0xc9: //ASCII
        lcd.write('E');
        break;  

      //I tilde, bypass tilde use I
      case 0x8d:
      case 0xcd: //ASCII
        lcd.write('I');
        break;  

      //O tilde, bypass tilde use O
      case 0x93:
      case 0xd3: //ASCII
        lcd.write('O');
        break;  

      //U tilde, bypass tilde use U
      case 0x9a:
      case 0xda: //ASCII
        lcd.write('U');
        break;  

      //U diaeresis, bypass diaresis use U
      case 0x9c:
      case 0xdc: //ASCII
        lcd.write('U');
        break;  
      
      default:
        // display character to the LCD, if it ins't a standard ASCII character can be displayed as japanese character because the Character ROM set used.
        lcd.write(valor);
        break;
    }
  }
}
}

