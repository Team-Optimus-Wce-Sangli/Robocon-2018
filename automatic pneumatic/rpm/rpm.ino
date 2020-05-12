//these pins can not be changed 2/3 are special pins
#define dir 8
#define pwm 9
#define valve 4
#define release_rev 5.1
#define r_dir 1
int encoderPin1 = 2;
int encoderPin2 = 3;
double rev=0;
long  val=0;
float rpm=0;
long int t=0;
int j=0;
int t1=0;int t2=0;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long encount;
long lastencoderValue = 0;
int i=1;
int lastMSB = 0;
int lastLSB = 0;
int tm[100];
int diff = 0;
int len=0;
void setup() {
  Serial.begin (115200);
  while(Serial.available() <= 0);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  pinMode(dir, OUTPUT); 
  pinMode(pwm,OUTPUT);
  
  pinMode(valve,OUTPUT);
  digitalWrite(valve,LOW);
  
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

  digitalWrite(dir,r_dir);
  analogWrite(pwm,0
  
  
  
  
  );

}

void loop(){ 
  //Do stuff here
  len = val;
  t = millis();
  delay(20);
  val=encoderValue;
  diff = val - len;
  //rev=val/12000.0;
  //rev=diff*360.0/12000.0;
  //rpm=rev*2;
  //rpm = rev*1000.0/(millis() - t)*60.0/2.0/3.1415;
  rpm = diff*0.0591;
  Serial.println(encoderValue);
 /* if(abs(rev)>release_rev)
 {
    analogWrite(pwm,0);
    digitalWrite(valve,HIGH); 
    delay(1000);
    analogWrite(pwm,0);
    digitalWrite(valve,LOW);
    delay(1000000);
 }*/
 
 
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) 
    encoderValue ++;
  //if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
  else encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
