/* PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UPs
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE*/
#include <Cytron_PS2Shield.h>
Cytron_PS2Shield ps2(10,11);
#define r1 2
#define r2 3
#define r3 4
#define r4 5
void setup() {
   ps2.begin(9600); 
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  
}

void loop() {
 
 
 if(ps2.readButton(PS2_UP)==0)
 {
 
  Serial1.write('a');
 Serial.println('a');
 }
 else if(ps2.readButton(PS2_DOWN)==0)
 {
 
  Serial1.write('b');
 Serial.println('b');
 } 
  else if(ps2.readButton(PS2_LEFT)==0)
 {
 
  Serial1.write('c');
 Serial.println('c');
 }
  else if(ps2.readButton(PS2_RIGHT)==0)
 {
 
  Serial1.write('d');
 Serial.println('d');
 }
 else if(ps2.readButton(PS2_TRIANGLE)==0)
 {
 
  Serial1.write('e');
 Serial.println('e');
 }
 else if(ps2.readButton(PS2_CROSS)==0)
 {
 
  Serial1.write('k');
 Serial.println('k');
 }
 else if(ps2.readButton(PS2_SQUARE)==0)
 {
 
  Serial1.write('g');
 Serial.println('g');
 }
 else if(ps2.readButton(PS2_CIRCLE)==0)
 {
 
  Serial1.write('h');
 Serial.println('h');
 }
 else if(ps2.readButton(PS2_LEFT_1)==0)
 {
 
  Serial1.write('i');
 Serial.println('i');
 }
 else if(ps2.readButton(PS2_LEFT_2)==0)
 {
 
  Serial1.write('j');
 Serial.println('j');
 }
 else if(ps2.readButton(PS2_RIGHT_1)==0)
 {
  Serial1.write('f');
 Serial.println('f');
 digitalWrite(r1,0);
digitalWrite(r2,1);
digitalWrite(r3,1);
digitalWrite(r1,0);
 
 
 }
 else if(ps2.readButton(PS2_RIGHT_2)==0)
 {
 
  Serial1.write('l');
 Serial.println('l');
 digitalWrite(r1,1);
digitalWrite(r2,0);
digitalWrite(r3,0);
digitalWrite(r1,1);

 
 }
  else if(ps2.readButton(PS2_JOYSTICK_RIGHT)==0)
 {
 
  Serial1.write('m');
 Serial.println('m');
 }
 else
 {
  Serial1.write('z');
 Serial.println('z');
 digitalWrite(r1,0);
digitalWrite(r2,0);
digitalWrite(r3,0);
digitalWrite(r1,0);
 }
 
  // put your main code here, to run repeatedly:

}
