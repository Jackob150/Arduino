/*
  Chooser.h - Chooser interface for NewtonPlay.
  Created by Jakub Ciesielski, 26.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "Chooser.h"
#include "Snake.h"
#include "Tetris.h"

Chooser::Chooser()
{
    _state = OUTER_MENU;
    _pointer = SNAKE;
    Snake snake = Snake();
    Tetris tetris = Tetris();
}

void Chooser::button_action(MyDisp * screen, int button)
{
    if (_state == OUTER_MENU) {
        switch (button) {
            case UP:
                _pointer = (_pointer + 1) % N_GAMES;
                break;
            case DOWN:
                _state = MENU;
                switch (_pointer) {
                    case SNAKE:
                        _snake.set_state(MENU);
                        break;
                    case TETRIS:
                        _tetris.set_state(MENU);
                        break;
                }
                break;
        }
    } else {
        if (button == UP) {
            if (_pointer == SNAKE && _snake.get_state() == MENU) {
                _state = OUTER_MENU;
                _snake.set_state(OUTER_MENU);
            } else if (_pointer == TETRIS && _tetris.get_state() == MENU) {
                _state = OUTER_MENU;
                _tetris.set_state(OUTER_MENU);
            }
        }
        switch (_pointer) {
            case SNAKE:
                _snake.button_action(screen, button);
                break;
            case TETRIS:
                _tetris.button_action(screen, button);
                break;
        }
    }
}

void Chooser::screen_display(MyDisp * screen) {
    switch (_pointer) {
        case SNAKE:
            _snake.screen_display(screen);
            break;
        case TETRIS:
            _tetris.screen_display(screen);
            break;
    }
}