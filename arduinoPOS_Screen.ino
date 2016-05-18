#include <LiquidCrystalFast.h>

//#include <LiquidCrystal.h>



/*************************************************************************************
 
  Mark Bramwell, July 2010
 
  This program will test the LCD panel and the buttons.When you push the button on the shield，
  the screen will show the corresponding one.
  
  Connection: Plug the LCD Keypad to the UNO(or other controllers)
 
**************************************************************************************/
 

//LiquidCrystal lcd(2, 4,8, 9, 10, 11);           // select the pins used on the LCD panel
LiquidCrystalFast lcd(12, 10, 11, 5, 4, 3, 2);

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
lcd.createChar(0, euro);
lcd.createChar(1,small_a_acute);
lcd.createChar(2,small_e_acute);
lcd.createChar(3,small_i_acute);
lcd.createChar(4,small_o_acute);
lcd.createChar(5,small_u_acute);
lcd.createChar(6,small_u_diaeresis);
lcd.createChar(7,cap_n_tilde);

lcd.begin(20,4); // initialize the lcd for 20 chars 4 lines and turn on backlight
//lcd.backlight();
lcd.setCursor(0,0); //Start at character 4 on line 0
lcd.clear();
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
      case 0xD:
        //lcd.write("CR");
        break;
      case 0xA:
        //lcd.write("LF");
        break;
      case 0x10:
        lcd.clear();
        break;  
      case 0x11:
        lcd.home();
        //lcd.setCursor(0,0);
        //count=0;
        break;
      case 0x12:
        lcd.setCursor(0,1);
        break;
      case 0x13:
        lcd.setCursor(0,2);
        break;  
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
      case 0xac:
        lcd.write(byte(0));
        break;

      //a tilde
      case 0xa1:
      case 0xe1: //ASCII 
        lcd.write(byte(1));
        break;

      //e tilde
      case 0xa9:
      case 0xe9: //ASCII 
        lcd.write(byte(2));
        break;

      //i tilde
      case 0xad:
      case 0xed: //ASCII 
        lcd.write(byte(3));
        break;        

      //o tilde
      case 0xb3:
      case 0xf3: //ASCII 
        lcd.write(byte(4));
        break;   

      //u tilde
      case 0xba:
      case 0xfa: //ASCII 
        lcd.write(byte(5));
        break; 

      //u diaeresis        
      case 0xbc:
      case 0xfc: //ASCII 
        lcd.write(byte(6));
        break;

      //n tilde N tilde       
      case 0xb1:
      case 0xf1: //ASCII 
      case 0x91:
      case 0xd1: //ASCII 
        lcd.write(byte(7));
        break;        

      //N tilde        

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
        // display each character to the LCD
        lcd.write(valor);
        break;
    }
//    if(count==16){
//      count=0;
//      line++;
//      lcd.setCursor(0,line%2);
//    }      
//    if(line ==2){
//      line=0;
//      lcd.clear();
//    }
  }
  
}
  //delay(80);
}

