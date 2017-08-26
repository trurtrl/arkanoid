/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef BALL_H
#define BALL_H
#include <vector>

//float M_PI = 3.14159265359;

class Ball {
private:
    int _x; // current position on axis X
    int _y;
    const int _radius;
    float _angle; //an angle in range from 0 to 2π (radians)
    float _speed; //movement by diagonal
    int _x_speed, _y_speed; // speed on axes
    void correct_x_speed(); // speed in axis X
    void correct_y_speed();
    void correct_angle(float &new_angle);

public:
    Ball(int pos_X, int pos_Y, float angle, int radius, float speed); 
    ~Ball();
    void set_x(int);
    void set_y(int);
    void set_direction(float new_angle); // changing an angle out of the class
    void set_speed(float s);

    int x() const {return _x;};
    int y() const {return _y;};
    int x_speed() const {return _x_speed;};
    int y_speed() const {return _y_speed;};
    int radius() const {return _radius;};
    float angle() const {return _angle;};

};

#endif /* BALL_H */

