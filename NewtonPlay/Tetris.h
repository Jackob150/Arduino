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

#define LEN 4
#define N_SHAPES 7

enum Shape
{
    LINE,
    SQUARE,
    T_BLOCK,
    S_BLOCK_1,
    S_BLOCK_2,
    L_BLOCK_1,
    L_BLOCK_2
};

struct Block
{
    struct Point pixels[LEN];
    struct Point idp;
    int shape;
    int orient;
};

class Tetris
{
    public:
        Tetris();
        
        virtual void button_action(MyDisp * screen, int button);
        virtual void screen_display(MyDisp * screen);

        void print_outer_menu(MyDisp * screen);
        void print_menu(MyDisp * screen);
        void print_score(MyDisp * screen);
        void print_game(MyDisp * screen);

        void draw_block();
        void move_block(MyDisp * screen, int dir);
        void rotate_block(MyDisp * screen);
        void update_ground();
        void check_line();

        void copy_block(struct Block * copy_to, struct Block * copy_from);
        int set_block(struct Block * block, int x, int y, int shape, int orient);
        int validate_ground(struct Block * block);

        int get_state();
        void set_state(int state);

    private:
        struct Block _block;
        int _ground[M_SIZE][M_SIZE];
        int _state;
        int _score;
        int _delay;
        int _diff;
};

#endif