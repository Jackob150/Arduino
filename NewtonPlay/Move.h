/*
  Move.h - Simple Game class implementation for presentation purposes.
  Created by Jakub Ciesielski, 22.07.2021.
*/
#ifndef Move_h
#define Move_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"

class Move
    : public Game
{
    public:
        Move(int x, int y);

        int get_x();
        int get_y();

        void set_x(int x);
        void set_y(int y);

        virtual void button_action(int button);
        virtual void screen_display(MyDisp * screen);

    private:
        int _x;
        int _y;
};

#endif