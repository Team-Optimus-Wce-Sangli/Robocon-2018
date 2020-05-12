int sp1=100;
int sp2=100;
int sp3=100;
int sp4=100;
int sp5=200;
int sp6=50;
int tspeed=50;
int i=0;
#define pwm1 13
#define pwm2 11
#define pwm3 8
#define pwm4 6
#define pwm6 2
#define pwm5 4
#define dir1 12
#define dir2 10
#define dir3 9
#define dir4 7
#define dir6 3
#define dir5 5
#define mag 14
#define a2bd 140416
#define b2cd 101253
#define c2bd 101253
#define b2dd 63172
#define d2ed 101253
#define e2dd 101253
#define d2fd 203392

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



int pos=0;
const int trigPin1 = 15;//ultrasonic1
const int echoPin1 = 16;//us1
const int trigPin2 = 20;//us2
const int echoPin2 = 21;//us2
long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
 // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
Serial1.begin(9600);
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
}

void forward()
{
    analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
  
}
void backward()
{
     analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
  
}
void left()
{
     analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
  
}
void right()
{
   analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
  
}

void leftturn()
{  analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
  
}
void rightturn()
{
     analogWrite(pwm1,sp1);//m1
    analogWrite(pwm2,sp2);//m2
    analogWrite(pwm3,sp3);//m3
    analogWrite(pwm4,sp4);//m4
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
}
void up()
{
  encoderValue5=0;
   analogWrite(pwm5,sp5);//m5
   digitalWrite(dir5,1);//m5
   if(abs(encoderValue5)>196800)
    {analogWrite(pwm5,0);//m5
    
    }
}
void down()
{
  encoderValue5=0;
   analogWrite(pwm5,sp5);//m5
   digitalWrite(dir5,0);//m5
   if(abs(encoderValue5)>196800)
   { analogWrite(pwm5,0);//m5
   
   }
}
void index()
{
  encoderValue6=0;
  int sp=0;
 long val=0;
 while(i!=1)
 {
  Serial.println(encoderValue6);
  if(abs(encoderValue6)<1968)
  { 
    sp=(abs(encoderValue6)-1968)*2.5;
    if(sp>50)
      sp=50;
     analogWrite(pwm6,sp);
  digitalWrite(dir6,1);
  if(abs(encoderValue6)<1975&abs(encoderValue6)>1965&val<1970&val>1965)
 { 
 i=1;Serial.println("same");
 }}
  if(abs(encoderValue6)>1968)
  {
    sp=(abs(encoderValue6)-1968)*2.5;
     if(sp>50)
    sp=50;
    analogWrite(pwm6,sp);
  digitalWrite(dir6,0);
  if(abs(encoderValue6)<1975&abs(encoderValue6)>1965&val<1970&val>1965)
 { i=1;Serial.println("same");
  } 
  }
   if(abs(encoderValue6)<1975&abs(encoderValue6)>1965&val<1970&val>1965)
 { 
 i=1;Serial.println("same");
 }

val=abs(encoderValue6);
 
 }
 
  
}
void grip()
{
  digitalWrite(mag,1);//magnet
}
void ungrip()
{
  digitalWrite(mag,0);//magnet
}
void off()
{
  analogWrite(pwm1,0);//m1
  analogWrite(pwm2,0);//m1
  analogWrite(pwm3,0);//m1
  analogWrite(pwm4,0);//m1
  analogWrite(pwm5,0);//m1
  analogWrite(pwm6,0);//m1
  //digitalWrite(mag,0);//magnet
 // Serial.println("off");
}
float us1()
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
distance1= duration1*0.034/2*10;
  return(distance1);
}
float us2()
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
distance2= duration2*0.034/2*10;
  return(distance2);
}
void calib()
{
   
 while(us1()<248|us1()>252|us2()<248|us2()>252|abs(us1()-us2())>3)
 {
  if(us1()>252&us2()>252)
  {
   
    left();
  }
  if(us1()<248&us2()<248)
  {
    right();
  }
 
  if(abs(us1()-us2())>3)
 {
  if(us1()>us2())
 { 
  leftturn();
  delay(50);
 
 }
  if(us2()>us1())
 { 
  rightturn();
  delay(50);
 }
 

   }
 }
 off();
}
void unwind()
{
  Serial.println("unwind");
  encoderValue6=0;
 
    digitalWrite(dir6,0);
    analogWrite(pwm6,100);
      delay(2000);
  off();
}

void loop() {
  
  
    if(Serial1.available()>0)
     {
      char c=Serial1.read();
    Serial.println(c);
    //Serial.println(encoderValue6);
    //Serial.println(encoderValue1);Serial.print(",");Serial.print(encoderValue2);Serial.print(",");Serial.print(encoderValue3);Serial.print(",");Serial.print(encoderValue4);
      if(c=='a')
      {
        forward();
        i=0;
      }
       else if(c=='b')
      {
        backward(); 
        i=0;
      }
       else if(c=='c')
      {
        left(); i=0;
      }
      else if(c=='d')
      {
        right(); i=0;
      }
      else if(c=='e')
      {
        calib(); i=0;
      }
      else if(c=='g')
      {
        leftturn(); i=0;
      }
      else if(c=='h')
      {
        rightturn(); i=0;
      }
        else if(c=='i')
      {
        up(); i=0;
      }
        else if(c=='j')
      {
        down(); i=0;
      }
        else if((c=='k')&&(!i))
      {  Serial.println("index");
        index(); 
      
      }
      else if(c=='m')
      {  
       unwind();
      
      }
       else if(c=='f')
      {
        grip();i=0;
      }
       else if(c=='l')
      {
        ungrip();i=0;
      }
      else if(c=='z')
      {
        off();i=0;
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
