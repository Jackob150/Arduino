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

class Snake
    : public Game
{
    public:
        Snake();

        virtual void button_action(MyDisp * screen, int button);
        virtual void screen_display(MyDisp * screen);

        void print_outer_menu(MyDisp * screen);
        void print_menu(MyDisp * screen);
        void print_score(MyDisp * screen);
        void print(MyDisp * screen);

        void move();
        void check_bounds(MyDisp * screen);
        void check_tail(MyDisp * screen);
        void check_apple();
        void place_apple();
        void put_apple();
        void game_over(MyDisp * screen);

        int get_state();
        void set_state(int state);

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