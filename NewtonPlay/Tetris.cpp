/*
  Snake.cpp - Snake Game for NewtonPlay.
  Created by Jakub Ciesielski, 24.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "Tetris.h"

Tetris::Tetris()
{
    _state = MENU;
    _score = 0;
    _delay = 1000;
}

void Tetris::button_action(int button)
{

}

void Tetris::screen_display(MyDisp * screen)
{
    
}