/*
  Chooser.h - Chooser interface for NewtonPlay.
  Created by Jakub Ciesielski, 26.07.2021.
*/
#ifndef Chooser_h
#define Chooser_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Snake.h"
#include "Tetris.h"
#include "Game.h"

#define N_GAMES 2

enum Games 
{
    SNAKE,
    TETRIS
};

class Chooser
    : public Game
{
    public:
        Chooser();

        virtual void button_action(MyDisp * screen, int button);
        virtual void screen_display(MyDisp * screen);

    private:
        Snake _snake;
        Tetris _tetris;
        int _pointer;
        int _state;
};

#endif