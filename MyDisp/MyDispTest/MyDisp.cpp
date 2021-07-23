/*
  MyDisp.cpp - Library for 8x8 LED matrix.
  Created by Jakub Ciesielski, 22.07.2021.
*/

#include "Arduino.h"
#include "ShiftReg.h"
#include "MyDisp.h"

MyDisp::MyDisp(ShiftReg * disp, ShiftReg * ref, int refresh_delay)
{
    for (int i = 0; i < M_SIZE; i++) {
        disp_arr[i] = 0;
    }
    _disp = disp;
    _ref = ref;
    _refresh_delay = refresh_delay;
}

void MyDisp::display()
{
    for (int i = 0; i < M_SIZE; i++) {
        _ref->write_byte(~(1 << i), true);
        _disp->write_byte(disp_arr[i], true);
        delay(_refresh_delay);
        _disp->write_byte(0, true);
    }
}