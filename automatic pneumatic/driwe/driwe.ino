#include <Servo.h>
Servo servo1;
Servo servo2;
#define pwm1 2
#define pwm2 3
#define pwm3 4
#define pwm4 5
#define pwm5 6
#define dir1 7
#define dir2 8
#define dir3 9
#define dir4 10
#define dir5 11
#define tr 12
#define a2bd 14.27
#define b2cd 10.29
#define c2bd 10.29
#define b2dd 6.42
#define d2ed 10.29
#define e2dd 10.29
#define d2fd 20.67
#define tr1 5000
#define tr2 5000
#define tr3 5000

int sp1=150;
int sp2=150;
int sp3=150;
int sp4=150;
int sp5=150;
int tspeed=50;

int encoderPin1 = 22;//1
int encoderPin2 = 23;//1
int encoderPin3 = 24;//2
int encoderPin4 = 25;//2
int encoderPin5 = 26;//3
int encoderPin6 = 27;//3
int encoderPin7 = 28;//4
int encoderPin8 = 29;//4
int encoderPin9 = 30;//5
int encoderPin10 = 31;//5


volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile int lastEncoded3 = 0;
volatile int lastEncoded4 = 0;
volatile int lastEncoded5 = 0;


volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile long encoderValue3 = 0;
volatile long encoderValue4 = 0;
volatile long encoderValue5 = 0;


long lastencoderValue1 = 0;
long lastencoderValue2 = 0;
long lastencoderValue3 = 0;
long lastencoderValue4 = 0;
long lastencoderValue5 = 0;


int lastMSB1 = 0;
int lastLSB1 = 0;
int lastMSB2 = 0;
int lastLSB2 = 0;
int lastMSB3 = 0;
int lastLSB3 = 0;
int lastMSB4 = 0;
int lastLSB4 = 0;
int lastMSB5 = 0;
int lastLSB5 = 0;


 volatile float   rev1=encoderValue1/12000;
 volatile float   rev2=encoderValue2/12000; 
 volatile float   rev3=encoderValue3/12000;
 volatile float   rev4=encoderValue4/12000; 
 volatile float   rev5=encoderValue5/12000;
 



const int trigPin1 = 32;//ultrasonic1
const int echoPin1 = 33;//us1
const int trigPin2 = 34;//us2
const int echoPin2 = 35;//us2
const int trigPin3 = 36;//ultrasonic1
const int echoPin3 = 37;//us1
const int trigPin4 = 38;//us2
const int echoPin4 = 39;//us2

long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
long duration3;//us1
int distance3;//us1
long duration4;//us2
int distance4;//us2

void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
 // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
Serial1.begin(9600);
  pinMode(2,OUTPUT);//1 pwm
   pinMode(3,OUTPUT); // 2 pwm
   pinMode(4,OUTPUT); // 3 pwm
   pinMode(5,OUTPUT);  // 4 pwm
   pinMode(6,OUTPUT);  // 5 pwm
  pinMode(7,OUTPUT);// 1 dir
   pinMode(8,OUTPUT);// 2 dir
   pinMode(9,OUTPUT);// 3 dir
   pinMode(10,OUTPUT); // 4 dir
   pinMode(11,OUTPUT);// 5 dir
     pinMode(12,OUTPUT); //  trow
pinMode(13,OUTPUT);
pinMode(14,OUTPUT);
   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
     pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
   
   pinMode(encoderPin1, INPUT); 
   pinMode(encoderPin2, INPUT);
   pinMode(encoderPin3, INPUT); 
  pinMode(encoderPin4, INPUT);
  pinMode(encoderPin5, INPUT); 
  pinMode(encoderPin6, INPUT);
  pinMode(encoderPin7, INPUT); 
  pinMode(encoderPin8, INPUT);
  pinMode(encoderPin9, INPUT); 
  pinMode(encoderPin10, INPUT);
 servo1.attach(13);
 servo2.attach(14);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin3, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin4, HIGH); //turn pullup resistor on
digitalWrite(encoderPin5, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin6, HIGH); //turn pullup resistor on
digitalWrite(encoderPin7, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin8, HIGH); //turn pullup resistor on
digitalWrite(encoderPin9, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin10, HIGH); //turn pullup resistor on


attachInterrupt(22, updateEncoder1, CHANGE); 
  attachInterrupt(23, updateEncoder1, CHANGE);
attachInterrupt(24, updateEncoder2, CHANGE); 
  attachInterrupt(25, updateEncoder2, CHANGE);
attachInterrupt(26, updateEncoder3, CHANGE); 
  attachInterrupt(27, updateEncoder3, CHANGE);
attachInterrupt(28, updateEncoder4, CHANGE); 
  attachInterrupt(29, updateEncoder4, CHANGE);
attachInterrupt(30, updateEncoder5, CHANGE); 
  attachInterrupt(31, updateEncoder5, CHANGE);

}
void leftturn()
{
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
  
}
void rightturn()
{
     analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
}
void a2b()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<a2bd)|abs(rev2<a2bd)|abs(rev3<a2bd)|abs(rev4<a2bd))
   {
    if(abs(rev1<a2bd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<a2bd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<a2bd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<a2bd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void b2c()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<b2cd)|abs(rev2<b2cd)|abs(rev3<b2cd)|abs(rev4<b2cd))
   {
    if(abs(rev1<b2cd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<b2cd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<b2cd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<b2cd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void c2b()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<c2bd)|abs(rev2<c2bd)|abs(rev3<c2bd)|abs(rev4<c2bd))
   {
    if(abs(rev1<c2bd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<c2bd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<c2bd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<c2bd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void b2d()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<b2dd)|abs(rev2<b2dd)|abs(rev3<b2dd)|abs(rev4<b2dd))
   {
    if(abs(rev1<b2dd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<b2dd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<b2dd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<b2dd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void d2e()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<d2ed)|abs(rev2<d2ed)|abs(rev3<d2ed)|abs(rev4<d2ed))
   {
    if(abs(rev1<d2ed))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<d2ed))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<d2ed))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<d2ed))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void e2d()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<e2dd)|abs(rev2<e2dd)|abs(rev3<e2dd)|abs(rev4<e2dd))
   {
    if(abs(rev1<e2dd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<e2dd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<e2dd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<e2dd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void d2f()
{
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    rev1=rev2=rev3=rev4=0;
   while(abs(rev1<d2fd)|abs(rev2<d2fd)|abs(rev3<d2fd)|abs(rev4<d2fd))
   {
    if(abs(rev1<d2fd))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(rev2<d2fd))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(rev3<d2fd))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(rev4<d2fd))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
  off();
}
void tr1()
{
  encoderValue5=0;
  servo2.write(0);
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>tr1)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
}
void tr2()
{
  encoderValue5=0;
   servo2.write(0);
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>tr2)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
}
void tr3()
{
  encoderValue5=0;
   servo2.write(0);
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>tr3)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
}
void grip()
{
  
 servo1.write(90);
digitalWrite(dir5,1);
 analogWrite(pwm5,50);
 delay(500);
  encoderValue5=0;
 digitalWrite(tr,1);
 delay(50);
 forward(100);
  digitalWrite(tr,0);
  delay(50);
  backward();
  delay(100);
 
   servo1.write(0); 
   servo2.write(90);
   while(abs(encoderValue5)<4000)
   {
     digitalWrite(dir5,1);
 analogWrite(pwm5,50);
   }
   
   
}
void off()
{
  analogWrite(pwm1,0);//m1
  analogWrite(pwm2,0);//m1
  analogWrite(pwm3,0);//m1
  analogWrite(pwm4,0);//m1
  analogWrite(pwm5,0);//m1
   digitalWrite(tr,0);//magnet
  
}
long us1()
{
  digitalWrite(trigPin1, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);

// Calculating the distance
distance1= duration1*0.034/2;
  return(distance1);
}
long us2()
{
  digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
distance2= duration2*0.034/2;
  return(distance2);
}
long us3()
{
  digitalWrite(trigPin3, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration3 = pulseIn(echoPin3, HIGH);

// Calculating the distance
distance3= duration3*0.034/2;
  return(distance3);
}
long us4()
{
  digitalWrite(trigPin4, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration4 = pulseIn(echoPin4, HIGH);

// Calculating the distance
distance4= duration4*0.034/2;
  return(distance4);
}
void calib1()
{
  long d1=us1();
  long d2=us2();
  while(d1>300&d2>300)
  {
    left();
  }
  while(d1<200&d2<200)
  {
    right();
  }
  if(d1<300&d1>200)
  int i=1;
   if(d2<300&d2>200)
  int j=1;
 while(abs(d1-d2)>5&i==1&j==1)
 {
  if(d1>d2)
 { leftturn();
 delay(50);
 }
  if(d2>d1)
 { rightturn();
   delay(50);
 }
   }
 off();
}
void calib2()
{
  long d1=us3();
  long d2=us4();
    while(d1>300&d2>300)
  {
    forward();
  }
  while(d1<200&d2<200)
  {
    backward();
  }
  if(d1<300&d1>200)
  int i=1;
   if(d2<300&d2>200)
  int j=1;
  
     while(abs(d1-d2)>5&i==1&j==1)
     {
       if(d1>d2)
       { rightturn();
         delay(50);
       }
       if(d2>d1)
       { leftturn();
       delay(50);
       }
   }
  
 off();
}
void forward()
{
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
  
  
}
void backward()
{
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
  
  
}
void loop() {
  
  a2b();
  calib1();
  calib2();
  grip();
  b2c();
   calib2();
  tr1();
  c2b();
   calib1();
  b2d();
   calib1();
    calib2();
  grip();
  d2e();
   calib2();
   tr2();
   e2d();
   calib1();
   calib2();
  grip();
  d2f():
  calib2();
  tr3();
    
  
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
  void updateEncoder4()
  {
  int MSB4 = digitalRead(encoderPin7); //MSB = most significant bit
  int LSB4 = digitalRead(encoderPin8); //LSB = least significant bit

  int encoded4 = (MSB4 << 1) |LSB4; //converting the 2 pin value to single number
  int sum4  = (lastEncoded4 << 2) | encoded4; //adding it to the previous encoded value

  if(sum4 == 0b1101 || sum4 == 0b0100 || sum4 == 0b0010 || sum4 == 0b1011) encoderValue4 ++;
  if(sum4 == 0b1110 || sum4 == 0b0111 || sum4 == 0b0001 || sum4 == 0b1000) encoderValue4 --;

  lastEncoded4 = encoded4; //store this value for next time 
  }
  void updateEncoder5()
  {
  int MSB5 = digitalRead(encoderPin9); //MSB = most significant bit
  int LSB5 = digitalRead(encoderPin10); //LSB = least significant bit

  int encoded5 = (MSB5 << 1) |LSB5; //converting the 2 pin value to single number
  int sum5  = (lastEncoded5 << 2) | encoded5; //adding it to the previous encoded value

  if(sum5 == 0b1101 || sum5 == 0b0100 || sum5 == 0b0010 || sum5 == 0b1011) encoderValue5 ++;
  if(sum5 == 0b1110 || sum5 == 0b0111 || sum5 == 0b0001 || sum5 == 0b1000) encoderValue5 --;

  lastEncoded5 = encoded5; //store this value for next time
  }
  void updateEncoder6()
  {
  int MSB6 = digitalRead(encoderPin11); //MSB = most significant bit
  int LSB6 = digitalRead(encoderPin12); //LSB = least significant bit

  int encoded6 = (MSB6 << 1) |LSB6; //converting the 2 pin value to single number
  int sum6  = (lastEncoded6 << 2) | encoded6; //adding it to the previous encoded value

  if(sum6 == 0b1101 || sum6 == 0b0100 || sum6 == 0b0010 || sum6 == 0b1011) encoderValue6 ++;
  if(sum6 == 0b1110 || sum6 == 0b0111 || sum6 == 0b0001 || sum6 == 0b1000) encoderValue6 --;

  lastEncoded6 = encoded6; //store this value for next time
  }
