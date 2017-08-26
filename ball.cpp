/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ball.h"
#include<math.h>
#include<iostream>

Ball::Ball(int pos_X, int pos_Y, float angle, int radius, float speed )
    : _x{pos_X}, _y{pos_Y}, _radius{radius}, _speed{speed}
{
        set_direction(angle);
};

void Ball::set_x(int x){_x = x;};
void Ball::set_y(int y){_y = y;};

void Ball::correct_x_speed() {_x_speed = _speed*std::cos(_angle);};
void Ball::correct_y_speed() {_y_speed = _speed*std::sin(_angle);};

void Ball::correct_angle(float &new_angle)
{
    if (new_angle > 2*M_PI){new_angle = new_angle-2*M_PI;}
    else if (new_angle < 0){new_angle = new_angle+2*M_PI;};
};

void Ball::set_direction(float new_angle)
{
    correct_angle(new_angle);
    _angle = new_angle;
    correct_x_speed();
    correct_y_speed();    
};

void Ball::set_speed(float s)
{
    _speed = s;
    correct_x_speed();
    correct_y_speed();      
};
