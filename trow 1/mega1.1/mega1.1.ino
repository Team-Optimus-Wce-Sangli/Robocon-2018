
#include<Servo.h>
Servo clamp;
char button;
int sp=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
clamp.attach(6);

}

void loop() {
  // put your main code here, to run repeatedly:

  button=Serial.read();
  if(button=='A')
  {
    sp=sp+5;
    if(sp>255)
    sp=255;
  }
   if(button=='B')
  {
    sp=sp-5;
    if(sp<0)
    sp=0;
  }
   if(button=='C')
  {
    sp=150;
    //clamp.write(0);
  }
   if(button=='D')
  {
   // clamp.write(30);
  }
   if(button=='E')
  {
    sp=0;
  }
  digitalWrite(3,HIGH);
 
  analogWrite(5,sp);
  Serial.println(sp);
  
}
