#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(10,11);

int sp=0;
void setup() {
  // put your setup code here, to run once:
 ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ps2.readButton(PS2_UP) == 0) // 0 = pressed, 1 = released
  {
   digitalWrite(2,LOW);
   analogWrite(3,255);
    digitalWrite(4,HIGH);
   analogWrite(5,255);
    digitalWrite(6,HIGH);
   analogWrite(7,255);
    digitalWrite(8,LOW);
   analogWrite(9,255);
   delay(200);
  }
    if(ps2.readButton(PS2_DOWN) == 0) // 0 = pressed, 1 = released
  {
     digitalWrite(2,1);
   analogWrite(3,255);
    digitalWrite(4,0);
   analogWrite(5,255);
    digitalWrite(6,0);
   analogWrite(7,255);
    digitalWrite(8,1);
   analogWrite(9,255);
   delay(200);
  }
    if(ps2.readButton(PS2_RIGHT) == 0) // 0 = pressed, 1 = released
  {
        digitalWrite(2,1);
   analogWrite(3,255);
    digitalWrite(4,1);
   analogWrite(5,255);
    digitalWrite(6,0);
   analogWrite(7,255);
    digitalWrite(8,0);
   analogWrite(9,255);
   delay(200);
  }
 if(ps2.readButton(PS2_LEFT) == 0) // 0 = pressed, 1 = released
  {
        digitalWrite(2,0);
   analogWrite(3,255);
    digitalWrite(4,0);
   analogWrite(5,255);
    digitalWrite(6,1);
   analogWrite(7,255);
    digitalWrite(8,1);
   analogWrite(9,255);
   delay(200);
  } 
    if(ps2.readButton(PS2_RIGHT_1) == 0) // 0 = pressed, 1 = released
  {
     digitalWrite(2,0);
   analogWrite(3,0);
    digitalWrite(4,0);
   analogWrite(5,0);
    digitalWrite(6,1);
   analogWrite(7,0);
    digitalWrite(8,1);
   analogWrite(9,0);
   delay(200);
  }
}
