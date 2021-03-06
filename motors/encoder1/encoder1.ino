//these pins can not be changed 2/3 are special pins
int encoderPin1 = 22;
int encoderPin2 = 23;
int rev=0;
int val=0;
int val1=0;
int t=0;
int j=0;
int t1=0;int t2=0;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int rpm;
long lastencoderValue = 0;
int i=1;
int lastMSB = 0;
int lastLSB = 0;
int tm[100];
void setup() {
  Serial.begin (115200);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
 pinMode(8, OUTPUT); 
  pinMode(9,OUTPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){ 
  //Do stuff here
digitalWrite(8,1);
analogWrite(9,254);

if(encoderValue)
{
 val=(encoderValue%9840)*(-1);
 if(val<=15&i)//&i//25-30
 {
  val1=val;
  rev=rev+1;
  delay(20);
  val=(encoderValue%9840)*(-1);
  if(val<val1+20)
  i=0;
  else
  i=1;
} 

}
if(millis()>=30000)
{
 analogWrite(9,0);
 delay(5000); 
}
 
  Serial.println(encoderValue);
 

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
