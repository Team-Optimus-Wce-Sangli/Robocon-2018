void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(4,1);
delay(1000);
digitalWrite(4,0);
delay(10000);
}
