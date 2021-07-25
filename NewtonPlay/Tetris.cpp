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
    _state = MENU;
    _score = 0;
}

void Tetris::button_action(int button)
{
    if (_state == MENU) {
        switch (button) {
            case UP:
                break;
            case DOWN:
                draw_block();
                _state = PLAY;
                _score = 0;
                _delay = 1000;
                break;
            case LEFT:
                break;
            case RIGHT:
                break;
        }
    }
    if (_state == PLAY) {
        switch (button) {
            case UP:
                rotate_block();
                break;
            case DOWN:
                break;
            case LEFT:
                move_block(LEFT);
                break;
            case RIGHT:
                move_block(RIGHT);
                break;
        }
    }
}

void Tetris::screen_display(MyDisp * screen)
{
    if (_state == MENU) {
        print_menu(screen);
    }
    if (_state == PLAY) {
        print_game(screen);
        screen->sleep(_delay);
        move_block(DOWN);
    }
}

void Tetris::print_menu(MyDisp * screen)
{
    screen->empty_screen(false);
    screen->set_pix(1, 1, 1);
    screen->set_pix(1, 1, 8);
    screen->set_pix(1, 8, 1);
    screen->set_pix(1, 8, 8);
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
    int type = (int)(random(0, N_SHAPES));
    _block.shape = type;
    _block.orient = 0;
    _block.idp.x = 4;
    _block.idp.y = 1;
    set_block(&_block, _block.idp.x, _block.idp.y, _block.shape, _block.orient);
}

void Tetris::move_block(int dir)
{
    int exit_status = 0;
    struct Block tmp;

    copy_block(&tmp, &_block);
    switch (dir) {
        case DOWN:
            tmp.idp.y++;
            for (int i = 0; i < LEN; i++) {
                tmp.pixels[i].y++;
            }
            exit_status = validate_ground(&tmp);
            break;
        case LEFT:
            tmp.idp.x--;
            for (int i = 0; i < LEN; i++) {
                tmp.pixels[i].x--;
                if (tmp.pixels[i].x < 1) {
                    exit_status = 1;
                    break;
                }
            }
            break;
        case RIGHT:
            tmp.idp.x++;
            for (int i = 0; i < LEN; i++) {
                _block.pixels[i].x++;
                if (tmp.pixels[i].x > 8) {
                    exit_status = 1;
                    break;
                }
            }
            break;
    }
    if (!exit_status) {
        copy_block(&_block, &tmp);
    } else if (exit_status == 2){
        update_ground();
    }
}

void Tetris::rotate_block()
{
    int exit_status = 0;
    struct Block tmp;

    copy_block(&tmp, &_block);
    tmp.orient = (tmp.orient + 1) % 4;
    exit_status = set_block(&tmp, tmp.idp.x, tmp.idp.y, tmp.shape, tmp.orient);
    if (!exit_status) {
        copy_block(&_block, &tmp);
    } else if (exit_status == 2){
        update_ground();
    }
}

void Tetris::update_ground()
{
    for (int i = 0; i < LEN; i++) {
        _ground[_block.pixels[i].x - 1][_block.pixels[i].y - 1] = 1;
        if (_block.pixels[i].y == 1) {
            _state = MENU;
            break;
        }
    }
    if (_state == PLAY) {
        check_line();
        draw_block();
    }
}

void Tetris::check_line()
{
    int cnt;
    for (int i = M_SIZE - 1; i > 0; i--) {
        cnt = 0;
        for (int j = 0; j < M_SIZE; j++) {
            if (_ground[i][j]) {
                cnt++;
            } else {
                break;
            }
        }
        if (cnt == 8) {
            _score++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < M_SIZE; j++) {
                    _ground[k][j] = _ground[k - 1][j];
                }
            }
            for (int k = 0; k < M_SIZE; k++) {
                _ground[0][k] = 0;
            }
        }
    }
}

void Tetris::copy_block(struct Block * copy_to, struct Block * copy_from)
{
    for (int i = 0; i < LEN; i++) {
        copy_to->pixels[i].x = copy_from->pixels[i].x;
        copy_to->pixels[i].y = copy_from->pixels[i].y;
    }
    copy_to->idp.x = copy_from->idp.x;
    copy_to->idp.y = copy_from->idp.y;
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
                         block->pixels[index].x = x + j + i * ((orient + 1) % 2);
                         block->pixels[index].y = y + i + j * (orient % 2);
                    } else {
                         block->pixels[index].x = x + j - i * ((orient + 1) % 2);
                         block->pixels[index].y = y + i - j * (orient % 2);
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
                    block->pixels[4].x = x - 1;
                    block->pixels[4].y = y;
                    break;
                case 1:
                    block->pixels[4].x = x + 1;
                    block->pixels[4].y = y;
                    break;
                case 2:
                    block->pixels[4].x = x + 1;
                    block->pixels[4].y = y + 2;
                    break;
                case 3:
                    block->pixels[4].x = x - 1;
                    block->pixels[4].y = y + 2;
                    break;
            }
            break;
    }
    return validate_ground(block);
}

int Tetris::validate_ground(struct Block * block)
{
    for (int i = 0; i < LEN; i++) {
        if (block->pixels[i].x < 1 || block->pixels[i].x > 8 || block->pixels[i].y < 1) {
            return 1;
        } else if (block->pixels[i].y > 8) {
            return 2;
        } else if (_ground[block->pixels[i].x - 1][block->pixels[i].y - 1]) {
            return 2;
        }
    }
    return 0;
}