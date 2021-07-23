/*
  ShiftReg.cpp - Library for 8-bit shift register.
  Created by Jakub Ciesielski, 22.07.2021.
*/

#include "Arduino.h"
#include "ShiftReg.h"

ShiftReg::ShiftReg(uint8_t ds, uint8_t stcp, uint8_t shcp, uint8_t q7s)
{
    digitalWrite(ds, LOW);
    pinMode(ds, OUTPUT);
    _ds = ds;
    digitalWrite(stcp, LOW);
    pinMode(stcp, OUTPUT);
    _stcp = stcp;
    digitalWrite(shcp, LOW);
    pinMode(shcp, OUTPUT);
    _shcp = shcp;
    digitalWrite(q7s, LOW);
    pinMode(q7s, INPUT);
    _q7s = q7s;
}

uint8_t ShiftReg::get_ds()
{
    return _ds;
}

uint8_t ShiftReg::get_stcp()
{
    return _stcp;
}

uint8_t ShiftReg::get_shcp()
{
    return _shcp;
}

uint8_t ShiftReg::get_q7s()
{
    return _q7s;
}

void ShiftReg::init()
{
    this->write_byte(0, true);
}

int ShiftReg::read_serial()
{
    return digitalRead(_q7s);
}

void ShiftReg::output_parallel()
{
    digitalWrite(_stcp, HIGH);
    delayMicroseconds(1);
    digitalWrite(_stcp, LOW);
}

void ShiftReg::write_bit(int val)
{
    digitalWrite(_ds, val);
    delayMicroseconds(1);
    digitalWrite(_shcp, HIGH);
    delayMicroseconds(1);
    digitalWrite(_shcp, LOW);
}

void ShiftReg::write_byte(uint8_t val, bool disp)
{
    for (int i = R_SIZE; i >= 0; i--) {
        write_bit((val & (1 << i)) >> i);
    }
    if (disp) {
        output_parallel();
    }
}