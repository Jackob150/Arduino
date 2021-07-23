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

int MyDisp::get_reg_ds(ShiftReg * reg)
{
    return reg->get_ds();
}

int MyDisp::get_reg_stcp(ShiftReg * reg)
{
    return reg->get_stcp();
}

int MyDisp::get_reg_shcp(ShiftReg * reg)
{
    return reg->get_shcp();
}

int MyDisp::get_reg_q7s(ShiftReg * reg)
{
    return reg->get_q7s();
}

int MyDisp::get_refresh_delay()
{
    return _refresh_delay;
}

void MyDisp::set_refresh_delay(int delay)
{
    _refresh_delay = delay;
}

void MyDisp::display()
{
    for (int i = 0; i < M_SIZE; i++) {
        _ref->write_byte(~(1 << i));
        _disp->write_byte(disp_arr[i]);
        delay(_refresh_delay);
        _disp->write_byte(0);
    }
}

void MyDisp::sleep(int miliseconds)
{
    int cnt = 0;
    while (11 * cnt < miliseconds) {
        this->display();
        cnt += _refresh_delay;
    }
}

void MyDisp::empty_screen(bool disp)
{
    for (int i = 0; i < M_SIZE; i++) {
        disp_arr[i] = 0;
    }
    if (disp) {
        this->display();
    }
}

void MyDisp::set_pix(int val, int x, int y)
{
    if (val) {
        disp_arr[y - 1] |= 1 << (M_SIZE - x);
    } else {
        disp_arr[y - 1] &= ~(1 << (M_SIZE - x));
    }
}