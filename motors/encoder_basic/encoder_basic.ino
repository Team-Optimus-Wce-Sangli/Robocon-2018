//these pins can not be changed 2/3 are special pins
int encoderPin1 = 23;
int encoderPin2 = 25;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;
 void setup() {
  Serial.begin (9600);
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
pinMode(4,OUTPUT);
 pinMode(22,OUTPUT);
 pinMode(24,OUTPUT);
 analogWrite(4,255);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
 
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(encoderPin1, updateEncoder, CHANGE); 
  attachInterrupt(encoderPin2, updateEncoder, CHANGE);
 }
 
void loop(){ 
  //Do stuff here
  digitalWrite(22,1);
digitalWrite(24,0);
  Serial.println(encoderValue);
 // delay(1000); //just here to slow down the output, and show it will work  even during a delay
}
 
void updateEncoder()
{
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
   if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
  lastEncoded = encoded; //store this value for next time
} 
