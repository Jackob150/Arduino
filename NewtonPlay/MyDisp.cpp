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

void MyDisp::print_digit(int x, int y, int digit)
{
    switch (digit) {
        case 0:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x, y + 3);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            break;
        case 1:
            set_pix(1, x + 2, y);
            set_pix(1, x + 1, y + 1);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 2, y + 4);
            break;
        case 2:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 2);
            set_pix(1, x, y + 3);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 1, y + 2);
            break;
        case 3:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 2);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 1, y + 2);
            break;
        case 4:
            set_pix(1, x, y);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x + 1, y + 2);
            set_pix(1, x + 2, y);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 2, y + 4);
            break;
        case 5:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 1, y + 2);
            break;
        case 6:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x, y + 3);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 1, y + 2);
            break;
        case 7:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 2, y + 4);
            break;
        case 8:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x, y + 3);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 1, y + 2);
            break;
        case 9:
            set_pix(1, x, y);
            set_pix(1, x + 1, y);
            set_pix(1, x + 2, y);
            set_pix(1, x, y + 4);
            set_pix(1, x + 1, y + 4);
            set_pix(1, x + 2, y + 4);
            set_pix(1, x, y + 1);
            set_pix(1, x, y + 2);
            set_pix(1, x + 2, y + 1);
            set_pix(1, x + 2, y + 2);
            set_pix(1, x + 2, y + 3);
            set_pix(1, x + 1, y + 2);
            break;
    }
}

void MyDisp::set_letter(char c)
{
    empty_screen(false);
    if (c == 'S') {
        for (int i = 2; i <= M_SIZE - 1; i++) {
            set_pix(1, i, 1);
            set_pix(1, i, 2);
            set_pix(1, i, 4);
            set_pix(1, i, 5);
            set_pix(1, i, 7);
            set_pix(1, i, 8);
        }
        set_pix(1, 2, 3);
        set_pix(1, 3, 3);
        set_pix(1, 6, 6);
        set_pix(1, 7, 6);
    } else if (c == 'T') {
        for (int i = 2; i <= M_SIZE - 1; i++) {
            set_pix(1, i, 2);
            set_pix(1, i, 3);
            set_pix(1, 4, i);
            set_pix(1, 5, i);
        }
    }
}