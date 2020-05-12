#include <PID_v1.h>
#define valve 2
#define laser_sensor 51
#define pwm1 12
#define pwm2 10
#define pwm3 8
#define pwm4 6
#define pwm5 4
#define dir1 11
#define dir2 9
#define dir3 7
#define dir4 5
#define dir5 3
#define tr 2
#define ls 51
#define led 13
#define a2bd 96282
#define b2cd 65000
#define c2bd 65000
#define b2dd 47169
#define d2ed 65000
#define e2dd 65000
#define f2dd 149646
#define d2fd 149646
const int trigPin3 = 39;//ultrasonic1
const int echoPin3 = 41;//us1
int sring=0;
int stflag=0;
int align=0;
long duration4;//us2
int distance4;//us2
long duration3;//us2
int distance3;//us2
int sp1=150;
int sp2=150;
int sp3=150;
int sp4=150;
int sp5=150;
int tspeed=150;

  const int trigPin4 = 22;//us2
const int echoPin4 = 23;//us2

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
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
     pinMode(41,INPUT);//laser
      pinMode(39,OUTPUT);//laser
    pinMode(13,OUTPUT);//led
    pinMode(14,OUTPUT);
   pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
}
void wall()
{
   analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
    
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
distance4= duration4*0.034/2*10;
  return(distance4);
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
distance3= duration3*0.034/2*10;
  return(distance3);
}
void calib2()
{
  
int e1=50;
 int e2=10;
  
  while(1)
   { Serial.println("while");
      e2=e1;
         Serial.print("e2==");Serial.println(e2);
    e1=us3();
    Serial.print("e1==");Serial.print(e1);
    if(abs(e1-e2)>5)
   { wall();
    delay(1000);}
    else
    break;
     
 
  }
Serial.println("done");
off();
//while(us4()>200|us4()<190)
//{
//  d1=us4();
//Serial.print("d1///");Serial.println(us4());
//if(us4()>200)
//{right();
//delay(50);
//Serial.println("right");
//}
//if(us4()<190)
//{left();Serial.println("left");
//delay(50);
//}
//if((us4()>190)&(us4()<200))
//{off();Serial.println("off");
//delay(50);
}

//d2=us4();
//Serial.print("d2////");Serial.println(us4());
//if(d1<200&d1>190&d2<200&d2>190)
//break;
//
//}
 
 void left()
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
void right()
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

void loop() {
  delay(2000);
calib2();
delay(1000000);

  // put your main code here, to run repeatedly:

}
