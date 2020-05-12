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
// 14 to 15 of mega2
//15 to 14 of mega2

# define m1pwm 4;
# define m2pwm 5;
# define m3pwm 6;
# define m1dir 7;
# define m2dir 8;
# define m3dir 9;

int encoderPin1 = 2;//1
int encoderPin2 = 3;//1
int encoderPin3 = 18;//2
int encoderPin4 = 19;//2
int encoderPin5 = 20;//3
int encoderPin6 = 21;//3
int pwm1=100;
int pwm2=100;
int pwm2=100;
int tspeed=50;

volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile int lastEncoded3 = 0;
volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile long encoderValue3 = 0;
long lastencoderValue1 = 0;
long lastencoderValue2 = 0;
long lastencoderValue3 = 0;
int lastMSB1 = 0;
int lastLSB1 = 0;
int lastMSB2 = 0;
int lastLSB2 = 0;
int lastMSB3 = 0;
int lastLSB3 = 0;
 volatile float   rev1=encoderValue1/9840; 
 volatile float   rev2=encoderValue2/9840;
 volatile float   rev3=encoderValue3/9840;

void setup() {
   ps2.begin(9600); 
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);
   pinMode(m1pwm,OUTPUT);//1 pwm
   pinMode(m2pwm,OUTPUT); // 2 pwm
   pinMode(m3pwm,OUTPUT); // 3 pwm
    pinMode(m1dir,OUTPUT);// 1 dir
   pinMode(m2dir,OUTPUT);// 2 dir
   pinMode(m3dir,OUTPUT);// 3 dir
   pinMode(encoderPin1, INPUT); 
   pinMode(encoderPin2, INPUT);
   pinMode(encoderPin3, INPUT); 
  pinMode(encoderPin4, INPUT);
  pinMode(encoderPin5, INPUT); 
  pinMode(encoderPin6, INPUT);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin3, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin4, HIGH); //turn pullup resistor on
digitalWrite(encoderPin5, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin6, HIGH); //turn pullup resistor on
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder1, CHANGE);
attachInterrupt(digitalPinToInterrupt(18), updateEncoder2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(19), updateEncoder2, CHANGE);
attachInterrupt(digitalPinToInterrupt(20), updateEncoder3, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(21), updateEncoder3, CHANGE);
}
void off()
{
  analogWrite(m1pwm,0);//m1
  analogWrite(m2pwm,0);//m2
  analogWrite(m3pwm,0);//m3
}
void forwardd()
{
  
}
void forward()
{
    analogWrite(m1pwm,pwm1);//m1
    analogWrite(m2pwm,pwm2);//m2
    analogWrite(m3pwm,pwm3);//m3
    
    digitalWrite(m1dir,0);//m1
    digitalWrite(m2dir,1);//m2
    digitalWrite(m3dir,1);//m3
    
  
}
void backward()
{
    analogWrite(m1pwm,pwm1);//m1
    analogWrite(m2pwm,pwm2);//m2
    analogWrite(m3pwm,pwm3);//m3
    
    digitalWrite(m1dir,1);//m1
    digitalWrite(m2dir,0);//m2
    digitalWrite(m3dir,0);//m3
  
}
void left()
{
    analogWrite(m1pwm,pwm1);//m1
    analogWrite(m2pwm,pwm2);//m2
    analogWrite(m3pwm,pwm3);//m3
    
    digitalWrite(m1dir,0);//m1
    digitalWrite(m2dir,0);//m2
    digitalWrite(m3dir,1);//m3
  
}
void right()
{
    analogWrite(m1pwm,pwm1);//m1
    analogWrite(m2pwm,pwm2);//m2
    analogWrite(m3pwm,pwm3);//m3
    
    digitalWrite(m1dir,0);//m1
    digitalWrite(m2dir,0);//m2
    digitalWrite(m3dir,1);//m3
  
}

void leftturn()
{
    analogWrite(m1pwm,tspeed);//m1
    analogWrite(m2pwm,tspeed);//m2
    analogWrite(m3pwm,tspeed);//m3
    
    digitalWrite(m1dir,0);//m1
    digitalWrite(m2dir,0);//m2
    digitalWrite(m3dir,0);//m3
  
}
void rightturn()
{
    analogWrite(m1pwm,tspeed);//m1
    analogWrite(m2pwm,tspeed);//m2
    analogWrite(m3pwm,tspeed);//m3
    
    digitalWrite(m1dir,1);//m1
    digitalWrite(m2dir,1);//m2
    digitalWrite(m3dir,1);//m3
}
void loop() {
 
 
 if(ps2.readButton(PS2_UP)==0)
 {
 
  Serial3.write('a');
 Serial.println('a');
 forward();
 }
 else if(ps2.readButton(PS2_DOWN)==0)
 {
 
  Serial3.write('b');
 Serial.println('b');
 backward();
 } 
  else if(ps2.readButton(PS2_LEFT)==0)
 {
 
  Serial3.write('c');
 Serial.println('c');
 left();
 }
  else if(ps2.readButton(PS2_RIGHT)==0)
 {
 
  Serial3.write('d');
 Serial.println('d');
 right();
 }
 else if(ps2.readButton(PS2_TRIANGLE)==0)
 {
 
  Serial3.write('e');
 Serial.println('e');
 }
 else if(ps2.readButton(PS2_CROSS)==0)
 {
 
  Serial3.write('f');
 Serial.println('f');
 }
 else if(ps2.readButton(PS2_SQUARE)==0)
 {
 
  Serial3.write('g');
 Serial.println('g');
 leftturn();
 }
 else if(ps2.readButton(PS2_CIRCLE)==0)
 {
 
  Serial3.write('h');
 Serial.println('h');
 rightturn();
 }
 else if(ps2.readButton(PS2_LEFT_1)==0)
 {
 
  Serial3.write('i');
 Serial.println('i');
 }
 else if(ps2.readButton(PS2_LEFT_2)==0)
 {
 
  Serial3.write('j');
 Serial.println('j');
 }
 else if(ps2.readButton(PS2_RIGHT_1)==0)
 {
 
  Serial3.write('k');
 Serial.println('k');
 }
 else
 {
  Serial3.write('z');
 Serial.println('z');
 off();
 }
 
  // put your main code here, to run repeatedly:

}

void updateEncoder1()
{
  int MSB1 = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB1 = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded1 = (MSB1 << 1) |LSB1; //converting the 2 pin value to single number
  int sum1  = (lastEncoded1 << 2) | encoded1; //adding it to the previous encoded value

  if(sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011) encoderValue1 ++;
  if(sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000) encoderValue1 --;

  lastEncoded1 = encoded1; //store this value for next time
}
 void updateEncoder2()
 {
  int MSB2 = digitalRead(encoderPin3); //MSB = most significant bit
  int LSB2 = digitalRead(encoderPin4); //LSB = least significant bit

  int encoded2 = (MSB2 << 1) |LSB2; //converting the 2 pin value to single number
  int sum2  = (lastEncoded2 << 2) | encoded2; //adding it to the previous encoded value

  if(sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) encoderValue2 ++;
  if(sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) encoderValue2 --;

  lastEncoded2 = encoded2; //store this value for next time
 }
  void updateEncoder3()
  {
  int MSB3 = digitalRead(encoderPin5); //MSB = most significant bit
  int LSB3 = digitalRead(encoderPin6); //LSB = least significant bit

  int encoded3 = (MSB3 << 1) |LSB3; //converting the 2 pin value to single number
  int sum3  = (lastEncoded3 << 2) | encoded3; //adding it to the previous encoded value

  if(sum3 == 0b1101 || sum3 == 0b0100 || sum3 == 0b0010 || sum3 == 0b1011) encoderValue3 ++;
  if(sum3 == 0b1110 || sum3 == 0b0111 || sum3 == 0b0001 || sum3 == 0b1000) encoderValue3 --;

  lastEncoded3 = encoded3; //store this value for next time
  }
