/*
  Snake.cpp - Snake Game for NewtonPlay.
  Created by Jakub Ciesielski, 24.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "Tetris.h"

Tetris::Tetris()
{
    _state = OUTER_MENU;
    _score = 0;
    _diff = 0;
}

void Tetris::button_action(MyDisp * screen, int button)
{
    if (_state == MENU) {
        switch (button) {
            case UP: // reserved
                break;
            case DOWN:
                for (int i = 0; i < M_SIZE; i++) {
                    for (int j = 0; j < M_SIZE; j++) {
                        _ground[i][j] = 0;
                    }
                }
                draw_block();
                _score = 0;
                _delay = 1000 - 150 * _diff;
                _state = PLAY;
                break;
            case LEFT:
                if (_diff > 0)
                    _diff--;
                break;
            case RIGHT:
                if (_diff < 6)
                    _diff++;
                break;
        }
    } else if (_state == PLAY) {
        switch (button) {
            case UP:
                rotate_block(screen);
                break;
            case DOWN:
                move_block(screen, DOWN);
                break;
            case LEFT:
                move_block(screen, LEFT);
                break;
            case RIGHT:
                move_block(screen, RIGHT);
                break;
        }
    }
}

void Tetris::screen_display(MyDisp * screen)
{
    if (_state == OUTER_MENU) {
        print_outer_menu(screen);
    } else if (_state == MENU) {
        print_menu(screen);
    } else if (_state == PLAY) {
        print_game(screen);
        screen->sleep(_delay);
        move_block(screen, DOWN);
    }
}

void Tetris::print_outer_menu(MyDisp * screen)
{
    screen->set_letter('T');
    screen->display();
}

void Tetris::print_menu(MyDisp * screen)
{
    screen->empty_screen(false);
    screen->set_pix(1, 1, 1);
    screen->set_pix(1, 8, 1);
    for (int i = 0; i < _diff; i++) {
        screen->set_pix(1, 2 + i, 1);
    }
    print_score(screen);
    screen->display();
}

void Tetris::print_score(MyDisp * screen)
{
    int s_0 = _score % 10;
    int s_1 = int(_score / 10);

    screen->print_digit(1, 3, s_1);
    screen->print_digit(5, 3, s_0);
}

void Tetris::print_game(MyDisp * screen)
{
    screen->empty_screen(false);
    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            if (_ground[i][j]) {
                screen->set_pix(1, i + 1, j + 1);
            }
        }
    }
    for (int i = 0; i < LEN; i++) {
        screen->set_pix(1, _block.pixels[i].x, _block.pixels[i].y);
    }
    screen->display();
}

void Tetris::draw_block()
{
    randomSeed(micros());
    int type = (int)(random(0, N_SHAPES));
    _block.shape = type;
    _block.orient = 0;
    _block.idp.x = 4;
    _block.idp.y = 0;
    set_block(&_block, _block.idp.x, _block.idp.y, _block.shape, _block.orient);
}

void Tetris::move_block(MyDisp * screen, int dir)
{
    int exit_status = 0;
    struct Block tmp;

    copy_block(&tmp, &_block);
    switch (dir) {
        case UP:
            break;
        case DOWN:
            exit_status = set_block(&tmp, tmp.idp.x, ++tmp.idp.y, tmp.shape, tmp.orient);
            break;
        case LEFT:
            exit_status = set_block(&tmp, --tmp.idp.x, tmp.idp.y, tmp.shape, tmp.orient);
            break;
        case RIGHT:
            exit_status = set_block(&tmp, ++tmp.idp.x, tmp.idp.y, tmp.shape, tmp.orient);
            break;
    }
    if (!exit_status) {
        copy_block(&_block, &tmp);
    } else if (exit_status == 2 && dir == DOWN){
        update_ground();
    }
    print_game(screen);
}

void Tetris::rotate_block(MyDisp * screen)
{
    int exit_status = 0;
    struct Block tmp;

    copy_block(&tmp, &_block);
    tmp.orient = (tmp.orient + 1) % 4;
    exit_status = set_block(&tmp, tmp.idp.x, tmp.idp.y, tmp.shape, tmp.orient);
    if (!exit_status) {
        copy_block(&_block, &tmp);
        print_game(screen);
    }
}

void Tetris::update_ground()
{
    for (int i = 0; i < LEN; i++) {
        _ground[_block.pixels[i].x - 1][_block.pixels[i].y - 1] = 1;
        if (_block.pixels[i].y == 0) {
            _state = MENU;
            break;
        }
    }
    if (_state != MENU) {
        check_line();
        draw_block();
    }
}

void Tetris::check_line()
{
    int cnt;
    int score = 0;
    for (int j = M_SIZE - 1; j > 0; j--) {
        cnt = 0;
        for (int i = 0; i < M_SIZE; i++) {
            if (_ground[i][j]) {
                cnt++;
            } else {
                break;
            }
        }
        if (cnt == 8) {
            score++;
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < M_SIZE; i++) {
                    _ground[i][k] = _ground[i][k - 1];
                }
            }
            for (int k = 0; k < M_SIZE; k++) {
                _ground[k][0] = 0;
            }
            j++;
        }
    }
    _score += score * score;
}

void Tetris::copy_block(struct Block * copy_to, struct Block * copy_from)
{
    for (int i = 0; i < LEN; i++) {
        copy_to->pixels[i].x = copy_from->pixels[i].x;
        copy_to->pixels[i].y = copy_from->pixels[i].y;
    }
    copy_to->idp.x = copy_from->idp.x;
    copy_to->idp.y = copy_from->idp.y;
    copy_to->shape = copy_from->shape;
    copy_to->orient = copy_from->orient;
}

int Tetris::set_block(struct Block * block, int x, int y, int shape, int orient)
{
    int index;
    switch (shape) {
        case LINE:
            if (orient % 2) {
                for (int i = 0; i < LEN; i++) {
                    block->pixels[i].x = x;
                    block->pixels[i].y = y - 1 + i;
                }
            } else {
                for (int i = 0; i < LEN; i++) {
                    block->pixels[i].x = x - 1 + i;
                    block->pixels[i].y = y;
                }
            }
            break;
        case SQUARE:
            for (int i = 0; i < int(LEN / 2); i++) {
                for (int j = 0; j < int(LEN / 2); j++) {
                    index = 2 * i + j;
                    block->pixels[index].x = x + j;
                    block->pixels[index].y = y + i;
                }
            }
            break;
        case T_BLOCK:
            block->pixels[2].x = x;
            block->pixels[2].y = y;
            block->pixels[1].x = x - 1;
            block->pixels[1].y = y + 1;
            block->pixels[0].x = x;
            block->pixels[0].y = y + 1;
            block->pixels[3].x = x + 1;
            block->pixels[3].y = y + 1;
            if (orient) {
                block->pixels[orient].x = x;
                block->pixels[orient].y = y + 2;
            }
            break;
        case S_BLOCK_1:
        case S_BLOCK_2:
            for (int i = 0; i < LEN / 2; i++) {
                for (int j = 0; j < LEN / 2; j++) {
                    index = 2 * i + j;
                    if (shape == S_BLOCK_1) {
                        if (orient % 2) {
                            block->pixels[index].x = x + i;
                            block->pixels[index].y = y + 2 - i - j;
                        } else {
                            block->pixels[index].x = x + j + i;
                            block->pixels[index].y = y + i;
                        }
                    } else {
                        if (orient % 2) {
                            block->pixels[index].x = x + i;
                            block->pixels[index].y = y + i + j;
                        } else {
                            block->pixels[index].x = x + j - i;
                            block->pixels[index].y = y + i;
                        }
                    }
                }
            }
            break;
        case L_BLOCK_1:
        case L_BLOCK_2:
            int mode = 0;
            block->pixels[0].x = x + 1;
            block->pixels[0].y = y + 1;
            if (orient % 2) {
                block->pixels[1].x = x + 1;
                block->pixels[1].y = y;
                block->pixels[2].x = x + 1;
                block->pixels[2].y = y + 2;
            } else {
                block->pixels[1].x = x;
                block->pixels[1].y = y + 1;
                block->pixels[2].x = x + 2;
                block->pixels[2].y = y + 1;
            }
            if (shape == L_BLOCK_2) {
                mode = 1;
            }
            switch ((orient + mode) % 4) {
                case 0:
                    block->pixels[3].x = x;
                    block->pixels[3].y = y;
                    break;
                case 1:
                    block->pixels[3].x = x + 2;
                    block->pixels[3].y = y;
                    break;
                case 2:
                    block->pixels[3].x = x + 2;
                    block->pixels[3].y = y + 2;
                    break;
                case 3:
                    block->pixels[3].x = x;
                    block->pixels[3].y = y + 2;
                    break;
            }
            break;
    }
    return validate_ground(block);
}

int Tetris::validate_ground(struct Block * block)
{
    for (int i = 0; i < LEN; i++) {
        if (block->pixels[i].x < 1 || block->pixels[i].x > 8) {
            return 1;
        } else if (block->pixels[i].y > 8) {
            return 2;
        } else if (_ground[block->pixels[i].x - 1][block->pixels[i].y - 1] == 1) {
            return 2;
        }
    }
    return 0;
}

int Tetris::get_state()
{
    return _state;
}

void Tetris::set_state(int state)
{
    _state = state;
}