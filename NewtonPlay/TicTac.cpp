/*
  TicTac.cpp - Tic Tac Toe Game for NewtonPlay.
  Created by Jakub Ciesielski, 27.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "TicTac.h"

TicTac::TicTac()
{
    for (int i = 0; i < T_SIZE; i++) {
        for (int j = 0; j < T_SIZE; j++) {
            _table[i][j] = 0;
        }
    }
    _state = OUTER_MENU;
    _mode = SINGLE;
    _diff = MONKEY;
}

void TicTac::button_action(MyDisp * screen, int button)
{
    if (_state == MENU) {
        switch (button) {
            case UP: // reserved
                break;
            case DOWN:
                for (int i = 0; i < T_SIZE; i++) {
                    for (int j = 0; j < T_SIZE; j++) {
                        _table[i][j] = 0;
                    }
                }
                _player = 0;
                _winner = 0;
                _passage = 0;
                _field = 0;
                _moves = 0;
                _state = PLAY;
                break;
            case LEFT:
                _mode = (_mode + 1) % 2;
                break;
            case RIGHT:
                if (!_mode) {
                    _diff = (_diff + 1) % 3;
                }
                break;
        }
    } else if (_state == PLAY) {
        switch (button) {
            case UP:
                _state = MENU;
                break;
            case DOWN:
                _table[_field % 3][(int)(_field / 3)] = _player + 1;
                move_done();
                break;
            case LEFT:
                _field--;
                if (_field < 0) {
                    _field += 9;
                }
                break;
            case RIGHT:
                _field = (_field + 1) % 9;
                break;
        }
    } else if (_state == HOLD) {
        switch (button) {
            case UP:
                break;
            case DOWN:
                _state = MENU;
                break;
            case LEFT:
                break;
            case RIGHT:
                break;
        }
    }
}

void TicTac::screen_display(MyDisp * screen)
{
    if (_state == OUTER_MENU) {
        print_outer_menu(screen);
    } else if (_state == MENU) {
        print_menu(screen);
    } else if (_state == PLAY) {
        if (_mode == 0 && _player == 1) {
            make_move();
        }
        print_game(screen);
    } else if (_state == HOLD) {
        if (_winner) {
            print_winner(screen);
            _passage = 1;
        }
    }
}

void TicTac::print_outer_menu(MyDisp * screen)
{
    screen->set_letter('X');
    screen->display();
}

void TicTac::print_menu(MyDisp * screen)
{
    screen->empty_screen(false);
    screen->print_digit(3, 3, _mode + 1);
    if (!_mode) {
        for (int i = 0; i <=_diff; i++) {
            screen->set_pix(1, 7, 7 - 2 * i);
            screen->set_pix(1, 7, 8 - 2 * i);
            screen->set_pix(1, 8, 7 - 2 * i);
            screen->set_pix(1, 8, 8 - 2 * i);
        }
    }
    screen->display();
}

void TicTac::print_game(MyDisp * screen)
{
    screen->empty_screen(false);
    for (int i = 1; i <= M_SIZE; i++) {
        screen->set_pix(1, 3, i);
        screen->set_pix(1, 6, i);
        screen->set_pix(1, i, 3);
        screen->set_pix(1, i, 6);
    }
    for (int i = 0; i < T_SIZE; i++) {
        for (int j = 0; j < T_SIZE; j++) {
            if (_table[i][j] == 1) {
                screen->set_pix(1, 3 * i + 1, 3 * j + 1);
                screen->set_pix(1, 3 * i + 2, 3 * j + 2);
            } else if (_table[i][j] == 2) {
                screen->set_pix(1, 3 * i + 1, 3 * j + 2);
                screen->set_pix(1, 3 * i + 2, 3 * j + 1);
            }
        }
    }
    screen->set_pix(1, 3 * (_field % 3) + 1, 3 * ((int)(_field / 3)) + 1);
    screen->set_pix(1, 3 * (_field % 3) + 1, 3 * ((int)(_field / 3)) + 2);
    screen->set_pix(1, 3 * (_field % 3) + 2, 3 * ((int)(_field / 3)) + 1);
    screen->set_pix(1, 3 * (_field % 3) + 2, 3 * ((int)(_field / 3)) + 2);
    screen->display();
}

void TicTac::print_winner(MyDisp * screen)
{   
    if (!_passage) {
        screen->empty_screen();
        screen->sleep(100);
        for (int i = 1; i <= M_SIZE; i++) {
            for (int j = 1; j <= M_SIZE; j++) {
                screen->set_pix(1, j, i);
            }
            screen->sleep(100);
        }
        for (int i = M_SIZE; i > 0; i--) {
            for (int j = 1; j <= M_SIZE; j++) {
                screen->set_pix(0, j, i);
            }
            screen->sleep(100);
        }
    }
    screen->print_digit(3, 2, _winner);
    screen->set_pix(1, 1, 1);
    screen->set_pix(1, 1, 2);
    screen->set_pix(1, 2, 1);
    screen->set_pix(1, 1, 7);
    screen->set_pix(1, 1, 8);
    screen->set_pix(1, 2, 8);
    screen->set_pix(1, 7, 1);
    screen->set_pix(1, 8, 1);
    screen->set_pix(1, 8, 2);
    screen->set_pix(1, 7, 8);
    screen->set_pix(1, 8, 8);
    screen->set_pix(1, 8, 7);
    screen->display();
}

int TicTac::check_winner()
{
    int sum[8];
    if (_table[0][0] * _table[1][1] * _table[2][2] == 1)
        return 1;
    if (_table[0][0] * _table[1][1] * _table[2][2] == 8)
        return 2;
    if (_table[0][2] * _table[1][1] * _table[2][0] == 1)
        return 1;
    if (_table[0][2] * _table[1][1] * _table[2][0] == 8)
        return 2;
    for (int i = 0; i < 3; i++) {
        if (_table[i][0] * _table[i][1] * _table[i][2] == 1)
            return 1;
        if (_table[i][0] * _table[i][1] * _table[i][2] == 8)
            return 2;
        if (_table[0][i] * _table[1][i] * _table[2][i] == 1)
            return 1;
        if (_table[i][0] * _table[i][1] * _table[i][2] == 8)
            return 2;
    }
    return 0;
}

void TicTac::make_move()
{
    switch (_diff) {
        case MONKEY:
            int monkey_field;
            do {
                monkey_field = (int)(random(0, 9));
            } while (_table[monkey_field % 3][(int)(monkey_field / 3)]);
            _table[monkey_field % 3][(int)(monkey_field / 3)] = _player + 1;
            move_done();
            break;
        case HUMAN:
            break;
        case GOD:
            break;
    }
}

void TicTac::move_done()
{
    _winner = check_winner();
    if (_winner) {
        _state = HOLD;
        return;
    }
    _moves++;
    if (_moves == 9) {
        _state = MENU;
    } else {
        do {
            _field = (_field + 1) % 9;
        } while (_table[_field % 3][(int)(_field / 3)]);
        _player = (_player + 1 ) % 2;
    }
}

int TicTac::get_state()
{
    return _state;
}

void TicTac::set_state(int state)
{
    _state = state;
}