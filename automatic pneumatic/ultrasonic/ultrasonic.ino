#define trigpin 33
#define echopin 31

long duration1;                                                                                                                                                                                                                                     
float distance1;
int i =0;
int average = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigpin,OUTPUT);//trigpin
pinMode(echopin,INPUT);//echopin
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigpin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echopin, HIGH);

// Calculating the distance
distance1= duration1*0.034/2*10;
 Serial.println(distance1);
 
}

