#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(10,11);


void setup() {
  // put your setup code here, to run once:
 ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ps2.readButton(PS2_UP) == 0) // 0 = pressed, 1 = released
  {
    Serial.write('A');
   delay(200);
  }
    if(ps2.readButton(PS2_DOWN) == 0) // 0 = pressed, 1 = released
  {
    Serial.write('B');
   delay(200);
  }
    if(ps2.readButton(PS2_RIGHT_1) == 0) // 0 = pressed, 1 = released
  {
    Serial.write('C');
   delay(200);
  }
    if(ps2.readButton(PS2_LEFT_1) == 0) // 0 = pressed, 1 = released
  {
    Serial.write('D');
   delay(200);
  }
    if(ps2.readButton(PS2_RIGHT_2) == 0) // 0 = pressed, 1 = released
  {
    Serial.write('E');
   delay(200);
  }
}
