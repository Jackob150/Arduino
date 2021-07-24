/*
  Controller.cpp - Library for 4-button controller to NewtonPlay console.
  Created by Jakub Ciesielski, 22.07.2021.
*/

#include "Arduino.h"
#include "Controller.h"

Controller::Controller(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t interrupt)
{
    pinMode(up, INPUT);
    _l_buttons[UP] = up;
    pinMode(down, INPUT);
    _l_buttons[DOWN] = down;
    pinMode(left, INPUT);
    _l_buttons[LEFT] = left;
    pinMode(right, INPUT);
    _l_buttons[RIGHT] = right;
    pinMode(interrupt, INPUT);
    _interrupt = interrupt;
}

uint8_t Controller::get_up()
{
    return _l_buttons[UP];
}

uint8_t Controller::get_down()
{
    return _l_buttons[DOWN];
}

uint8_t Controller::get_left()
{
    return _l_buttons[LEFT];
}

uint8_t Controller::get_right()
{
    return _l_buttons[RIGHT];
}

uint8_t Controller::get_interrupt()
{
    return _interrupt;
}

int Controller::check_buttons()
{
    int button_pressed;
    for (int button = UP; button <= RIGHT; button++) {
        if (!digitalRead(_l_buttons[button])) {
            button_pressed = button;
            break;
        }
    }

    return button_pressed;
}