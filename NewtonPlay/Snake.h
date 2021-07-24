/*
  Snake.h - Snake Game for NewtonPlay.
  Created by Jakub Ciesielski, 24.07.2021.
*/
#ifndef Snake_h
#define Snake_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"

#define MAX_LEN 64

enum State {
    MENU,
    PLAY
};

struct Point
{
    int x, y;
};

class Snake
    : public Game
{
    public:
        Snake();

        virtual void button_action(int button);
        virtual void screen_display(MyDisp * screen);

        void print_menu(MyDisp * screen);
        void print_score(MyDisp * screen);
        void print(MyDisp * screen);
        void move();
        void check_bounds();
        void check_tail();
        void check_apple();
        void place_apple();
        void game_over();

    private:
        struct Point _snake_arr[MAX_LEN];
        struct Point _tail;
        struct Point _apple;
        int _len;
        int _dir;
        int _speed;
        int _points;
        int _state;
        int _diff;
};

#endif