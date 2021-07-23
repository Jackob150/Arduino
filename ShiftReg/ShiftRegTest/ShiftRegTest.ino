#include "ShiftReg.h"

ShiftReg sr = ShiftReg(10, 8, 7, 12);
int counter = 0;

void setup() {
  Serial.begin(9600);
  sr.init(HIGH);
  delay(1000);
  int val = 4;
  sr.write_byte(val, true);
  delay(1000);
}

void loop() {
  if (counter % 8)
  {
    sr.write_bit(0);
  } else {
    sr.write_bit(1);
  }
  sr.output_parallel();
  counter++;
  delay(500);
}
