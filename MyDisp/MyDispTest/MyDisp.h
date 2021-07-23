/*
  MyDisp.h - Library for 8x8 LED matrix.
  Created by Jakub Ciesielski, 22.07.2021.
*/
#ifndef MyDisp_h
#define MyDisp_h

#include "Arduino.h"
#include "ShiftReg.h"

#define M_SIZE 8

class MyDisp
{
    public:
        MyDisp(ShiftReg * disp, ShiftReg * ref, int refresh_delay);

        uint8_t disp_arr[M_SIZE];

        /*int get_refresh_delay();
        int get_reg_ds(ShiftReg * reg);
        int get_reg_stcp(ShiftReg * reg);
        int get_reg_shcp(ShiftReg * reg);
        int get_reg_q7s(ShiftReg * reg);
        int set_refresh_delay(int delay);*/

        void display();

    private:
        ShiftReg * _disp;
        ShiftReg * _ref;
        int _refresh_delay;
};

#endif