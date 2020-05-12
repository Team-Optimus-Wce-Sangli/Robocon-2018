void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Serial1.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    char c=Serial.read();
    Serial1.write(c);
    Serial.println(c);
  }
  // put your main code here, to run repeatedly:

}
