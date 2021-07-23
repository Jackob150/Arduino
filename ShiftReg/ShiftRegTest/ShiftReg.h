/*
  ShiftReg.h - Library for 8-bit shift register.
  Created by Jakub Ciesielski, 22.07.2021.
*/
#ifndef ShiftReg_h
#define ShiftReg_h

#include "Arduino.h"

class ShiftReg
{
  public:
    ShiftReg(uint8_t ds, uint8_t stcp, uint8_t shcp, uint8_t q7s);

    uint8_t get_ds();
    uint8_t get_stcp();
    uint8_t get_shcp();
    uint8_t get_q7s();

    void init();
    int read_serial();
    void write_bit(int val);
    void write_byte(uint8_t byte, bool disp);
    void output_parallel();

  private:
    uint8_t _ds;        //serial input pin
    uint8_t _stcp;      //storage clock input pin
    uint8_t _shcp;      //shift register input pin
    uint8_t _q7s;       //serial output pin
};

#endif