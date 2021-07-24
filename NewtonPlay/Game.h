/*
  Game.h - Abstract class for games for NewtonPlay platform.
  Created by Jakub Ciesielski, 22.07.2021.
*/
#ifndef Game_h
#define Game_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"

class Game
{
    public:
        virtual void button_action(int button) = 0;
        virtual void screen_display(MyDisp * screen) = 0;
};

#endif