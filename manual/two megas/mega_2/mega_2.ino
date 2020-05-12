# define m4pwm 4;
# define m5pwm 5;
# define m6pwm 6;
# define m4dir 7;
# define m5dir 8;
# define m6dir 9; 
# define mag 10;
const int trigPin1 = 22;//ultrasonic1
const int echoPin1 = 23;//us1
const int trigPin2 = 24;//us2
const int echoPin2 = 25;//us2

 


int encoderPin7 = 2;//4
int encoderPin8 = 3;//4
int encoderPin9 = 18;//5
int encoderPin10 = 19;//5
int encoderPin11 = 20;//6
int encoderPin12 = 21;//6

 int pwm4=100;
int pwm5=100;
int pwm6=100;
int tspeed=50;

volatile int lastEncoded4 = 0;
volatile int lastEncoded5 = 0;
volatile int lastEncoded6 = 0;


volatile long encoderValue4 = 0;
volatile long encoderValue5 = 0;
volatile long encoderValue6 = 0;

long lastencoderValue4 = 0;
long lastencoderValue5 = 0;
long lastencoderValue6 = 0;

int lastMSB4 = 0;
int lastLSB4 = 0;
int lastMSB5 = 0;
int lastLSB5 = 0;
int lastMSB6 = 0;
int lastLSB6 = 0;


 volatile float   rev4=encoderValue4/9840;
 volatile float   rev5=encoderValue5/9840; 
 volatile float   rev6=encoderValue6/9840;


int pos=0;

long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
 // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
Serial3.begin(9600);
 
   pinMode(m4pwm,OUTPUT);  // 4 pwm
   pinMode(m5pwm,OUTPUT);  // 5 pwm
   pinMode(m6pwm,OUTPUT); // 6 pwm
   pinMode(mag,OUTPUT); //  magnet
     pinMode(m4dir,OUTPUT); // 4 dir
   pinMode(m5dir,OUTPUT);// 5 dir
   pinMode(m6dir,OUTPUT); // 6 dir
   
   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  
  pinMode(encoderPin7, INPUT); 
  pinMode(encoderPin8, INPUT);
  pinMode(encoderPin9, INPUT); 
  pinMode(encoderPin10, INPUT);
  pinMode(encoderPin11, INPUT); 
  pinMode(encoderPin12, INPUT);

  
digitalWrite(encoderPin7, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin8, HIGH); //turn pullup resistor on
digitalWrite(encoderPin9, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin10, HIGH); //turn pullup resistor on
digitalWrite(encoderPin11, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin12, HIGH); //turn pullup resistor on

 attachInterrupt(digitalPinToInterrupt(encoderPin7), updateEncoder4, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderPin8), updateEncoder4, CHANGE);
attachInterrupt(digitalPinToInterrupt(encoderPin9), updateEncoder5, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderPin10), updateEncoder5, CHANGE);
attachInterrupt(digitalPinToInterrupt(encoderPin11), updateEncoder6, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderPin12), updateEncoder6, CHANGE);
 
}
void forwardd()
{
 
          
}
void forward()
{
    analogWrite(m4pwm,pwm4);//
    digitalWrite(m4dir,0);//m4
  
}
void backward()
{
   analogWrite(m4pwm,pwm4);//
    digitalWrite(m4dir,1);//m4
  
}
void left()
{
  analogWrite(m4pwm,pwm4);//
    digitalWrite(m4dir,1);//m4
}
void right()
{
   analogWrite(m4pwm,pwm4);//
    digitalWrite(m4dir,0);//m4
  
}

void leftturn()
{
   analogWrite(m4pwm,tspeed);//
    digitalWrite(m4dir,0);//m4
  
}
void rightturn()
{
  analogWrite(m4pwm,tspeed);//
    digitalWrite(m4dir,1);//m4
}
void up()
{
   analogWrite(m5pwm,pwm5);//m5
   digitalWrite(m5dir,1);//m5
}
void down()
{
   analogWrite(m5pwm,pwm5);//m5
   digitalWrite(m5dir,0);//m5
}
void index()
{
 encoderValue6=0;
 while(encoderValue6<600)
 {
  analogWrite(m6pwm,pwm6);
  digitalWrite(m6dir,1);
 }
 analogWrite(m6pwm,0);
  
  
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
  
  analogWrite(m4pwm,0);//m4
  analogWrite(m5pwm,0);//m5
  analogWrite(m6pwm,0);//m6
  digitalWrite(mag,0);//magnet
  
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
  
  
    if(Serial1.available()>0)
     {
      char c=Serial1.read();
      Serial.println(c);
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
        forwardd(); 
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
      
      
      }
   
  // put your main code here, to run repeatedly:
  
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
