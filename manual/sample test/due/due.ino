int pwm1=100;
int pwm2=100;
int pwm3=100;
int pwm4=100;
int pwm5=200;
int pwm6=50;
int tspeed=50;

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
const int trigPin1 = 16;//ultrasonic1
const int echoPin1 = 17;//us1
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
  pinMode(13,OUTPUT);//1 pwm
   pinMode(11,OUTPUT); // 2 pwm
   pinMode(8,OUTPUT); // 3 pwm
   pinMode(6,OUTPUT);  // 4 pwm
   pinMode(4,OUTPUT);  // 5 pwm
   pinMode(2,OUTPUT); // 6 pwm
   pinMode(8,OUTPUT); //  magnet
   pinMode(12,OUTPUT);// 1 dir
   pinMode(10,OUTPUT);// 2 dir
   pinMode(9,OUTPUT);// 3 dir
   pinMode(7,OUTPUT); // 4 dir
   pinMode(5,OUTPUT);//5dir
   pinMode(3,OUTPUT);// 6 dir
   pinMode(14,OUTPUT); // magn
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
 
}
void forwardd()
{
  digitalWrite(9,0);//m1
         digitalWrite(10,1);//m2
           digitalWrite(11,1);//m3
         digitalWrite(12,0);//m4
  encoderValue1=encoderValue2=encoderValue3=encoderValue4=0;
        
        while((abs(encoderValue1)<12000)|(abs(encoderValue2)<12000)|(abs(encoderValue3)<12000)|(abs(encoderValue4)<12000))
        {
          if(encoderValue1<12000)
          analogWrite(2,100);
          else
          analogWrite(2,0);
           if(encoderValue2<12000)
          analogWrite(3,100);
          else
          analogWrite(3,0);
           if(encoderValue3<12000)
          analogWrite(4,100);
          else
          analogWrite(4,0);
           if(encoderValue4<12000)
          analogWrite(5,100);
          else
          analogWrite(5,0);
          }
         
         off(); 
          
          
}
void forward()
{
    analogWrite(13,pwm1);//m1
    analogWrite(11,pwm2);//m2
    analogWrite(8,pwm3);//m3
    analogWrite(6,pwm4);//m4
     analogWrite(2,50);//m6
    digitalWrite(12,0);//m1
    digitalWrite(10,1);//m2
    digitalWrite(9,1);//m3
    digitalWrite(7,0);//m4
digitalWrite(3,0);//m4
  
}
void backward()
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
void left()
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
void right()
{
    analogWrite(2,pwm1);//m1
    analogWrite(3,pwm2);//m2
    analogWrite(4,pwm3);//m3
    analogWrite(5,pwm4);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,1);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,0);//m4
  
}

void leftturn()
{
    analogWrite(2,tspeed);//m1
    analogWrite(3,tspeed);//m2
     analogWrite(4,tspeed);//m1
    analogWrite(5,tspeed);//m2
   
    digitalWrite(9,0);//m1
    digitalWrite(10,0);//m2
    digitalWrite(11,0);//m3
    digitalWrite(12,0);//m4
  
}
void rightturn()
{
    analogWrite(2,tspeed);//m1
    analogWrite(3,tspeed);//m2
    analogWrite(4,tspeed);//m3
    analogWrite(5,tspeed);//m4
    digitalWrite(9,1);//m1
    digitalWrite(10,1);//m2
    digitalWrite(11,1);//m3
    digitalWrite(12,1);//m4
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
 encoderValue6=0;
 while(encoderValue6<600)
 {
  analogWrite(7,100);
  digitalWrite(14,1);
 }
 analogWrite(7,0);
  
  
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


void loop() {
  //Serial.print(encoderValue1);Serial.print(encoderValue2);Serial.print(encoderValue3);Serial.print(encoderValue4);Serial.print(encoderValue5);Serial.println(encoderValue6);
 // Serial.print(us1());Serial.print("--");Serial.println(us2());
    if(Serial1.available()>0)
     {
      char c=Serial1.read();
      //Serial.println(c);
    //Serial.println(encoderValue1);Serial.print(",");Serial.print(encoderValue2);Serial.print(",");Serial.print(encoderValue3);Serial.print(",");Serial.print(encoderValue4);
      if(c=='a')
      {
        forward(); 
      }
       else if(c=='b')
      {
        backward(); 
      }
       else if(c=='c')
      {
        left(); 
      }
      else if(c=='d')
      {
        right(); 
      }
      else if(c=='e')
      {
        digitalWrite(14,1);
        delay(1000);
        digitalWrite(14,0); 
      }
      else if(c=='g')
      {
        leftturn(); 
      }
      else if(c=='h')
      {
        rightturn(); 
      }
        else if(c=='i')
      {
        up(); 
      }
        else if(c=='j')
      {
        down(); 
      }
        else if(c=='k')
      {
        index(); 
      }
      else if(c=='z')
      {
        off();
      }
      else if(c=='l')
      {
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
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
