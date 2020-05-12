#define motor1p 3
#define motor2p 9
#define motor3p 6
#define motor4p 5

#define motor1d A0
#define motor2d A3
#define motor3d A2
#define motor4d A1

void setup() {
  // put your setup code here, to run once:
pinMode(motor1d,OUTPUT);
pinMode(motor2d,OUTPUT);
pinMode(motor3d,OUTPUT);
pinMode(motor4d,OUTPUT);

}
void setDir(int motorpin,int dir){
  digitalWrite(motorpin,dir);
}
void setSpd(byte sp){
  if(sp){
  analogWrite(motor1p,255);
  analogWrite(motor2p,255);
  analogWrite(motor3p,255);
  analogWrite(motor4p,255);
  }
  delay(100);
  for(int i = 0;i<= 100; i++){
    analogWrite(motor1p,sp);
    analogWrite(motor2p,sp);
    analogWrite(motor3p,sp);
    analogWrite(motor4p,sp);
  }
}

void forward(int t,byte sp){
  setDir(motor1d,1);
  setDir(motor2d,0);
  setDir(motor3d,1);
  setDir(motor4d,0);
  setSpd(sp);
  delay(t);
  setSpd(0);
}
void backward(int t, byte sp){
  setDir(motor1d,0);
  setDir(motor2d,1);
  setDir(motor3d,0);
  setDir(motor4d,1);
  setSpd(sp);
  delay(t);
  setSpd(0);
}
void right(int t, byte sp){
  setDir(motor1d,0);
  setDir(motor2d,0);
  setDir(motor3d,0);
  setDir(motor4d,0);
  setSpd(sp);
  delay(t);
  setSpd(0);
}
void left(int t, byte sp){
  setDir(motor1d,1);
  setDir(motor2d,1);
  setDir(motor3d,1);
  setDir(motor4d,1);
  setSpd(sp);
  delay(t);
  setSpd(0);
  delay(5000);
}
void loop() {
  // put your main code here, to run repeatedly:
  forward(1000,230);
  delay(1000);
  backward(1000,230);
  delay(1000);
  right(1000,230);
  delay(1000);
  left(1000,230);
  delay(1000);
}
