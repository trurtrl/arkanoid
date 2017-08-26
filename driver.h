/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "ball.h"
#include "obstacle.h"
#include "parser.h"

typedef Line* (Obstacle::* ObstacleFn)(); 


//std::vector<Obstacle*> vector_obstacles;


class Driver{
private:
    std::vector<ObstacleFn> vector_sides;
    std::vector<Obstacle*> vector_obstacles;
    Ball* ball;
    int collision;    
    
    void interaction (std::vector<Obstacle*> &vector_obs, std::vector<Obstacle*>::iterator iter_obs);
    void define_sides_to_check(std::vector<ObstacleFn> &vec_sides, Ball* ball);
    bool is_intersected(Obstacle* obs, ObstacleFn p_func, Ball* ball);
    void reflect_angle(Obstacle* obs, ObstacleFn p_func, Ball* ball);
    bool is_angle_acute(Obstacle* obs, ObstacleFn p_func, Ball* ball);
    float distance_to_line(Obstacle* obs, ObstacleFn p_func, Ball* ball);
    int length2(int p1x, int p1y, int p2x, int p2y);
    void prevent_looping();         
    
public:
    Driver(std::vector<Obstacle*> &vec_obs, Ball* ball, int col)
    :vector_obstacles{vec_obs}, ball{ball}, collision{col} 
    {};  
    void move_ball(Ball* ball);
    void print_obstacles();
    bool is_in_vector_deletable_obstacle();
    
    void print_collision(Obstacle* obs, ObstacleFn p_func, Ball* ball);

};


#endif /* DRIVER_H */

