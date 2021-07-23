#include "ShiftReg.h"
#include "MyDisp.h"

ShiftReg disp = ShiftReg(5, 6, 7, 12);
ShiftReg ref = ShiftReg(2, 3, 4, 11);
MyDisp screen = MyDisp(&disp, &ref, 1);

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 8; i++) {
        screen.disp_arr[i] = 1 << i; 
    }
}

void loop() {
    screen.display();
}
