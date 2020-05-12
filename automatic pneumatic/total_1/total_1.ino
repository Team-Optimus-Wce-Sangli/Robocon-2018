

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
#define tr 13
#define ls 39
#define a2bd 50000
#define b2cd 101253
#define c2bd 101253
#define b2dd 63172
#define d2ed 101253
#define e2dd 101253
#define d2fd 203392
int ar=0;


int sp1=150;
int sp2=150;
int sp3=150;
int sp4=150;
int sp5=150;
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


 



const int trigPin1 = 31;//ultrasonic1
const int echoPin1 = 33;//us1
const int trigPin2 = 35;//us2
const int echoPin2 = 37;//us2
const int trigPin3 = 39;//ultrasonic1
const int echoPin3 = 41;//us1
const int trigPin4 = 43;//us2
const int echoPin4 = 45;//us2

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
     pinMode(41,INPUT);//laser
      pinMode(39,OUTPUT);//laser
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


attachInterrupt(58, updateEncoder1, CHANGE); 
  attachInterrupt(59, updateEncoder1, CHANGE);
attachInterrupt(60, updateEncoder2, CHANGE); 
  attachInterrupt(61, updateEncoder2, CHANGE);
attachInterrupt(62, updateEncoder3, CHANGE); 
  attachInterrupt(63, updateEncoder3, CHANGE);
attachInterrupt(64, updateEncoder4, CHANGE); 
  attachInterrupt(65, updateEncoder4, CHANGE);
attachInterrupt(66, updateEncoder5, CHANGE); 
  attachInterrupt(67, updateEncoder5, CHANGE);
digitalWrite(39,1);
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
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1)<a2bd&a)
      { 
       pid1=abs((encoderValue1)-a2bd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)<(a2bd+200)&(encoderValue1)>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)>a2bd&a)
     {
        pid1=abs((encoderValue1)-a2bd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)<(a2bd+200)&(encoderValue1)>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)<(a2bd+200)&(encoderValue1)>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1);
  }
     
    {
       
      if((encoderValue2*(-1))<a2bd&b)
      { 
       pid2=abs(encoderValue2-a2bd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*(-1))<(a2bd+500)&((encoderValue2)*(-1))>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*(-1))>a2bd&b)
     {
        pid2=abs(((encoderValue2)*(-1))-a2bd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*(-1))<(a2bd+500)&((encoderValue2)*(-1))>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*(-1))<(a2bd+500)&((encoderValue2)*(-1))>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*(-1));
  }
     

     {
       
      if(encoderValue3*(-1)<a2bd&c)
      { 
       pid3=abs(encoderValue3*(-1)-a2bd)*2.5;
       if(pid3>150)
        pid3=150;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*(-1)<(a2bd+500)&encoderValue3*(-1)>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*(-1)>a2bd&c)
     {
        pid3=abs(encoderValue3*(-1)-a2bd)*2.5;
         if(pid3>150)
         pid3=150;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*(-1)<(a2bd+500)&encoderValue3*(-1)>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*(-1)<(a2bd+500)&encoderValue3*(-1)>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*(-1);
  }
     {
       
      if((encoderValue4)<a2bd&d)
      { 
       pid4=abs((encoderValue4)-a2bd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4)<(a2bd+200)&(encoderValue4)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4)>a2bd&d)
     {
        pid4=abs((encoderValue4)-a2bd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4)<(a2bd+200)&(encoderValue4)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4)<(a2bd+200)&(encoderValue4)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4);
  }
     
   }
  off();
  delay(1000);
}
void b2c()
{
  int x=1;int y=1;int z=(-1);w=(-1);
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1)*x<b2cd&a)
      { 
       pid1=abs((encoderValue1)*x-b2cd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(b2cd+200)&(encoderValue1*x)>(b2cd-200)&val1<(b2cd+200)&val1>(b2cd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>b2cd&a)
     {
        pid1=abs((encoderValue1)*x-b2cd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)*x<(b2cd+200)&(encoderValue1)*x>(b2cd-200)&val1<(b2cd+200)&val1>(b2cd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(b2cd+200)&(encoderValue1)*x>(b2cd-200)&val1<(b2cd+200)&val1>(b2cd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if(encoderValue2*y<b2cd&b)
      { 
       pid2=abs(encoderValue2-b2cd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(b2cd+500)&encoderValue2>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>b2cd&b)
     {
        pid2=abs(encoderValue2-b2cd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(b2cd+500)&encoderValue2>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(b2cd+500)&encoderValue2>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<b2cd&c)
      { 
       pid3=abs(encoderValue3-b2cd)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(b2cd+200)&encoderValue3>(b2cd-200)&val3<(b2cd+200)&val3>(b2cd-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>b2cd&c)
     {
        pid3=abs(encoderValue3-b2cd)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(b2cd+200)&encoderValue3>(b2cd-200)&val3<(b2cd+200)&val3>(b2cd-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(b2cd+200)&encoderValue3>(b2cd-200)&val3<(b2cd+200)&val3>(b2cd-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<b2cd&d)
      { 
       pid4=abs((encoderValue4*(-1))-b2cd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(b2cd+200)&(encoderValue4*(-1))>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>b2cd&d)
     {
        pid4=abs((encoderValue4*(-1))-b2cd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(b2cd+200)&(encoderValue4*(-1))>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(b2cd+200)&(encoderValue4*(-1))>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}
void c2b()
{
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1*(-1))<c2bd&a)
      { 
       pid1=abs((encoderValue1*(-1))-c2bd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1*(-1))<(c2bd+200)&(encoderValue1*(-1))>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1*(-1))>c2bd&a)
     {
        pid1=abs((encoderValue1*(-1))-c2bd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1*(-1))<(c2bd+200)&(encoderValue1*(-1))>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1*(-1))<(c2bd+200)&(encoderValue1*(-1))>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1*(-1));
  }
     
    {
       
      if(encoderValue2<c2bd&b)
      { 
       pid2=abs(encoderValue2-c2bd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(c2bd+500)&encoderValue2>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>c2bd&b)
     {
        pid2=abs(encoderValue2-c2bd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(c2bd+500)&encoderValue2>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(c2bd+500)&encoderValue2>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<c2bd&c)
      { 
       pid3=abs(encoderValue3-c2bd)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(c2bd+200)&encoderValue3>(c2bd-200)&val3<(c2bd+200)&val3>(c2bd-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>c2bd&c)
     {
        pid3=abs(encoderValue3-c2bd)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(c2bd+200)&encoderValue3>(c2bd-200)&val3<(c2bd+200)&val3>(c2bd-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(c2bd+200)&encoderValue3>(c2bd-200)&val3<(c2bd+200)&val3>(c2bd-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<c2bd&d)
      { 
       pid4=abs((encoderValue4*(-1))-c2bd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(c2bd+200)&(encoderValue4*(-1))>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>c2bd&d)
     {
        pid4=abs((encoderValue4*(-1))-c2bd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(c2bd+200)&(encoderValue4*(-1))>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(c2bd+200)&(encoderValue4*(-1))>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}
void b2d()
{
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1*(-1))<b2dd&a)
      { 
       pid1=abs((encoderValue1*(-1))-b2dd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1*(-1))<(b2dd+200)&(encoderValue1*(-1))>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1*(-1))>b2dd&a)
     {
        pid1=abs((encoderValue1*(-1))-b2dd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1*(-1))<(b2dd+200)&(encoderValue1*(-1))>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1*(-1))<(b2dd+200)&(encoderValue1*(-1))>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1*(-1));
  }
     
    {
       
      if(encoderValue2<b2dd&b)
      { 
       pid2=abs(encoderValue2-b2dd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(b2dd+500)&encoderValue2>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>b2dd&b)
     {
        pid2=abs(encoderValue2-b2dd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(b2dd+500)&encoderValue2>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(b2dd+500)&encoderValue2>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<b2dd&c)
      { 
       pid3=abs(encoderValue3-b2dd)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(b2dd+200)&encoderValue3>(b2dd-200)&val3<(b2dd+200)&val3>(b2dd-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>b2dd&c)
     {
        pid3=abs(encoderValue3-b2dd)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(b2dd+200)&encoderValue3>(b2dd-200)&val3<(b2dd+200)&val3>(b2dd-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(b2dd+200)&encoderValue3>(b2dd-200)&val3<(b2dd+200)&val3>(b2dd-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<b2dd&d)
      { 
       pid4=abs((encoderValue4*(-1))-b2dd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(b2dd+200)&(encoderValue4*(-1))>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>b2dd&d)
     {
        pid4=abs((encoderValue4*(-1))-b2dd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(b2dd+200)&(encoderValue4*(-1))>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(b2dd+200)&(encoderValue4*(-1))>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}
void d2e()
{
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1*(-1))<d2ed&a)
      { 
       pid1=abs((encoderValue1*(-1))-d2ed)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1*(-1))<(d2ed+200)&(encoderValue1*(-1))>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1*(-1))>d2ed&a)
     {
        pid1=abs((encoderValue1*(-1))-d2ed)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1*(-1))<(d2ed+200)&(encoderValue1*(-1))>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1*(-1))<(d2ed+200)&(encoderValue1*(-1))>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1*(-1));
  }
     
    {
       
      if(encoderValue2<d2ed&b)
      { 
       pid2=abs(encoderValue2-d2ed)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(d2ed+500)&encoderValue2>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>d2ed&b)
     {
        pid2=abs(encoderValue2-d2ed)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(d2ed+500)&encoderValue2>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(d2ed+500)&encoderValue2>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<d2ed&c)
      { 
       pid3=abs(encoderValue3-d2ed)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(d2ed+200)&encoderValue3>(d2ed-200)&val3<(d2ed+200)&val3>(d2ed-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>d2ed&c)
     {
        pid3=abs(encoderValue3-d2ed)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(d2ed+200)&encoderValue3>(d2ed-200)&val3<(d2ed+200)&val3>(d2ed-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(d2ed+200)&encoderValue3>(d2ed-200)&val3<(d2ed+200)&val3>(d2ed-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<d2ed&d)
      { 
       pid4=abs((encoderValue4*(-1))-d2ed)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(d2ed+200)&(encoderValue4*(-1))>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>d2ed&d)
     {
        pid4=abs((encoderValue4*(-1))-d2ed)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(d2ed+200)&(encoderValue4*(-1))>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(d2ed+200)&(encoderValue4*(-1))>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}
void e2d()
{
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1*(-1))<e2dd&a)
      { 
       pid1=abs((encoderValue1*(-1))-e2dd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1*(-1))<(e2dd+200)&(encoderValue1*(-1))>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1*(-1))>e2dd&a)
     {
        pid1=abs((encoderValue1*(-1))-e2dd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1*(-1))<(e2dd+200)&(encoderValue1*(-1))>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1*(-1))<(e2dd+200)&(encoderValue1*(-1))>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1*(-1));
  }
     
    {
       
      if(encoderValue2<e2dd&b)
      { 
       pid2=abs(encoderValue2-e2dd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(e2dd+500)&encoderValue2>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>e2dd&b)
     {
        pid2=abs(encoderValue2-e2dd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(e2dd+500)&encoderValue2>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(e2dd+500)&encoderValue2>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<e2dd&c)
      { 
       pid3=abs(encoderValue3-e2dd)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(e2dd+200)&encoderValue3>(e2dd-200)&val3<(e2dd+200)&val3>(e2dd-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>e2dd&c)
     {
        pid3=abs(encoderValue3-e2dd)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(e2dd+200)&encoderValue3>(e2dd-200)&val3<(e2dd+200)&val3>(e2dd-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(e2dd+200)&encoderValue3>(e2dd-200)&val3<(e2dd+200)&val3>(e2dd-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<e2dd&d)
      { 
       pid4=abs((encoderValue4*(-1))-e2dd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(e2dd+200)&(encoderValue4*(-1))>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>e2dd&d)
     {
        pid4=abs((encoderValue4*(-1))-e2dd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(e2dd+200)&(encoderValue4*(-1))>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(e2dd+200)&(encoderValue4*(-1))>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}
void d2f()
{
   int d11=1;
  int d21=0;
  int d31=0;
  int d41=1;
  int d12=0;
  int d22=1;
  int d32=1;
  int d42=0;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while(c==1|a==1|b==1|d==1)
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
     
       
     {
       
      if((encoderValue1*(-1))<d2fd&a)
      { 
       pid1=abs((encoderValue1*(-1))-d2fd)*2.5;
       if(pid1>150)
        pid1=150;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1*(-1))<(d2fd+200)&(encoderValue1*(-1))>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1*(-1))>d2fd&a)
     {
        pid1=abs((encoderValue1*(-1))-d2fd)*2.5;
         if(pid1>150)
         pid1=150;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1*(-1))<(d2fd+200)&(encoderValue1*(-1))>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1*(-1))<(d2fd+200)&(encoderValue1*(-1))>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1*(-1));
  }
     
    {
       
      if(encoderValue2<d2fd&b)
      { 
       pid2=abs(encoderValue2-d2fd)*2.5;
       if(pid2>150)
        pid2=150;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(encoderValue2<(d2fd+500)&encoderValue2>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(encoderValue2>d2fd&b)
     {
        pid2=abs(encoderValue2-d2fd)*2.5;
         if(pid2>150)
         pid2=150;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(encoderValue2<(d2fd+500)&encoderValue2>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(encoderValue2<(d2fd+500)&encoderValue2>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=encoderValue2;
  }
     

     {
       
      if(encoderValue3<d2fd&c)
      { 
       pid3=abs(encoderValue3-d2fd)*2.5;
       if(pid3>150)
        {pid3=150;}
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3<(d2fd+200)&encoderValue3>(d2fd-200)&val3<(d2fd+200)&val3>(d2fd-200))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3>d2fd&c)
     {
        pid3=abs(encoderValue3-d2fd)*2.5;
         if(pid3>150)
         {pid3=150;}
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3<(d2fd+200)&encoderValue3>(d2fd-200)&val3<(d2fd+200)&val3>(d2fd-200))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3<(d2fd+200)&encoderValue3>(d2fd-200)&val3<(d2fd+200)&val3>(d2fd-200))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3;
  }
     {
       
      if((encoderValue4*(-1))<d2fd&d)
      { 
       pid4=abs((encoderValue4*(-1))-d2fd)*2.5;
       if(pid4>150)
        pid4=150;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*(-1))<(d2fd+200)&(encoderValue4*(-1))>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*(-1))>d2fd&d)
     {
        pid4=abs((encoderValue4*(-1))-d2fd)*2.5;
         if(pid4>150)
         pid4=150;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*(-1))<(d2fd+200)&(encoderValue4*(-1))>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*(-1))<(d2fd+200)&(encoderValue4*(-1))>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*(-1));
  }
     
   }
  off();
  delay(1000);
}

void tr1()
{
  
  arm(0);
 
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>5000)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
  arm(0);
}
void tr2()
{
   arm(0);
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>5000)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
  arm(0);
}
void tr3()
{
  
  arm(0);
  digitalWrite(dir5,1);
  analogWrite(pwm5,sp5);
  if(encoderValue5>5000)
  {
    digitalWrite(tr,1);
    analogWrite(pwm5,0);
    delay(1000);
    digitalWrite(tr,0);
   
  }
  arm(0);
}
void grip()
{
 arm(3000);
 
  digitalWrite(tr,1);
  Serial.println("open");
 delay(50);
 
 forward();
 delay(100);
  digitalWrite(tr,0);
   Serial.println("close");
  delay(50);
  backward();
  delay(100);
    
}
void arm(int val)

{     
     int ar=0; 
      int pid5=0;
      long val5=0;
       while(ar==0)
     {
        if(encoderValue5<val)
      { 
       pid5=abs(encoderValue5-val)*2.5;
       if(pid5>50)
        pid5=50;
       analogWrite(pwm5,pid5);
       digitalWrite(dir5,1);
      
      }
      if(encoderValue5>val)
     {
        pid5=abs(encoderValue5-val)*2.5;
         if(pid5>50)
         pid5=50;
        analogWrite(pwm5,pid5);
         digitalWrite(dir5,0);
            }
  if(encoderValue5==val5)
  {
    ar=1;
    Serial.println("open");
    delay(500);
    ar=0;
    delay(500);
    Serial.println("close");
    ar=0;
  }
      val5=encoderValue5;
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
distance1= duration1*0.034/2*10;
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
distance2= duration2*0.034/2*10;
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
distance3= duration3*0.034/2*10;
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
distance4= duration4*0.034/2*10;
  return(distance4);
}
void calib1()
{
  
   while(us1()<245|us1()>255|us2()<245|us2()>255|abs(us1()-us2())>5)
 {
 Serial.print(us1()); Serial.print("/");Serial.println(us2());
  if(us1()>255&us2()>255)
  {  
    backward();
  }
  if(us1()<245&us2()<245)
  {
    forward();
  }
 
  if(abs(us1()-us2())>5)
 {
   if(us1()>us2())
  { 
  rightturn();
  Serial.println("right");
  delay(50);
   }
  if(us2()>us1())
   { 
  leftturn();
  Serial.println("left");
  delay(50);
  }
    }
    
 }
 off();
}
void calib2()
{
 int i=0;
 int j=0;
    while(us3()>300&us4()>300)
  {
    forward();
  }
  while(us3()<200&us4()<200)
  {
    backward();
  }
  if(us3()<300&us3()>200)
  int i=1;
   if(us4()<300&us4()>200)
  int j=1;  
     while(abs(us3()-us4())>5&i==1&j==1)
     {
       if(us3()>us4())
       { rightturn();
         delay(50);
       }
       if(us4()>us3())
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
void left()
{
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
  
  
}
void right()
{
    analogWrite(pwm1,tspeed);//m1
    analogWrite(pwm2,tspeed);//m2
     analogWrite(pwm3,tspeed);//m1
    analogWrite(pwm4,tspeed);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
  
  
}

void loop() {
//Serial.println(encoderValue5);
 
//  delay(5000);
////
// 
////calib1();
//
if(Serial.available())
{
//arm(3000);
a2b();
//forward();
//delay(2000);
//backward();
//delay(2000);
delay(100000000);

}

//delay(1000000000);
// delay(20000);
//  calib2();
//  grip();
//  b2c();
//   calib2();
//  tr1();
//  c2b();
//   calib1();
//  b2d();
//   calib1();
//    calib2();
//  grip();
//  d2e();
//   calib2();
//   tr2();
//   e2d();
//   calib1();
//   calib2();
//  grip();
//  d2f():
//  calib2();
//  tr3();
    
  
}

void updateEncoder1()
{
  int MSB1 = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB1 = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded1 = (MSB1 << 1) |LSB1; //converting the 2 pin value to single number
  int sum1  = (lastEncoded1 << 2) | encoded1; //adding it to the pencoderValueious encoded value

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

