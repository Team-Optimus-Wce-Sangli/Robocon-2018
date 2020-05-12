//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;
int rev=0;
long val;
long val1;

int i=0;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int rpm;
long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
int tm[100];
void setup() {
  Serial.begin (115200);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
 pinMode(8, OUTPUT); 
  pinMode(9,OUTPUT);
pinMode(4,OUTPUT);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
while(!Serial.available());
}

void loop(){ 
  //Do stuff here
digitalWrite(8,1);
analogWrite(9,120);

val=abs(encoderValue);
Serial.println(val);
val1=35000;


//
if(abs(encoderValue)>val1)
{digitalWrite(4,1);
analogWrite(9,0);
Serial.println("tr");
delay(1000);
digitalWrite(4,0);
delay(1000);

delay(1000000);
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
