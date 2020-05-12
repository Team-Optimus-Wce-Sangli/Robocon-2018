void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
 
    digitalWrite(dir1,1);//m1
    digitalWrite(dir2,0);//m2
    digitalWrite(dir3,0);//m3
    digitalWrite(dir4,1);//m4
    encoderValue1=encoderValue2=encoderValue3=encoderValue4=0;
   while(abs(encoderValue1<20000)|abs(encoderValue2<20000)|abs(encoderValue3<20000)|abs(encoderValue4<20000))
   {
    if(abs(encoderValue1<20000))
    analogWrite(pwm1,sp1);
    else
     analogWrite(pwm1,0);
      if(abs(encoderValue2<20000))
    analogWrite(pwm2,sp2);
    else
     analogWrite(pwm2,0);
      if(abs(encoderValue3<20000))
    analogWrite(pwm3,sp3);
    else
     analogWrite(pwm3,0);
      if(abs(encoderValue4<20000))
    analogWrite(pwm4,sp4);
    else
     analogWrite(pwm4,0);
   }
}
