void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial1.available())
  {
    char c=Serial1.read();
    Serial.println(c);
  }
  // put your main code here, to run repeatedly:

}
