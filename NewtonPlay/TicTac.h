/*
  TicTac.h - Tic Tac Toe Game for NewtonPlay.
  Created by Jakub Ciesielski, 27.07.2021.
*/
#ifndef TicTac_h
#define TicTac_h

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"

#define T_SIZE 3

enum Mode
{
    SINGLE,
    MULTI
};

enum Difficulty
{
    MONKEY,
    HUMAN,
    GOD
};

class TicTac
{
    public:
        TicTac();

        void button_action(MyDisp * screen, int button);
        void screen_display(MyDisp * screen);

        int get_state();
        void set_state(int state);

        void print_outer_menu(MyDisp * screen);
        void print_menu(MyDisp * screen);
        void print_game(MyDisp * screen);
        void print_winner(MyDisp * screen);

        int check_winner();
        void make_move();
        void move_done();

    private:
        int _table[T_SIZE][T_SIZE];
        int _state;
        int _mode;
        int _diff;
        int _player;
        int _winner;
        int _passage;
        int _field;
        int _moves;
};

#endif