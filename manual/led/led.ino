#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address

//LiquidCrystal_I2C lcd(0x38, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address


// Creat a set of new characters


void setup()
{
//   int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));

  // Switch on the backlight
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN,0);
  
             // initialize the lcd 

 

 
}

void loop()
{
  // lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");  
//  lcd.setCursor ( 0, 1 );        // go to the next line
//  lcd.print (" FORUM - fm   ");
 // delay ( 1000 );
}
