
// ################ Defining pin names #######################


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
#define lz 53
#define flap 19
#define led 13
#define a2bd 96282
#define b2cd 50160
#define c2bd 65000
#define b2dd 42169
#define d2ed 45160
#define e2dd 65000
#define f2dd 149646
#define d2fd 139806
int sring=0;
int stflag=0;
int align=0;
int sp2=150;
int sp1=250;
int sp1m=250;
int tspeed=100;
int wspeed=150;
int wspeed2=80;
double release_val1 = 60935;
double release_val2 = 60585;
double release_val3 = 60735;//60300
double pwm_val = 0;
char r_dir=0;
int l=0;
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
int st=0;

volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile int lastEncoded3 = 0;
volatile int lastEncoded4 = 0;
volatile int lastEncoded5 = 0;


volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile long encoderValue3 = 0;
volatile long encoderValue4 = 0;
double encoderValue5 = 0;


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
const int trigPin5 = 47;//us2
const int echoPin5 = 49;//us2

long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
long duration3;//us1
int distance3;//us1
long duration4;//us2
int distance4;//us2
long duration5;//us2
int distance5;//us2
double Kp=0.1;
double Ki=0.05;
double Kd=0.001;
double reqd_pos = -2300;
int throw_velocity1 = -70;
int throw_velocity2 = -90;
int throw_velocity3 = -100;
int travel_velocity = 20;

PID myPID(&encoderValue5,&pwm_val, &reqd_pos, Kp, Ki, Kd, DIRECT);
byte state = 0 ;
char run = 0;
unsigned char flag = 0;


void setup()
{
  //motor 1,2,3,4 driwe.5 lead,6 index
 // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
Serial1.begin(9600);
myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-100,100);
    myPID.SetSampleTime(1);
       pinMode(laser_sensor, INPUT);
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
    pinMode(53,INPUT);
   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
     pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
   pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
    pinMode(trigPin5, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin5, INPUT); // Sets the echoPin as an Input
   
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
  
    digitalWrite(dir5,r_dir);
 
digitalWrite(47,1);
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
digitalWrite(51,1);
}

void grip()
{
  digitalWrite(47,1);
  int shuttle=0;int done=0;
  Serial.println("ingrip");
state=0;
sring=0;
   while(1)
   {     
     reqd_pos = -2300;                
  switch(state)
  {
  case 0 :                 for(int ti=millis();millis()<ti+1000;)
                         {
                          myPID.Compute();
                          setPWM(pwm_val);
                         }
                          for(int ti=millis();millis()<ti+5000;)
                         {
                          myPID.Compute();
                          setPWM(pwm_val);
                           Serial.println("open"); 
                            digitalWrite(valve, HIGH);
                          if(digitalRead(flap)==1)
                             {
                                 sring=0;
                          
                               }
                           else
                             {
                                 sring=1;
                              }
                         }
                        // open valve when reached
                          digitalWrite(valve, LOW);
                          delay(2000);
                           reqd_pos = -3000; 
                           for(int ti=millis();millis()<ti+1000;)
                         {
                          myPID.Compute();
                          setPWM(pwm_val);
                         }
                         analogWrite(pwm5,0);
                          delay(1000);
                          if(encoderValue5>(-2950))
                          {
                            shuttle=1;
                          }
                          else
                          {
                            shuttle=0;
                          }
                                                                                                        
                               flag = 0;
                               done=1;
                             break; 
                          }
       if(shuttle==1)                   
       break;              
   }          
    reqd_pos = 0;            
}
void wall()
{
  digitalWrite(47,0);
   analogWrite(pwm1,wspeed);//m1
    analogWrite(pwm2,wspeed);//m2
     analogWrite(pwm3,wspeed);//m1
    analogWrite(pwm4,wspeed);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
    
}
void wall2()
{
    digitalWrite(47,0);
   analogWrite(pwm1,wspeed2);//m1
    analogWrite(pwm2,wspeed2);//m2
     analogWrite(pwm3,wspeed2);//m1
    analogWrite(pwm4,wspeed2);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,0);//m4
    
}
void wback()
{
   analogWrite(pwm1,wspeed);//m1
    analogWrite(pwm2,wspeed);//m2
     analogWrite(pwm3,wspeed);//m1
    analogWrite(pwm4,wspeed);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    
}
 void throw1()
{
        int t=millis();
        reqd_pos = 0;
                       while(millis()<t+1000)        
                      {  
                         reqd_pos =0;
                         wall2();
                        myPID.Compute();
                        setPWM(pwm_val);}
                        while(1)
                        {
                          wall2();
                          if(abs(encoderValue5)<24000)
                         { setPWM(-50);}
                         else if(abs(encoderValue5) <= release_val1&abs(encoderValue5)>=24000)
                        {setPWM(throw_velocity1);  }
                        else
                        {               Serial.println("trowsd 1");
                            digitalWrite(valve,HIGH);
                             setPWM(100);
                            delay(200); 
                            setPWM(0);
                            delay(1000);
                             digitalWrite(valve,LOW); 
                             reqd_pos =-2300;
                            state = 0;
                            off();
                            break;
                 }
                        }
                        sring=0;
                           
}
   void throw2()
{
        int t=millis();
        reqd_pos = 0;
                       while(millis()<t+1000)        
                      {   reqd_pos =0;
                        wall2();
                        myPID.Compute();
                        setPWM(pwm_val);}
                        while(1)
                        {
                          wall2();
                          if(abs(encoderValue5)<24000)
                         { setPWM(-50);}
                         else if(abs(encoderValue5) <= release_val2&abs(encoderValue5)>=24000)
                        {setPWM(throw_velocity2);  }
                        else
                        {               Serial.println("trowsd 3");
                            digitalWrite(valve,HIGH);
                             setPWM(100);
                            delay(200); 
                            setPWM(0);
                            delay(1000);
                             digitalWrite(valve,LOW); 
                             reqd_pos =-2300;
                            state = 0;
                            off();
                            break;
                 }
                        }
                        sring=0;
                           
}
    void throw3()
{
        int t=millis();
        reqd_pos =0;
                       while(millis()<t+1000)        
                      {  reqd_pos =0;
                        wall2();
                        myPID.Compute();
                        setPWM(pwm_val);}
                        while(1)
                        {
                          wall2();
                          if(abs(encoderValue5)<24000)
                         { setPWM(-50);}
                         else if(abs(encoderValue5) <= release_val3&abs(encoderValue5)>=24000)
                        {setPWM(throw_velocity3);  }
                        else
                        {               Serial.println("trowsd 3");
                            digitalWrite(valve,HIGH);
                             setPWM(100);
                            delay(200); 
                            setPWM(0);
                            delay(1000);
                             digitalWrite(valve,LOW); 
                             reqd_pos =-2300;
                            state = 0;
                            off();
                            break;
                 }
                        }
                        sring=0;
                           
}
  void setPWM(int val){
    if(val>0)
        digitalWrite(dir5, HIGH);
    else 
        digitalWrite(dir5, LOW);
    analogWrite(pwm5,abs(val));
}  
void leftturn()
{
    analogWrite(pwm1,50);//m1
    analogWrite(pwm2,50);//m2
     analogWrite(pwm3,50);//m1
    analogWrite(pwm4,50);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
  
}
void rightturn()
{
     analogWrite(pwm1,50);//m1
    analogWrite(pwm2,50);//m2
     analogWrite(pwm3,50);//m1
    analogWrite(pwm4,50);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
}
void a2b()
{  digitalWrite(47,0);
  int x=1;int y=(-1);int z=(-1);int w=1;
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
      int armpos=0;
    encoderValue1=0;
   while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
    
      {                 
     {
      if((encoderValue1)*x<a2bd&a)
      { 
       pid1=abs((encoderValue1)*x-a2bd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(a2bd+200)&(encoderValue1)*x>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>a2bd&a)
     {
        pid1=abs((encoderValue1)*x-a2bd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)*x<(a2bd+200)&(encoderValue1)*x>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(a2bd+200)&(encoderValue1)*x>(a2bd-200)&val1<(a2bd+200)&val1>(a2bd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<a2bd&b)
      { 
       pid2=abs(encoderValue2*y-a2bd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*y)<(a2bd+500)&((encoderValue2)*y)>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>a2bd&b)
     {
        pid2=abs(((encoderValue2)*y)-a2bd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*y)<(a2bd+500)&((encoderValue2)*y)>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(a2bd+500)&((encoderValue2)*y)>(a2bd-500)&val2<(a2bd+500)&val2>(a2bd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<a2bd&c)
      { 
       pid3=abs(encoderValue3*z-a2bd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*z<(a2bd+500)&encoderValue3*z>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>a2bd&c)
     {
        pid3=abs(encoderValue3*z-a2bd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*z<(a2bd+500)&encoderValue3*z>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(a2bd+500)&encoderValue3*z>(a2bd-500)&val3<(a2bd+500)&val3>(a2bd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<a2bd&d)
      { 
       pid4=abs((encoderValue4*w)-a2bd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4*w)<(a2bd+200)&(encoderValue4*w)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>a2bd&d)
     {
        pid4=abs((encoderValue4*w)-a2bd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4*w)<(a2bd+200)&(encoderValue4*w)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(a2bd+200)&(encoderValue4*w)>(a2bd-200)&val4<(a2bd+200)&val4>(a2bd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
    if(armpos==0)
                      {setPWM(travel_velocity);
                        // wait till arm reaches initial pos
                        while(digitalRead(laser_sensor) == LOW);
                            //Serial.println(digitalRead(laser_sensor));
                            Serial.println("zero");
                       encoderValue5 = 0;
                       // Serial.println("Reached Zero !");
                        setPWM(0);
                        reqd_pos = -2300;
                        state = 1;
                        for(int ti=millis();millis()<ti+1000;)
                         {myPID.Compute();
                          setPWM(pwm_val); }
                          armpos=1;
                      }    
                     
      
      }                    
   }
  off();
  delay(1000);
      
}
void b2c()
{
    digitalWrite(47,1);
  int x=1;int y=(1);int z=(-1);int w=(-1);
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
      int armpos=0;
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
     while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    reqd_pos =0;
   
       if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    } 
     {
       
      if((encoderValue1)*x<b2cd&a)
      { 
       pid1=abs((encoderValue1)*x-b2cd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(b2cd+200)&(encoderValue1)*x>(b2cd-200)&val1<(b2cd+200)&val1>(b2cd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>b2cd&a)
     {
        pid1=abs((encoderValue1)*x-b2cd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
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
       
      if((encoderValue2*y)<b2cd&b)
      { 
       pid2=abs(encoderValue2*y-b2cd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,0);
      if(((encoderValue2)*y)<(b2cd+500)&((encoderValue2)*y)>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>b2cd&b)
     {
        pid2=abs(((encoderValue2)*y)-b2cd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,1);
         if(((encoderValue2)*y)<(b2cd+500)&((encoderValue2)*y)>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(b2cd+500)&((encoderValue2)*y)>(b2cd-500)&val2<(b2cd+500)&val2>(b2cd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<b2cd&c)
      { 
       pid3=abs(encoderValue3*z-b2cd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*z<(b2cd+500)&encoderValue3*z>(b2cd-500)&val3<(b2cd+500)&val3>(b2cd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>b2cd&c)
     {
        pid3=abs(encoderValue3*z-b2cd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*z<(b2cd+500)&encoderValue3*z>(b2cd-500)&val3<(b2cd+500)&val3>(b2cd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(b2cd+500)&encoderValue3*z>(b2cd-500)&val3<(b2cd+500)&val3>(b2cd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<b2cd&d)
      { 
       pid4=abs((encoderValue4*w)-b2cd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*w)<(b2cd+200)&(encoderValue4*w)>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>b2cd&d)
     {
        pid4=abs((encoderValue4*w)-b2cd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*w)<(b2cd+200)&(encoderValue4*w)>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(b2cd+200)&(encoderValue4*w)>(b2cd-200)&val4<(b2cd+200)&val4>(b2cd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
      
   }
  off();
  delay(1000);
      
}
void c2b()
{
    digitalWrite(47,0);
   int x=(-1);int y=(-1);int z=(1);int w=1;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
     int armpos=0; 
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
     while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
  
     
  if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
       
     {
       
      if((encoderValue1)*x<c2bd&a)
      { 
       pid1=abs((encoderValue1)*x-c2bd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,1);
      if((encoderValue1)*x<(c2bd+200)&(encoderValue1)*x>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>c2bd&a)
     {
        pid1=abs((encoderValue1)*x-c2bd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,0);
         if((encoderValue1)*x<(c2bd+200)&(encoderValue1)*x>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(c2bd+200)&(encoderValue1)*x>(c2bd-200)&val1<(c2bd+200)&val1>(c2bd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<c2bd&b)
      { 
       pid2=abs(encoderValue2*y-c2bd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*y)<(c2bd+500)&((encoderValue2)*y)>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>c2bd&b)
     {
        pid2=abs(((encoderValue2)*y)-c2bd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*y)<(c2bd+500)&((encoderValue2)*y)>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(c2bd+500)&((encoderValue2)*y)>(c2bd-500)&val2<(c2bd+500)&val2>(c2bd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<c2bd&c)
      { 
       pid3=abs(encoderValue3*z-c2bd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3*z<(c2bd+500)&encoderValue3*z>(c2bd-500)&val3<(c2bd+500)&val3>(c2bd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>c2bd&c)
     {
        pid3=abs(encoderValue3*z-c2bd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3*z<(c2bd+500)&encoderValue3*z>(c2bd-500)&val3<(c2bd+500)&val3>(c2bd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(c2bd+500)&encoderValue3*z>(c2bd-500)&val3<(c2bd+500)&val3>(c2bd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<c2bd&d)
      { 
       pid4=abs((encoderValue4*w)-c2bd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4*w)<(c2bd+200)&(encoderValue4*w)>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>c2bd&d)
     {
        pid4=abs((encoderValue4*w)-c2bd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4*w)<(c2bd+200)&(encoderValue4*w)>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(c2bd+200)&(encoderValue4*w)>(c2bd-200)&val4<(c2bd+200)&val4>(c2bd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
     if(armpos==0)
                      {setPWM(travel_velocity);
                        // wait till arm reaches initial pos
                        while(digitalRead(laser_sensor) == LOW);
                            //Serial.println(digitalRead(laser_sensor));
                            Serial.println("zero");
                       encoderValue5 = 0;
                       // Serial.println("Reached Zero !");
                        setPWM(0);
                        reqd_pos = -2300;
                        state = 1;
                        for(int ti=millis();millis()<ti+1000;)
                         {myPID.Compute();
                          setPWM(pwm_val); }
                          armpos=1;
                      }    
                     
      
      
   }
  off();
  delay(1000);
       
}
void b2d()
{
    digitalWrite(47,1);
   int x=1;int y=(-1);int z=(-1);int w=1;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
        int armpos=0; 
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
      while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
    if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
       
     {
       
      if((encoderValue1)*x<b2dd&a)
      { 
       pid1=abs((encoderValue1)*x-b2dd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(b2dd+200)&(encoderValue1)*x>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>b2dd&a)
     {
        pid1=abs((encoderValue1)*x-b2dd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)*x<(b2dd+200)&(encoderValue1)*x>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(b2dd+200)&(encoderValue1)*x>(b2dd-200)&val1<(b2dd+200)&val1>(b2dd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<b2dd&b)
      { 
       pid2=abs(encoderValue2*y-b2dd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*y)<(b2dd+500)&((encoderValue2)*y)>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>b2dd&b)
     {
        pid2=abs(((encoderValue2)*y)-b2dd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*y)<(b2dd+500)&((encoderValue2)*y)>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(b2dd+500)&((encoderValue2)*y)>(b2dd-500)&val2<(b2dd+500)&val2>(b2dd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<b2dd&c)
      { 
       pid3=abs(encoderValue3*z-b2dd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*z<(b2dd+500)&encoderValue3*z>(b2dd-500)&val3<(b2dd+500)&val3>(b2dd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>b2dd&c)
     {
        pid3=abs(encoderValue3*z-b2dd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*z<(b2dd+500)&encoderValue3*z>(b2dd-500)&val3<(b2dd+500)&val3>(b2dd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(b2dd+500)&encoderValue3*z>(b2dd-500)&val3<(b2dd+500)&val3>(b2dd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<b2dd&d)
      { 
       pid4=abs((encoderValue4*w)-b2dd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4*w)<(b2dd+200)&(encoderValue4*w)>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>b2dd&d)
     {
        pid4=abs((encoderValue4*w)-b2dd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4*w)<(b2dd+200)&(encoderValue4*w)>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(b2dd+200)&(encoderValue4*w)>(b2dd-200)&val4<(b2dd+200)&val4>(b2dd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
     
   }
  off();
  delay(1000);  

     
}
void d2e()
{
    digitalWrite(47,1);
    int x=1;int y=(1);int z=(-1);int w=(-1);
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
        int armpos=0; 
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
     while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
   
       
     {
       
      if((encoderValue1)*x<d2ed&a)
      { 
       pid1=abs((encoderValue1)*x-d2ed)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(d2ed+200)&(encoderValue1)*x>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>d2ed&a)
     {
        pid1=abs((encoderValue1)*x-d2ed)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)*x<(d2ed+200)&(encoderValue1)*x>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(d2ed+200)&(encoderValue1)*x>(d2ed-200)&val1<(d2ed+200)&val1>(d2ed-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<d2ed&b)
      { 
       pid2=abs(encoderValue2*y-d2ed)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,0);
      if(((encoderValue2)*y)<(d2ed+500)&((encoderValue2)*y)>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>d2ed&b)
     {
        pid2=abs(((encoderValue2)*y)-d2ed)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,1);
         if(((encoderValue2)*y)<(d2ed+500)&((encoderValue2)*y)>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(d2ed+500)&((encoderValue2)*y)>(d2ed-500)&val2<(d2ed+500)&val2>(d2ed-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<d2ed&c)
      { 
       pid3=abs(encoderValue3*z-d2ed)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*z<(d2ed+500)&encoderValue3*z>(d2ed-500)&val3<(d2ed+500)&val3>(d2ed-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>d2ed&c)
     {
        pid3=abs(encoderValue3*z-d2ed)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*z<(d2ed+500)&encoderValue3*z>(d2ed-500)&val3<(d2ed+500)&val3>(d2ed-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(d2ed+500)&encoderValue3*z>(d2ed-500)&val3<(d2ed+500)&val3>(d2ed-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<d2ed&d)
      { 
       pid4=abs((encoderValue4*w)-d2ed)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*w)<(d2ed+200)&(encoderValue4*w)>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>d2ed&d)
     {
        pid4=abs((encoderValue4*w)-d2ed)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*w)<(d2ed+200)&(encoderValue4*w)>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(d2ed+200)&(encoderValue4*w)>(d2ed-200)&val4<(d2ed+200)&val4>(d2ed-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
     
   }
  off();
  delay(1000);     
}
void e2d()
{
    digitalWrite(47,0);
   int x=(-1);int y=(-1);int z=(1);int w=1;
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
     int armpos=0; 
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
   while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
  
   if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
    
     {
       
      if((encoderValue1)*x<e2dd&a)
      { 
       pid1=abs((encoderValue1)*x-e2dd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,1);
      if((encoderValue1)*x<(e2dd+200)&(encoderValue1)*x>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>e2dd&a)
     {
        pid1=abs((encoderValue1)*x-e2dd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,0);
         if((encoderValue1)*x<(e2dd+200)&(encoderValue1)*x>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(e2dd+200)&(encoderValue1)*x>(e2dd-200)&val1<(e2dd+200)&val1>(e2dd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<e2dd&b)
      { 
       pid2=abs(encoderValue2*y-e2dd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*y)<(e2dd+500)&((encoderValue2)*y)>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>e2dd&b)
     {
        pid2=abs(((encoderValue2)*y)-e2dd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*y)<(e2dd+500)&((encoderValue2)*y)>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(e2dd+500)&((encoderValue2)*y)>(e2dd-500)&val2<(e2dd+500)&val2>(e2dd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<e2dd&c)
      { 
       pid3=abs(encoderValue3*z-e2dd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3*z<(e2dd+500)&encoderValue3*z>(e2dd-500)&val3<(e2dd+500)&val3>(e2dd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>e2dd&c)
     {
        pid3=abs(encoderValue3*z-e2dd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3*z<(e2dd+500)&encoderValue3*z>(e2dd-500)&val3<(e2dd+500)&val3>(e2dd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(e2dd+500)&encoderValue3*z>(e2dd-500)&val3<(e2dd+500)&val3>(e2dd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<e2dd&d)
      { 
       pid4=abs((encoderValue4*w)-e2dd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4*w)<(e2dd+200)&(encoderValue4*w)>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>e2dd&d)
     {
        pid4=abs((encoderValue4*w)-e2dd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4*w)<(e2dd+200)&(encoderValue4*w)>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(e2dd+200)&(encoderValue4*w)>(e2dd-200)&val4<(e2dd+200)&val4>(e2dd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
      if(armpos==0)
                      {setPWM(travel_velocity);
                        // wait till arm reaches initial pos
                        while(digitalRead(laser_sensor) == LOW);
                            //Serial.println(digitalRead(laser_sensor));
                            Serial.println("zero");
                       encoderValue5 = 0;
                       // Serial.println("Reached Zero !");
                        setPWM(0);
                        reqd_pos = -2300;
                        state = 1;
                        for(int ti=millis();millis()<ti+1000;)
                         {myPID.Compute();
                          setPWM(pwm_val); }
                          armpos=1;
                      }    
                     
      
   }
  off();
  delay(1000);     
}
void d2f()
{
    digitalWrite(47,1);
   int x=1;int y=(1);int z=(-1);int w=(-1);
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
    int armpos=0;  
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }
     {
       
      if((encoderValue1)*x<d2fd&a)
      { 
       pid1=abs((encoderValue1)*x-d2fd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,0);
      if((encoderValue1)*x<(d2fd+200)&(encoderValue1)*x>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>d2fd&a)
     {
        pid1=abs((encoderValue1)*x-d2fd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,1);
         if((encoderValue1)*x<(d2fd+200)&(encoderValue1)*x>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(d2fd+200)&(encoderValue1)*x>(d2fd-200)&val1<(d2fd+200)&val1>(d2fd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<d2fd&b)
      { 
       pid2=abs(encoderValue2*y-d2fd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,0);
      if(((encoderValue2)*y)<(d2fd+500)&((encoderValue2)*y)>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>d2fd&b)
     {
        pid2=abs(((encoderValue2)*y)-d2fd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,1);
         if(((encoderValue2)*y)<(d2fd+500)&((encoderValue2)*y)>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(d2fd+500)&((encoderValue2)*y)>(d2fd-500)&val2<(d2fd+500)&val2>(d2fd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<d2fd&c)
      { 
       pid3=abs(encoderValue3*z-d2fd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,0);
      if(encoderValue3*z<(d2fd+500)&encoderValue3*z>(d2fd-500)&val3<(d2fd+500)&val3>(d2fd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>d2fd&c)
     {
        pid3=abs(encoderValue3*z-d2fd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,1);
         if(encoderValue3*z<(d2fd+500)&encoderValue3*z>(d2fd-500)&val3<(d2fd+500)&val3>(d2fd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(d2fd+500)&encoderValue3*z>(d2fd-500)&val3<(d2fd+500)&val3>(d2fd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<d2fd&d)
      { 
       pid4=abs((encoderValue4*w)-d2fd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,0);
      if((encoderValue4*w)<(d2fd+200)&(encoderValue4*w)>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>d2fd&d)
     {
        pid4=abs((encoderValue4*w)-d2fd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,1);
         if((encoderValue4*w)<(d2fd+200)&(encoderValue4*w)>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(d2fd+200)&(encoderValue4*w)>(d2fd-200)&val4<(d2fd+200)&val4>(d2fd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
     
   }
  off();
  delay(1000);   
}
void f2d()
{
    digitalWrite(47,0);
   int x=-1;int y=(-1);int z=(1);int w=(1);
   int a=1;
   int b=1;
   int c=1;
   int d=1;
   int pid1=0;
   int val1=0;
    encoderValue4=0;
      int pid4=0;
      long val4=0;
    int armpos=0;  
     encoderValue3=0;
      int pid3=0;
      long val3=0;
    encoderValue2=0;
      int pid2=0;
      long val2=0;
    encoderValue1=0;
   while((c==1)&&(a==1)&&(b==1)&&(d==1))
   {Serial.print(encoderValue1); Serial.print("/");Serial.print(encoderValue2);Serial.print("/");Serial.print(encoderValue3);Serial.print("/");Serial.print(encoderValue4);Serial.print("/");Serial.print(a);Serial.print("/");Serial.print(b);Serial.print("/");Serial.print(c);Serial.print("/");Serial.println(d);
    
           
                          
       if((abs(encoderValue1)<10000)||(abs(encoderValue2)<10000)||(abs(encoderValue3)<10000)||(abs(encoderValue4)<10000))
    {
      sp1=sp2; 
    }
    else
    {
      sp1=sp1m;
    }         
       
       
     {
       
      if((encoderValue1)*x<f2dd&a)
      { 
       pid1=abs((encoderValue1)*x-f2dd)*2.5;
       if(pid1>sp1)
        pid1=sp1;
       analogWrite(pwm1,pid1);
       digitalWrite(dir1,1);
      if((encoderValue1)*x<(f2dd+200)&(encoderValue1)*x>(f2dd-200)&val1<(f2dd+200)&val1>(f2dd-200))
      { 
       analogWrite(pwm1,0);
       a=0;
      }
      }
      if((encoderValue1)*x>f2dd&a)
     {
        pid1=abs((encoderValue1)*x-f2dd)*2.5;
         if(pid1>sp1)
         pid1=sp1;
        analogWrite(pwm1,pid1);
         digitalWrite(dir1,0);
         if((encoderValue1)*x<(f2dd+200)&(encoderValue1)*x>(f2dd-200)&val1<(f2dd+200)&val1>(f2dd-200))
         { analogWrite(pwm1,0);
          a=0;
         } 
     }
   if((encoderValue1)*x<(f2dd+200)&(encoderValue1)*x>(f2dd-200)&val1<(f2dd+200)&val1>(f2dd-200))
    { 
     a=0;
     analogWrite(pwm1,0);
     }
      val1=(encoderValue1)*x;
  }
     
    {
       
      if((encoderValue2*y)<f2dd&b)
      { 
       pid2=abs(encoderValue2*y-f2dd)*2.5;
       if(pid2>sp1)
        pid2=sp1;
       analogWrite(pwm2,pid2);
       digitalWrite(dir2,1);
      if(((encoderValue2)*y)<(f2dd+500)&((encoderValue2)*y)>(f2dd-500)&val2<(f2dd+500)&val2>(f2dd-500))
      { 
       analogWrite(pwm2,0);
       b=0;
      }
      }
      if(((encoderValue2)*y)>f2dd&b)
     {
        pid2=abs(((encoderValue2)*y)-f2dd)*2.5;
         if(pid2>sp1)
         pid2=sp1;
        analogWrite(pwm2,pid2);
         digitalWrite(dir2,0);
         if(((encoderValue2)*y)<(f2dd+500)&((encoderValue2)*y)>(f2dd-500)&val2<(f2dd+500)&val2>(f2dd-500))
         { analogWrite(pwm2,0);
          b=0;
         } 
     }
   if(((encoderValue2)*y)<(f2dd+500)&((encoderValue2)*y)>(f2dd-500)&val2<(f2dd+500)&val2>(f2dd-500))
    { 
     b=0;
     analogWrite(pwm2,0);
     }
      val2=((encoderValue2)*y);
  }
     

     {
       
      if(encoderValue3*z<f2dd&c)
      { 
       pid3=abs(encoderValue3*z-f2dd)*2.5;
       if(pid3>sp1)
        pid3=sp1;
       analogWrite(pwm3,pid3);
       digitalWrite(dir3,1);
      if(encoderValue3*z<(f2dd+500)&encoderValue3*z>(f2dd-500)&val3<(f2dd+500)&val3>(f2dd-500))
      { 
       analogWrite(pwm3,0);
       c=0;
      }
      }
      if(encoderValue3*z>f2dd&c)
     {
        pid3=abs(encoderValue3*z-f2dd)*2.5;
         if(pid3>sp1)
         pid3=sp1;
        analogWrite(pwm3,pid3);
         digitalWrite(dir3,0);
         if(encoderValue3*z<(f2dd+500)&encoderValue3*z>(f2dd-500)&val3<(f2dd+500)&val3>(f2dd-500))
         { analogWrite(pwm3,0);
          c=0;
         } 
     }
   if(encoderValue3*z<(f2dd+500)&encoderValue3*z>(f2dd-500)&val3<(f2dd+500)&val3>(f2dd-500))
    { 
     c=0;
     analogWrite(pwm3,0);
     }
      val3=encoderValue3*z;
  }
     {
       
      if((encoderValue4*w)<f2dd&d)
      { 
       pid4=abs((encoderValue4*w)-f2dd)*2.5;
       if(pid4>sp1)
        pid4=sp1;
       analogWrite(pwm4,pid4);
       digitalWrite(dir4,1);
      if((encoderValue4*w)<(f2dd+200)&(encoderValue4*w)>(f2dd-200)&val4<(f2dd+200)&val4>(f2dd-200))
      { 
       analogWrite(pwm4,0);
       d=0;
      }
      }
      if((encoderValue4*w)>f2dd&d)
     {
        pid4=abs((encoderValue4*w)-f2dd)*2.5;
         if(pid4>sp1)
         pid4=sp1;
        analogWrite(pwm4,pid4);
         digitalWrite(dir4,0);
         if((encoderValue4*w)<(f2dd+200)&(encoderValue4*w)>(f2dd-200)&val4<(f2dd+200)&val4>(f2dd-200))
         { analogWrite(pwm4,0);
          d=0;
         } 
     }
   if((encoderValue4*w)<(f2dd+200)&(encoderValue4*w)>(f2dd-200)&val4<(f2dd+200)&val4>(f2dd-200))
    { 
     d=0;
     analogWrite(pwm4,0);
     }
      val4=(encoderValue4*w);
  }
       if(armpos==0)
                      {setPWM(travel_velocity);
                        // wait till arm reaches initial pos
                        while(digitalRead(laser_sensor) == LOW);
                            //Serial.println(digitalRead(laser_sensor));
                            Serial.println("zero");
                       encoderValue5 = 0;
                       // Serial.println("Reached Zero !");
                        setPWM(0);
                        reqd_pos = -2300;
                        state = 1;
                        for(int ti=millis();millis()<ti+1000;)
                         {myPID.Compute();
                          setPWM(pwm_val); }
                          armpos=1;
                      }    
                     
      
   }
  off();
  delay(1000);   
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
long us5()
{
  digitalWrite(trigPin5, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin5, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin5, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration5 = pulseIn(echoPin5, HIGH);

// Calculating the distance
distance5= duration5*0.034/2*10;
  return(distance5);
}
void calib1()
{
 
  
   while(us1()<235|us1()>245|us2()<235|us2()>245|abs(us1()-us2())>5)
 {
 Serial.print(us1()); Serial.print("/");Serial.println(us2());
  if((us1()>245)&&(us2()>245))
  {  
    left();
  }
  if((us1()<235)&&(us2()<235))
  {
    right();
  }
 
    if(((us1()<245&us1()>235)|(us2()<245&us2()>235))&(abs(us1()-us2())>5))
   {
     if(us1()>us2())
    { 
    leftturn();
    Serial.println("right");
    delay(50);
     }
    if(us2()>us1())
     { 
    rightturn();
    Serial.println("left");
    delay(50);
    }
      }
    
 }
 off();
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
    delay(500);}
    else
    break;
    }
// wall();
// delay(5000);
  off();
 while(digitalRead(53)!=1)
{ right1();
digitalWrite(13,0);
}
digitalWrite(13,1);
 delay(750);
 off();
 e1=50;
  e2=10;
  
  while(1)
   { Serial.println("while");
      e2=e1;
         Serial.print("e2==");Serial.println(e2);
    e1=us3();
    Serial.print("e1==");Serial.print(e1);
    if(abs(e1-e2)>5)
   { wall();
    delay(500);}
    else
    break;
    }
// wall();
// delay(5000);
  off();




Serial.println("done");
 }
void calib3()
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
    delay(500);}
    else
    break;
   }
//wall();
//delay(5000);
  off();
  while(digitalRead(53)!=1)
{ right1();
digitalWrite(13,0);
}
digitalWrite(13,1);
 delay(750);
 off();
 
  e1=50;
  e2=10;
  
  while(1)
   { Serial.println("while");
      e2=e1;
         Serial.print("e2==");Serial.println(e2);
    e1=us3();
    Serial.print("e1==");Serial.print(e1);
    if(abs(e1-e2)>5)
   { wall();
    delay(500);}
    else
    break;
  }
  
// wall();
// delay(8c000);
  off();



 



Serial.println("done");
 }
void calib4()
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
    delay(750);}
    else
    break;
  }
  
// wall();
// delay(8c000);
  off();
   while(digitalRead(53)!=1)
{ right1();
digitalWrite(13,0);
}
digitalWrite(13,1);
 delay(750);
 off();
 
 e1=50;
 e2=10;
  
  while(1)
   { Serial.println("while");
      e2=e1;
         Serial.print("e2==");Serial.println(e2);
    e1=us3();
    Serial.print("e1==");Serial.print(e1);
    if(abs(e1-e2)>5)
   { wall();
    delay(500);}
    else
    break;
  }
  
// wall();
// delay(8c000);
  off();
Serial.println("done");

}

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
void left1()
{
    analogWrite(pwm1,100);//m1
    analogWrite(pwm2,100);//m2
     analogWrite(pwm3,100);//m1
    analogWrite(pwm4,100);//m2
   
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,1);//m2
    digitalWrite(dir3,1);//m3
    digitalWrite(dir4,1);//m4
  
  
}
void right1()
{ 
    analogWrite(pwm1,100);//m1
    analogWrite(pwm2,125);//m2
     analogWrite(pwm3,100);//m1
    analogWrite(pwm4,125);//m2
   
    digitalWrite(dir1,0);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,0);//m4
  
  
}

void loop()
{ //Serial.println(us4());

//Serial.print("us4=");Serial.print(us4());Serial.print("////us5=");Serial.println(us5());
// 
 
 while(l==0)
                      {setPWM(travel_velocity);
                        // wait till arm reaches initial pos
                        while(digitalRead(laser_sensor) == LOW);
                            //Serial.println(digitalRead(laser_sensor));
                            Serial.println("zero");
                       encoderValue5 = 0;
                       // Serial.println("Reached Zero !");
                        off();
                        l=1;
                      }    
 if(Serial.available())
  {
    if(Serial.read()=='1')
    {
      throw1();
      delay(2000);
    }
    if(Serial.read()=='2')
    {
      throw2();
      delay(2000);
    }
    if(Serial.read()=='3')
    {
      throw3();
      delay(2000);
    }
    if(Serial.read()=='0')
    {
      off();
    }
  }
//  delay(5000);
//  {digitalWrite(13,0);
//  align=0;}
//
//    a2b();
//   
//    calib1();
//       
//            while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//           { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//         grip(); delay(1000);
//          }
//           
//         {digitalWrite(13,0);
//         align=0;}
//   b2c();
//   calib2();
//   throw1();
//   wback();
//   delay(1000);
//   off();
//   c2b();
//   calib1();   
//      while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//           { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//       {digitalWrite(13,0);
//       align=0;
//       }
//      while(sring==1)
//      {
//       b2c();
//       calib2();
//       throw1();
//        wback();
//         delay(1000);
//         off();
//         c2b();
//         calib1();
//        while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//            { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//           {digitalWrite(13,0);
//       align=0;
//       }
//      }
//    b2d();
//     calib1();
//    d2e();
//    calib3();
//     throw2();
//      wback();
//     delay(1500);
//     off();
//       e2d();
//        calib1();
//       while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//            { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//           {digitalWrite(13,0);
//             align=0;
//       }
//         while(sring==1)
//         {
//           d2e();
//           calib3();
//            throw2();
//             wback();
//           delay(1500);
//           off();
//           e2d();
//           calib1();
//           while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//           { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//           {digitalWrite(13,0);
//       align=0;
//       }
//         }
//         calib1();
//          d2f();
//          calib4();
//          throw3();
//          wback();
//          delay(1500);
//          off();
//          
//          f2d();
//          calib1();
//      while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//            { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//           {digitalWrite(13,0);
//       align=0;}
//       
//         while(sring==1)
//         {
//           d2f();
//           calib4();
//            throw3();
//             wback();
//           delay(1500);
//           
//           off();
//           f2d();
//           calib1();
//           while(1)
//          {
//            if (digitalRead(flap)==1)
//          { align=1;digitalWrite(13,1);break;}
//          else
//          { align=0;digitalWrite(13,0);}
//          }
//           if(align==0)
//            { off();digitalWrite(valve,1);}
//         if(align==1)
//         {delay(1000);
//          grip(); delay(1000);
//          }
//           {digitalWrite(13,0);
//       align=0;
//       }
//         }
//     delay(1000000000000);   
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

