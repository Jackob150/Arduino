/*
  Snake.cpp - Snake Game for NewtonPlay.
  Created by Jakub Ciesielski, 24.07.2021.
*/

#include "Arduino.h"
#include "MyDisp.h"
#include "Controller.h"
#include "Game.h"
#include "Snake.h"

Snake::Snake()
{
    _state = MENU;
    _diff = 1;
}

void Snake::button_action(int button)
{
    if (_state == MENU) {
        switch (button) {
            case UP:
                break;
            case DOWN:
                _state = PLAY;
                _snake_arr[0].x = 1;
                _snake_arr[0].y = 7;
                _snake_arr[1].x = 1;
                _snake_arr[1].y = 8;
                _tail.x = 1;
                _tail.y = 8;

                put_apple();
                
                _len = 2;
                _dir = UP;
                _speed = 1 + int(_diff / 3);
                _points = 0;
                break;
            case LEFT:
                if (_diff > 1) {
                    _diff--;
                }
                break;
            case RIGHT:
                if (_diff < 8) {
                    _diff++;
                }
                break;
        }
    }
    if (_state == PLAY) {
        if (_dir + button > 1 && _dir + button < 5) {
            _dir = button;
        }
    }
}

void Snake::screen_display(MyDisp * screen)
{
    if (_state == MENU) {
        print_menu(screen);
    }
    if (_state == PLAY) {
        print(screen);
        screen->sleep(int(1000/_speed));
        move();
        check_bounds();
        check_tail();
        check_apple();
        if (_state == MENU) {
            screen->sleep(1000);
        }
    }
}

void Snake::print_menu(MyDisp * screen)
{
    screen->empty_screen(false);
    for (int i = 1; i <= _diff; i++) {
        screen->set_pix(1, i, 1);
    }
    print_score(screen);
    screen->display();
}

void Snake::print_score(MyDisp * screen)
{
    int s_0 = _points % 10;
    int s_1 = int(_points / 10);

    screen->print_digit(1, 3, s_1);
    screen->print_digit(5, 3, s_0);
}

void Snake::print(MyDisp * screen)
{
    screen->empty_screen(false);
    for (int i = 0; i < _len; i++) {
        screen->set_pix(1, _snake_arr[i].x, _snake_arr[i].y);
    }
    screen->set_pix(1, _apple.x, _apple.y);
    screen->display();
}

void Snake::move()
{
    struct Point tmp_1, tmp_2;
    tmp_1 = _snake_arr[0];
    switch (_dir) {
        case UP:
            _snake_arr[0].y -= 1;
            break;
        case DOWN:
            _snake_arr[0].y += 1;
            break;
        case LEFT:
            _snake_arr[0].x -= 1;
            break;
        case RIGHT:
            _snake_arr[0].x += 1;
            break;
    }
    for (int i = 1; i < _len; i++) {
        tmp_2 = _snake_arr[i];
        _snake_arr[i] = tmp_1;
        tmp_1 = tmp_2;
    }
    _tail = tmp_1;
}

void Snake::check_bounds()
{
    for (int i = 0; i < _len; i++) {
        if (_snake_arr[i].x < 1 || _snake_arr[i].x > 8 || _snake_arr[i].y < 1 || _snake_arr[i].y > 8) {
            game_over();
        }
    }
}

void Snake::check_tail()
{
    for (int i = 1; i < _len; i++) {
        if (_snake_arr[0].x == _snake_arr[i].x && _snake_arr[0].y == _snake_arr[i].y) {
            game_over();
        }
    }

}

void Snake::check_apple()
{
    if (_snake_arr[0].x == _apple.x && _snake_arr[0].y == _apple.y) {
        _snake_arr[_len] = _tail;
        _len++;
        _points++;
        if (_points % (5 - int(_diff/2)) == 0) {
            _speed++;
        }
        put_apple();
    }
}

void Snake::put_apple()
{
    bool status = false;
    while (!status) {
        status = true;
        _apple.x = int(random(1, 9));
        _apple.y = int(random(1, 9));
        for (int i = 0; i < _len; i++) {
            if (_apple.x == _snake_arr[i].x && _apple.y == _snake_arr[i].y) {
                status = false;
            }
        }
    }
}

void Snake::game_over()
{
    _state = MENU;
}