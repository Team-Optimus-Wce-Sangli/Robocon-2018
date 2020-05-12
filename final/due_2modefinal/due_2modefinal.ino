#include <PID_v1.h>

#include <PID_v1.h>
#include <Servo.h>
int s0=0;
int s90=0;
Servo flaps; 
int flap=90;
#define start 50 
#define pwm1 13
#define pwm2 11
#define pwm3 8
#define pwm4 6
#define pwm6 2//grip
#define pwm5 4//index
#define pwm7 20//lead
#define dir1 12
#define dir2 10
#define dir3 9
#define dir4 7
#define dir6 3
#define dir5 5
#define dir7 21//lead
#define mag 14
#define a2bd 140416
#define b2cd 101253
#define c2bd 101253
#define b2dd 63172
#define d2ed 101253
#define e2dd 101253
#define d2fd 203392
int m=1;
int sp1m=200;
int sp2m=200;
int sp3m=200;
int sp4m=200;
int sp12m=70;
int sp22m=70;
int sp32m=70;
int sp42m=70;
int sp1=50;
int sp2=50;
int sp3=50;
int sp4=50;
int sp12=50;
int sp22=50;
int sp32=50;
int sp42=50;
int tspeed=30;
int tspeedm=100;
int tspeed2m=70;
int sp5=200;
int sp6=50;
int sp7=100;

int i=0;
int j=0;
int s=0;



int encoderPin1 = 58;//1
int encoderPin2 = 59;//1
int encoderPin3 = 60;//2
int encoderPin4 = 61;//2
int encoderPin5 = 62;//3
int encoderPin6 = 63;//3
int encoderPin7 = 64;//4
int encoderPin8 = 65;//4
int encoderPin9 = 66;//5
int encoderPin10 = 67;//5
int encoderPin11 = 68;//6
int encoderPin12 = 69;//6

volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile int lastEncoded3 = 0;
volatile int lastEncoded4 = 0;
volatile int lastEncoded5 = 0;
volatile int lastEncoded6 = 0;

  double encoderValue1 = 0;
  double encoderValue2 = 0;
 double encoderValue3 = 0;
 double encoderValue4 = 0;
  double encoderValue5 = 0;
  double encoderValue6 = 0;

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
int pos=0;
const int trigPin1 = 16;//ultrasonic1
const int echoPin1 = 17;//us1
const int trigPin2 = 20;//us2
const int echoPin2 = 21;//us2
long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
double pwm_val1=0;
double pwm_val2=0;
double pwm_val3=0;
double pwm_val4=0;
double Kp=0.1;
double Ki=0.05;
double Kd=0.001;

double reqd_pos1 =0;
double reqd_pos2 =0;
double reqd_pos3 =0;
double reqd_pos4 =0;

PID myPID1(&encoderValue1,&pwm_val1,&reqd_pos1,Kp,Ki,Kd, DIRECT);
PID myPID2(&encoderValue2,&pwm_val2,&reqd_pos2, Kp, Ki, Kd, DIRECT);
PID myPID3(&encoderValue3,&pwm_val3,&reqd_pos3,Kp,Ki,Kd,DIRECT);
PID myPID4(&encoderValue4,&pwm_val4,&reqd_pos4,Kp,Ki,Kd,DIRECT);
void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
 // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
Serial1.begin(9600);
 flaps.attach(17);
    myPID1.SetMode(AUTOMATIC);
    myPID1.SetOutputLimits(-100,100);
   myPID1.SetSampleTime(1);
    myPID2.SetMode(AUTOMATIC);
   myPID2.SetOutputLimits(-100,100);
   myPID2.SetSampleTime(1);
    myPID3.SetMode(AUTOMATIC);
   myPID3.SetOutputLimits(-100,100);
   myPID3.SetSampleTime(1);
    myPID4.SetMode(AUTOMATIC);
    myPID4.SetOutputLimits(-100,100);
    myPID4.SetSampleTime(1);
  pinMode(pwm1,OUTPUT);//1 pwm
   pinMode(pwm2,OUTPUT); // 2 pwm
   pinMode(pwm3,OUTPUT); // 3 pwm
   pinMode(pwm4,OUTPUT);  // 4 pwm
   pinMode(pwm6,OUTPUT);  // 5 pwm
   pinMode(pwm5,OUTPUT); // 6 pwm
   pinMode(mag,OUTPUT); //  magnet
   pinMode(dir1,OUTPUT);// 1 dir
   pinMode(dir2,OUTPUT);// 2 dir
   pinMode(dir3,OUTPUT);// 3 dir
   pinMode(dir4,OUTPUT); // 4 dir
   pinMode(dir5,OUTPUT);// 5 dir
   pinMode(17,OUTPUT);
   pinMode(dir6,OUTPUT); // 6 dir
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

  attachInterrupt(encoderPin1, updateEncoder1, CHANGE); 
  attachInterrupt(encoderPin2, updateEncoder1, CHANGE);
  attachInterrupt(encoderPin3, updateEncoder2, CHANGE); 
  attachInterrupt(encoderPin4, updateEncoder2, CHANGE);
  attachInterrupt(encoderPin5, updateEncoder3, CHANGE); 
  attachInterrupt(encoderPin6, updateEncoder3, CHANGE);
  attachInterrupt(encoderPin7, updateEncoder4, CHANGE); 
  attachInterrupt(encoderPin8, updateEncoder4, CHANGE);
  attachInterrupt(encoderPin9, updateEncoder5, CHANGE); 
  attachInterrupt(encoderPin10, updateEncoder5, CHANGE);
  attachInterrupt(encoderPin11, updateEncoder6, CHANGE); 
  attachInterrupt(encoderPin12, updateEncoder6, CHANGE);
 digitalWrite(mag,0);
 flap90();
}
void forward1()
{   digitalWrite(dir1,0);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
    sp1=sp1+1;
    if(sp1>sp1m)
    sp1=sp1m;
   sp2=sp2+1;
    if(sp2>sp2m)
    sp2=sp2m;
    sp3=sp3+1;
    if(sp3>sp3m)
    sp3=sp3m;
    sp4=sp4+1;
    if(sp4>sp4m)
    sp4=sp4m;
    analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
//Serial.print("sp1=");Serial.print(sp1);Serial.print("//");Serial.print("sp2=");Serial.print(sp2);Serial.print("//");Serial.print("sp3=");Serial.print(sp3);Serial.print("//");Serial.print("sp4=");Serial.print(sp4);Serial.println("//");
  
}
void backward1()
{

    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    sp1=sp1+1;
    if(sp1>sp1m)
    sp1=sp1m;
   sp2=sp2+1;
    if(sp2>sp2m)
    sp2=sp2m;
    sp3=sp3+1;
    if(sp3>sp3m)
    sp3=sp3m;
    sp4=sp4+1;
    if(sp4>sp4m)
    sp4=sp4m;
    analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4

  
}
void left1()
{

    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
    sp1=sp1+1;
    if(sp1>sp1m)
    sp1=sp1m;
   sp2=sp2+1;
    if(sp2>sp2m)
    sp2=sp2m;
    sp3=sp3+1;
    if(sp3>sp3m)
    sp3=sp3m;
    sp4=sp4+1;
    if(sp4>sp4m)
    sp4=sp4m;
    analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4

  
}
void right1()
{
 
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
    sp1=sp1+1;
    if(sp1>sp1m)
    sp1=sp1m;
   sp2=sp2+1;
    if(sp2>sp2m)
    sp2=sp2m;
    sp3=sp3+1;
    if(sp3>sp3m)
    sp3=sp3m;
    sp4=sp4+1;
    if(sp4>sp4m)
    sp4=sp4m;
    analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4

}

void leftturn1()
{    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
    tspeed=tspeed+1;
    if(tspeed>tspeedm)
    sp1=sp1m;
 
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
    analogWrite(pwm3,tspeed);//m3
    analogWrite(pwm4,tspeed);//m4
  
}
void rightturn1()
{
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
    tspeed=tspeed+1;
    if(tspeed>tspeedm)
    sp1=sp1m;
 
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
    analogWrite(pwm3,tspeed);//m3
    analogWrite(pwm4,tspeed);//m4
  
}
void forward2()
{ 
  reqd_pos1 -=60;
  reqd_pos2 +=60;
   reqd_pos3 +=60;
  reqd_pos4 +=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);
 
}
void backward2()
{

  reqd_pos1 +=60;
reqd_pos2 -=60;
 reqd_pos3 -=60;
reqd_pos4 -=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);
 //  delay(600);

  
}
void left2()
{

       reqd_pos1 -=60;
reqd_pos2 -=60;
 reqd_pos3 +=60;
reqd_pos4 -=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);
   //delay(600);

  
}
void right2()
{
 
  reqd_pos1 +=60;
reqd_pos2 +=60;
 reqd_pos3 -=60;
reqd_pos4 +=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);
//delay(600);
}

void leftturn2()
{  reqd_pos1 -=60;
reqd_pos2 -=60;
 reqd_pos3 -=60;
reqd_pos4 +=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);
  
}
void rightturn2()
{
   reqd_pos1 +=60;
reqd_pos2 +=60;
 reqd_pos3 +=60;
reqd_pos4 -=60;

   myPID1.Compute();
   setPWM1(pwm_val1);
     myPID2.Compute();
   setPWM2(pwm_val2);
     myPID3.Compute();
   setPWM3(pwm_val3);
     myPID4.Compute();
   setPWM4(pwm_val4);

}
void up()
{
 
   analogWrite(pwm7,sp7);//m5
   digitalWrite(dir7,1);//m5
   
}
void down()
{
    analogWrite(pwm7,sp7);//m5
   digitalWrite(dir7,0);//m5
  
}
void index()
{
//  encoderValue6=0;
//  int sp=0;
// long val=0;
// while(i!=1)
// {
// 
//  if(abs(encoderValue6)<1968)
//  { 
//    sp=40;
////     if(sp>10)
////    sp=10;
// //    Serial.println(sp);
//   analogWrite(pwm5,sp);
//  digitalWrite(dir5,1);
//  if(abs(encoderValue6)<1980&abs(encoderValue6)>1960&val<1980&val>1960)
// { 
// i=1;Serial.println("same");
// }}
//  if(abs(encoderValue6)>1968)
//  {
//    sp=40;//(abs(encoderValue6)-1968)*1.5;
//    if(sp>40)
//    sp=40;
//     Serial.println(sp);
//    analogWrite(pwm5,sp);
//  digitalWrite(dir5,0);
//  if(abs(encoderValue6)<1980&abs(encoderValue6)>1960&val<1980&val>1960)
// { i=1;Serial.println("same");
//  } 
//  }
//   if(abs(encoderValue6)<1980&abs(encoderValue6)>1960&val<1980&val>1960)
// { 
// i=1;Serial.println("same");
// }
//
//val=abs(encoderValue6);
// 
// }
 
  digitalWrite(dir5,1);
  analogWrite(pwm5,60);
  
}
void grip()
{
 
 
  digitalWrite(dir6,1);
  analogWrite(pwm6,100);
}
void ungrip()
{

  digitalWrite(dir6,0);
  analogWrite(pwm6,100);
}
void flap0()
{

  flaps.write(0);
}
void flap90()
{

   flaps.write(60);
}
 void setPWM1(int val){
    if(val>0)
        digitalWrite(dir1, HIGH);
    else 
        digitalWrite(dir1, LOW);
    analogWrite(pwm1,abs(val));
}  
 void setPWM2(int val){
    if(val>0)
        digitalWrite(dir2, HIGH);
    else 
        digitalWrite(dir2, LOW);
    analogWrite(pwm2,abs(val));
}  
 void setPWM3(int val){
    if(val>0)
        digitalWrite(dir3, HIGH);
    else 
        digitalWrite(dir3, LOW);
    analogWrite(pwm3,abs(val));
}  
 void setPWM4(int val){
    if(val>0)
        digitalWrite(dir4,LOW);
    else 
        digitalWrite(dir4, HIGH);
    analogWrite(pwm4,abs(val));
}  
void off()
{
  encoderValue1=0;
  encoderValue2=0;
  encoderValue3=0;
  encoderValue4=0;
  

  analogWrite(pwm1,0);//m1
  analogWrite(pwm2,0);//m1
  analogWrite(pwm3,0);//m1
  analogWrite(pwm4,0);//m1
  analogWrite(pwm5,0);//m1
  analogWrite(pwm6,0);//m1
   sp1=50;
 sp2=55;
 sp3=50;
 sp4=60;
 sp12=50;
 sp22=50;
 sp32=50;
 sp42=50;
tspeed=30;
 reqd_pos1 =0;
 reqd_pos2 =0;
 reqd_pos3 =0;
reqd_pos4 =0;
}

void unwind()
{
    digitalWrite(dir5,0);
  analogWrite(pwm5,50);
}

void loop() {

    if(Serial1.available()>0)
     {
      char c=Serial1.read();
      Serial.println(c);
       Serial.println(m);
 
    //Serial.println(encoderValue6);
    //Serial.println(encoderValue1);Serial.print(",");Serial.print(encoderValue2);Serial.print(",");Serial.print(encoderValue3);Serial.print(",");Serial.print(encoderValue4);
      if(c=='e'&m==1)
      {
       forward1();
       s=1;i=0;j=0;s0=0;s90=0;
      }
       else if(c=='k'&m==1)
      {
        backward1();s=1;i=0;j=0;s0=0;s90=0;
      }
       else if(c=='g'&m==1)
      {
        left1();s=1;i=0;j=0;s0=0;s90=0;
      }
      else if(c=='h'&m==1)
      {
       right1();s=1;i=0;j=0;s0=0;s90=0;
      }
    
      else if(c=='c'&m==1)
      {
        leftturn1(); s=1;i=0;j=0;s0=0;s90=0;
      }
      else if(c=='d'&m==1)
      {
        rightturn1(); s=1;i=0;j=0;s0=0;s90=0;
      }
       if(c=='e'&m==2)
      {
       forward2();s=1;i=0;j=0;s0=0;s90=0;
       s=0;
      }
       else if(c=='k'&m==2)
      {
        backward2();s=0;i=0;j=0;s0=0;s90=0;
      }
       else if(c=='g'&m==2)
      {
        left2();s=0;i=0;j=0;s0=0;s90=0;
      }
      else if(c=='h'&m==2)
      {
       right2();s=1;i=0;j=0;s0=0;s90=0;
      }
    
      else if(c=='c'&m==2)
      {
        leftturn2();s=0;i=0;j=0;s0=0;s90=0;
      }
      else if(c=='d'&m==2)
      {
        rightturn2();s=0;i=0;j=0;s0=0;s90=0;
      }
        else if(c=='i')
      {
        up(); s=0;i=0;j=0;s0=0;s90=0;
      }
        else if(c=='j')
      {
        down(); s=0;i=0;j=0;s0=0;s90=0;
      }
        else if((c=='b')&&(!i))
      {  Serial.println("index");
        index(); s=0;j=0;s0=0;s90=0;
      
      }
   else if(c=='m'&&(j==0))
     {  
    unwind();s=0;i=0;s0=0;s90=0;    
     }
       else if(c=='f')
      {
        grip();s=0;i=0;j=0;s0=0;s90=0;
      }
       else if(c=='l')
      {
        ungrip();s=0;i=0;j=0;s0=0;s90=0;
      }
       else if(c=='n'&m==1)
      {
       
       m=2;i=0;j=0;s=0;s0=0;s90=0;
         
        
       
      }
       else if(c=='n'&m==2)
      {
       
       m=1;s=0;i=0;j=0;s0=0;s90=0;
        
        
       
      }
       else if(c=='a'&flap==90&s0==0)
      {
     
        flaps.write(0);
        Serial.println("zero");
        delay(1000);
        flap=0;
        i=0;j=0;s=0;s0=1;s90=1;
          
      }
       else if(c=='a'&flap==0&s90==0)
      {
     
        flaps.write(90);
         Serial.println("90");
        delay(1000);
        flap=90;
        i=0;j=0;s=0;s90=1;s0=1;
          
      }
      else if(c=='z')
      {
        off();        i=0;j=0;s=0;s90=0;s0=0;
      }
      
      
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
