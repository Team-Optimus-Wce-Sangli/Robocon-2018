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
int encoderPin1 = 62;//1
int encoderPin2 = 63;//1
//int encoderPin3 = 60;//2
//int encoderPin4 = 61;//2
//int encoderPin5 = 62;//3
//int encoderPin6 = 63;//3
//int encoderPin7 = 64;//4
//int encoderPin8 = 65;//4
//int encoderPin9 = 66;//5
//int encoderPin10 = 67;//5
//int encoderPin11 = 68;//6
//int encoderPin12 = 69;//6

//these pins can not be changed 2/3 are special pins

float rev=0;
long  val=0;
float rpm=0;
int t=0;
int j=0;
int t1=0;int t2=0;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;
int i=1;
int lastMSB = 0;
int lastLSB = 0;
int tm[100];
void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
 pinMode(pwm4, OUTPUT); 
  pinMode(dir4,OUTPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(encoderPin1, updateEncoder, CHANGE); 
  attachInterrupt(encoderPin2, updateEncoder, CHANGE);

}

void loop(){ 

 
  {//Do stuff here
digitalWrite(dir3,1);
analogWrite(pwm3,200);
 val=encoderValue;
  rev=val/9840.0;
  rpm=rev*2.0;
 Serial.println(val);
if(abs(val)>100)
{
 
 analogWrite(pwm3,0);
Serial.println("rpm");
Serial.println(rpm); 
 
 delay(30000); 
}
 
  }
 

}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
