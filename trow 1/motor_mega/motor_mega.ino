#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(10,11);

int sp=0;
void setup() {
  // put your setup code here, to run once:
 ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ps2.readButton(PS2_UP) == 0) // 0 = pressed, 1 = released
  {
   sp=sp+5;
   delay(200);
  }
    if(ps2.readButton(PS2_DOWN) == 0) // 0 = pressed, 1 = released
  {
    sp=sp-5;
   delay(200);
  }
    if(ps2.readButton(PS2_RIGHT_1) == 0) // 0 = pressed, 1 = released
  {
    sp=0;
   delay(200);
  }
  digitalWrite(8,HIGH);
    
      analogWrite(9,sp);
      Serial.println(sp);
}
