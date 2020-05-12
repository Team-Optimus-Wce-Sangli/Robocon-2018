

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

 // SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial
int pwm1=195;
int pwm2=190;
int pwm3=200;
int pwm4=202;
int pwm5=200;
int pwm6=50;
int tspeed=50;

int encoderPin1 = 16;//1
int encoderPin2 = 17;//1
int encoderPin3 = 18;//2
int encoderPin4 = 19;//2
int encoderPin5 = 20;//3
int encoderPin6 = 21;//3
int encoderPin7 = 22;//4
int encoderPin8 = 23;//4
int encoderPin9 = 24;//5
int encoderPin10 = 25;//5
int encoderPin11 = 26;//6
int encoderPin12 = 27;//6

volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile int lastEncoded3 = 0;
volatile int lastEncoded4 = 0;
volatile int lastEncoded5 = 0;
volatile int lastEncoded6 = 0;

volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile long encoderValue3 = 0;
volatile long encoderValue4 = 0;
volatile long encoderValue5 = 0;
volatile long encoderValue6 = 0;

long lastencoderValue1 = 0;
long lastencoderValue2 = 0;
long lastencoderValue3 = 0;
long lastencoderValue4 = 0;
long lastencoderValue5 = 0;
long lastencoderValue6 = 0;
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
int lastMSB6 = 0;
int lastLSB6 = 0;

 volatile float rev1=encoderValue1/12000;
 volatile float   rev2=encoderValue2/12000; 
 volatile float   rev3=encoderValue3/12000;
 volatile float   rev4=encoderValue4/12000; 
 volatile float   rev5=encoderValue5/12000;
 volatile float   rev6=encoderValue6/12000;


int pos=0;
const int trigPin1 = 30;//us1
const int echoPin1 = 31;//us1
const int trigPin2 = 32;//us2
const int echoPin2 = 33;//us2
long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
  ps2.begin(115200); // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(115200);
  pinMode(2,OUTPUT);//1 pwm
   pinMode(3,OUTPUT); // 2 pwm
   pinMode(4,OUTPUT); // 3 pwm
   pinMode(5,OUTPUT);  // 4 pwm
   pinMode(6,OUTPUT);  // 5 pwm
   pinMode(7,OUTPUT); // 6 pwm
   pinMode(8,OUTPUT); //  magnet
   pinMode(9,OUTPUT);// 1 dir
   pinMode(10,OUTPUT);// 2 dir
   pinMode(11,OUTPUT);// 3 dir
   pinMode(12,OUTPUT); // 4 dir
   pinMode(13,OUTPUT);// 5 dir
   pinMode(14,OUTPUT); // 6 dir
   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
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
  pinMode(encoderPin11, INPUT); 
  pinMode(encoderPin12, INPUT);

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
digitalWrite(encoderPin11, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin12, HIGH); //turn pullup resistor on

attachInterrupt(16, updateEncoder1, CHANGE); 
  attachInterrupt(17, updateEncoder1, CHANGE);
attachInterrupt(18, updateEncoder2, CHANGE); 
  attachInterrupt(19, updateEncoder2, CHANGE);
attachInterrupt(20, updateEncoder3, CHANGE); 
  attachInterrupt(21, updateEncoder3, CHANGE);
attachInterrupt(22, updateEncoder4, CHANGE); 
  attachInterrupt(23, updateEncoder4, CHANGE);
attachInterrupt(24, updateEncoder5, CHANGE); 
  attachInterrupt(25, updateEncoder5, CHANGE);
attachInterrupt(26, updateEncoder6, CHANGE); 
  attachInterrupt(27, updateEncoder6, CHANGE);
 
}
void forward()
{
    analogWrite(2,pwm1);//m1
    analogWrite(3,pwm2);//m2
    analogWrite(4,pwm3);//m3
    analogWrite(5,pwm4);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,0);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,1);//m4
  
}
void backward()
{
    analogWrite(2,pwm1);//m1
    analogWrite(3,pwm2);//m2
    analogWrite(4,pwm3);//m3
    analogWrite(5,pwm4);//m4
    digitalWrite(9,0);//m1
    digitalWrite(10,1);//m2
    digitalWrite(11,1);//m3
    digitalWrite(12,0);//m4
  
}
void left()
{
    analogWrite(2,pwm1);//m1
    analogWrite(3,pwm2);//m2
    analogWrite(4,pwm3);//m3
    analogWrite(5,pwm4);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,1);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,1);//m4
  
}
void right()
{
    analogWrite(2,pwm1);//m1
    analogWrite(3,pwm2);//m2
    analogWrite(4,pwm3);//m3
    analogWrite(5,pwm4);//m4
    digitalWrite(9,0);//m1
    digitalWrite(10,0);//m2
    digitalWrite(11,1);//m3
    digitalWrite(12,1);//m4
  
}

void leftturn()
{
    analogWrite(2,tspeed);//m1
    analogWrite(3,tspeed);//m2
    analogWrite(4,0);//m3
    analogWrite(5,0);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,1);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,1);//m4
  
}
void rightturn()
{
    analogWrite(2,0);//m1
    analogWrite(3,0);//m2
    analogWrite(4,tspeed);//m3
    analogWrite(5,tspeed);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,0);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,0);//m4
}
void up()
{
   analogWrite(6,pwm5);//m5
   digitalWrite(13,1);//m5
}
void down()
{
   analogWrite(6,pwm5);//m5
   digitalWrite(13,0);//m5
}
void index()
{
  long encoderValue61=encoderValue6;
  long encoderValue62=0;
  while(encoderValue62<encoderValue61+600)
  {
   analogWrite(7,pwm6);//m6
   digitalWrite(14,0);//m6
   encoderValue62=encoderValue6;
  }
  analogWrite(7,0);//m6 
  pos=pos+1;
  
}
void grip()
{
  digitalWrite(8,1);//magnet
}
void ungrip()
{
  digitalWrite(8,0);//magnet
}
void off()
{
  analogWrite(2,0);//m1
  analogWrite(3,0);//m1
  analogWrite(4,0);//m1
  analogWrite(5,0);//m1
  analogWrite(6,0);//m1
  analogWrite(7,0);//m1
  digitalWrite(8,0);//magnet
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
void calib()
{
  long d1=us1();
  long d2=us2();
  if(d1>100&d2>100)
  {
   left();
   delay(200);
  }
  else
  {
    if(d1<100&d2>100)
    {leftturn();
    delay(200);}
    if(d1>100&d2<100)
    {rightturn();
    delay(200);
    }
    if(d1<100&d2<100)
    {
      off();
    }
   }
  
}
void loop()
{
   if(Serial.available())
   {
    char s=Serial.read();
    switch(s)
    {
      case 'a':
      {
        forward();
        
        break;
      }
      case 'b':
      {
        backward();
        break;
      }
      case 'c':
      {
        left();
        break;
      }
      case 'd':
      {
        right();
        break;
      }
      case 'e':
      {
        up();
        break;
      }
      case 'f':
      {
        down();
        break;
      }
      case 'g':
      {
        index();
        break;
      }
      case 'h':
      {
        grip();
        break;
      }
      case 'i':
      {
        ungrip();
        break;
      }
      case 'k':
      {
        calib();
        break;
      }
      default :
      {
        off();
        break;
      }
    }
    
   }
  
  
 
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
