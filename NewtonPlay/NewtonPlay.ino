#include "ShiftReg.h"
#include "MyDisp.h"
#include "Controller.h"

ShiftReg disp = ShiftReg(5, 6, 7, 11);
ShiftReg ref = ShiftReg(8, 9, 10, 12);
MyDisp screen = MyDisp(&disp, &ref, 1);
Controller contr = Controller(14, 15, 16, 17, 2);

volatile int p_x = 4;
volatile int p_y = 4;

void interrupt_action()
{
    game.button_action(contr.check_buttons());
}

void setup() {
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(contr.get_interrupt()),interrupt_action ,FALLING);

    screen.empty_screen();
}

void loop() {
    screen.set_pix(1, p_x, p_y);
    screen.display();
}
