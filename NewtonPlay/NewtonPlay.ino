#include "ShiftReg.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Chooser.h"

#define DEBOUNCER 150

ShiftReg disp = ShiftReg(5, 6, 7, 11);
ShiftReg ref = ShiftReg(8, 9, 10, 12);
MyDisp screen = MyDisp(&disp, &ref, 1);
Controller contr = Controller(14, 15, 16, 17, 2);
Chooser chooser = Chooser();

volatile unsigned long button_pressed = 0;

void interrupt_action()
{
    if (millis() - button_pressed > DEBOUNCER) {
        button_pressed = millis();
        chooser.button_action(&screen, contr.check_buttons());
    }
}

void setup() {
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(contr.get_interrupt()),interrupt_action ,FALLING);

    screen.empty_screen();
}

void loop() {
    chooser.screen_display(&screen);
}
