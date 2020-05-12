int sp1=100;
int sp2=100;
int sp3=100;
int sp4=100;
int sp5=200;
int sp6=50;
int tspeed=50;
int i=0;
int j=0;
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
long duration1;//us1
int distance1;//us1
long duration2;//us2
int distance2;//us2
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
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
const int trigPin1 = 15;//ultrasonic1
const int echoPin1 = 16;//us1
const int trigPin2 = 20;//us2
const int echoPin2 = 21;//us2
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
void loop() {
  Serial.println(us1()); Serial.print("/");Serial.println(us2());
//  // put your main code here, to run repeatedly:
// while(us1()<248|us1()>252|us2()<248|us2()>252|abs(us1()-us2())>3)
// {
// Serial.println(us1()); Serial.print("/");Serial.println(us2());
//  if(us1()>252&us2()>252)
//  {  
//    left();
//  }
//  if(us1()<248&us2()<248)
//  {
//    right();
//  }
// 
//  if(abs(us1()-us2())>3)
// {
//   if(us1()>us2())
//  { 
//  leftturn();
//  delay(50);
//   }
//  if(us2()>us1())
//   { 
//  rightturn();
//  delay(50);
//  }
//    }
// }
// off();
}
