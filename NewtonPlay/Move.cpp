/*
  Move.cpp - Simple Game class implementation for presentation purposes.
  Created by Jakub Ciesielski, 22.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "Move.h"

Move::Move(int x, int y)
{
    _x = x;
    _y = y;
}

int Move::get_x()
{
    return _x;
}

int Move::get_y()
{
    return _y;
}

void Move::set_x(int x)
{
    _x = x;
}

void Move::set_y(int y)
{
    _y = y;
}

void Move::button_action(int button)
{
    switch (button) {
        case UP:
            _y -=1;
            if (_y <= 0) {
                _y += 8;
            }
            break;
        case DOWN:
            _y = (_y % 8) + 1;
            break;
        case LEFT:
            _x -= 1;
            if (_x <= 0) {
                _x += 8;
            }
            break;
        case RIGHT:
            _x = (_x % 8) + 1;
            break;
    }
}

void Move::screen_display(MyDisp * screen)
{
    screen->empty_screen();
    screen->set_pix(1, _x, _y);
    screen->display();
}