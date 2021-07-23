/*
  Controller.h - Library for 4-button controller to NewtonPlay console.
  Created by Jakub Ciesielski, 22.07.2021.
*/
#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

enum buttons {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Controller
{
  public:
    Controller(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t interrupt);

    uint8_t get_up();
    uint8_t get_down();
    uint8_t get_left();
    uint8_t get_right();
    uint8_t get_interrupt();

    int check_buttons();

  private:
    uint8_t _l_buttons[4];
    uint8_t _interrupt;
};

#endif