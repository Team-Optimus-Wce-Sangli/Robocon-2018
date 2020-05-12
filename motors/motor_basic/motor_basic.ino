void setup() {
  // put your setup code here, to run once:
  pinMode(
2,OUTPUT);
pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8,1);
  analogWrite(9,100);
  delay(2000);
  analogWrite(3,0);
  delay(10000);
  

}
