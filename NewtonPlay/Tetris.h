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

#define MAX_SIZE 64
#define LEN 4

enum State
{
    MENU,
    PLAY
};

enum Shape
{
    LINE,
    SQUARE,
    T_BLOCK,
    S_BLOCK,
    L_BLOCK
};

struct Point
{
    int x, y;
}

struct Block
{
    struct Point pixels[LEN];
    int shape;
    int orient;
};

class Tetris
{
    public:
        Tetris();
        
        virtual void button_action(int button);
        virtual void screen_display(MyDisp * screen);

        void print_menu(MyDisp * screen);
        void print_score(MyDisp * screen);
        void print_game(MyDisp * screen);

        void draw_block();
        void move_block();
        void rotate_block();
        void check_block();
        void update_ground();
        void check_over();
        void game_over();

    private:
        struct Block block;
        struct Point ground[MAX_LEN];
        int _state;
        int _score;
        int _delay;
};