/*
  Tetris.h - Tetris Game for NewtonPlay.
  Created by Jakub Ciesielski, 24.07.2021.
*/
#ifndef Tetris_h
#define Tetris_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"

class Tetris
{
    public:
        Tetris();
        
        virtual void button_action(int button);
        virtual void screen_display(MyDisp * screen);
};