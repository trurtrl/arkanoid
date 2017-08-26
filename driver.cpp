/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "driver.h"
#include <cmath>


bool Driver::is_in_vector_deletable_obstacle()
{
    for (Obstacle* p_obs:vector_obstacles)
    {
        if(p_obs->destroyable) return 1;
    }
    return 0;
};

void Driver::interaction(std::vector<Obstacle*> &vector_obs, std::vector<Obstacle*>::iterator iter_obs)
{
    (*iter_obs) -> touch();
    if ((*iter_obs)->destroyable && (*iter_obs)->counter == 0) // conditions to destroy the obstacle 
    {
        std::cout << "--- Deleting object ---" << std::endl;
        (*iter_obs) -> print();
        std::cout << "=== Deleting object ===" << std::endl;        
        delete (*iter_obs);
        vector_obs.erase(iter_obs);
        std::cout << "\tThere are " << vector_obstacles.size() << " obstacles -" << std::endl;         
//       print_obstacles();
    };
};

void Driver::move_ball(Ball* ball)
{
    ball -> set_x( (ball -> x()) + (ball -> x_speed()) );
    ball -> set_y( (ball -> y()) + (ball -> y_speed()) );

    define_sides_to_check(vector_sides, ball);

    for (std::vector<Obstacle*>::iterator iter_obs = vector_obstacles.begin(); iter_obs != vector_obstacles.end();  ++iter_obs)
    {
        for(int s=0; s!=vector_sides.size();++s)
        {
            if (is_intersected(*iter_obs, vector_sides[s], ball))
            {
//                print_collision(*iter_obs, vector_sides[s], ball);
                interaction(vector_obstacles, iter_obs);
//                std::cout << "\told angle = " << ball ->angle() << std::endl;
                reflect_angle(*iter_obs, vector_sides[s], ball);
//                std::cout << "\tnew angle = " << ball ->angle() << std::endl;
                prevent_looping();
            };
        };

    };
//    vector_sides.clear();
};

void Driver::print_collision(Obstacle* obs, ObstacleFn p_func, Ball* ball)
{
    int first_x  = (obs ->* p_func)() -> begin() ->x;
    int first_y  = (obs ->* p_func)() -> begin() ->y;  
    int second_x = (obs ->* p_func)() -> end() ->x;
    int second_y = (obs ->* p_func)() -> end() ->y; 
    int ball_x = ball -> x();
    int ball_y = ball ->y();
    std::cout << "hit in -" << (obs ->* p_func)() -> side << "-" << std::endl;
    std::cout << "\tLine:\t(" << first_x<<","<<first_y<<" - "<<second_x<<","<<second_y<<")" << std::endl;
    std::cout << "\tBall:\t(" << ball_x<< "," << ball_y<< ")" << std::endl;
};

void Driver::define_sides_to_check(std::vector<ObstacleFn> &vec_sides, Ball* ball)
{
    vec_sides.clear();
    float angle = ball -> angle();
    if     (angle < 0.5*M_PI)
        {vec_sides.push_back( &Obstacle::down); vec_sides.push_back( &Obstacle::left);}
    else if(angle > 0.5*M_PI && angle < M_PI)
        {vec_sides.push_back( &Obstacle::down); vec_sides.push_back( &Obstacle::right);}
    else if(angle > M_PI   && angle < 1.5*M_PI)
        {vec_sides.push_back( &Obstacle::up); vec_sides.push_back( &Obstacle::right);} 
    else if(angle < 2*M_PI)
        {vec_sides.push_back( &Obstacle::up); vec_sides.push_back( &Obstacle::left);}
    else if(angle = 0.5*M_PI)
        {vec_sides.push_back( &Obstacle::down);}
    else if(angle = M_PI)
        {vec_sides.push_back( &Obstacle::left);}        
    else if(angle = 1.5*M_PI)
        {vec_sides.push_back( &Obstacle::up);}
    else
        {vec_sides.push_back( &Obstacle::right);}; 
};

bool Driver::is_intersected(Obstacle* obs, ObstacleFn p_func, Ball* ball)
// how much intersections ball has with the line, set by two points
{
    float dist = distance_to_line(obs, p_func, ball);
    int radius = ball -> radius(); 
    if ((dist < radius) && is_angle_acute(obs, p_func, ball ))
    {
        return 1;
    };
    return 0;
//    else if (dist < radius) {return 2;};  // possible to diversify reflection, needs to change this and reflection functions 
};

void Driver::reflect_angle(Obstacle* obs, ObstacleFn p_func, Ball* ball)
{
    char reflection_side = (obs ->* p_func)() -> side;
    float angle = ball -> angle();
    switch(reflection_side)
    {
        case 'u':
            if (angle > 1.5*M_PI && angle < 2*M_PI) // 2π-α 
                {ball -> set_direction(-(angle-2*M_PI));} // α 
            else if (angle > M_PI && angle < 1.5*M_PI) // π+α 
                {ball -> set_direction(2*M_PI-angle);} //π-α
            else if (angle == 1.5*M_PI)
                {ball -> set_direction(0.5*M_PI);} 
            else 
                {std::cout << "Angle is wrong in 'u'" << std::endl;};
            break;
        case 'r':
            if (angle > 0.5*M_PI && angle < M_PI) // π-α 
                {ball -> set_direction(M_PI-angle);} // α 
            else if (angle > M_PI && angle < 1.5*M_PI) // π+α 
                {ball -> set_direction(3*M_PI-angle);} //2π-α
            else if (angle == M_PI)
                {ball -> set_direction(0);} 
            else 
                {std::cout << "Angle is wrong in 'r'" << std::endl;};
            break;
        case 'd':
            if (angle > 0 && angle < 0.5*M_PI) // α 
                {ball -> set_direction(2*M_PI-angle);} // 2π-α 
            else if (angle > 0.5*M_PI && angle < M_PI) // π-α 
                {ball -> set_direction(2*M_PI-angle);} //π+α
            else if (angle == 0.5*M_PI)
                {ball -> set_direction(1.5*M_PI);} 
            else 
                {std::cout << "Angle is wrong in 'd'" << std::endl;};  
            break;
        case 'l':
            if (angle > 0 && angle < 0.5*M_PI) // α 
                {ball -> set_direction(M_PI-angle);} // π-α 
            else if (angle > 1.5*M_PI && angle < 2*M_PI) // 2π-α 
                {ball -> set_direction(3*M_PI-angle);} //π+α
            else if (angle == 0)
                {ball -> set_direction(M_PI);} 
            else 
                {std::cout << "Angle is wrong in 'l'" << std::endl;}; 
            break;
        default:
            std::cout << "Problems with getting a side of reflection" << std::endl;
    };        
};

bool Driver::is_angle_acute(Obstacle* obs, ObstacleFn p_func, Ball* ball) 
/* length2 - the square of the distanse between two points
 * According to the law of cosines, if (b^2 + c^2 - a^2)>0, the angle between 
 * 'b' and 'c' is acute (sharp); if ==0, the angle is right
 * Here if at least one angle is not obtuse (blunt) and (distance <= radius ), 
 * ball touches\intersects the line.   
 */
{
    int x1 = (obs ->* p_func)() ->begin() -> x;
    int y1 = (obs ->* p_func)() ->begin() -> y;
    int x2 = (obs ->* p_func)() ->end() -> x;
    int y2 = (obs ->* p_func)() ->end() -> y;
    int x0 = ball -> x();
    int y0 = ball -> y();
    int a2 = length2(x0, y0, x1, y1);
    int b2 = length2(x0, y0, x2, y2);
    int c2 = (obs ->* p_func)() -> length2();
    if ((b2+c2-a2) >= 0 && (a2+c2-b2) >= 0)
    {
//        std::cout << "a2 = "<< a2 << "; b2 =" << b2<< "; c2 = " << c2 << std::endl; 
        return 1;
    }; // angle is not obtuse
    return 0;
};

float Driver::distance_to_line(Obstacle* obs, ObstacleFn p_func, Ball* ball)
/* *p_func - pointer to function, describing the side of obstacle obs
 * For Line:
 *  distance = |(y2-y1)x0 - (x2-x1)y0 + x2y1 - y2x1| / sqrt( (y2-y1)^2 + (x2-x1)^2 )
 * - the formula for defining a distance(perpendicular) between a line and a point p(x0, y0).
 * a=y2-y1; b=x2-x1; c=x2y1-y2x1; length=sqrt( (y2-y1)^2 + (x2-x1)^2 ) 
*/
{
    float a = (obs ->* p_func)() -> a();
    float b = (obs ->* p_func)() -> b();
    float c = (obs ->* p_func)() -> c();    
    float length = (obs ->* p_func)() -> length(); 
    int x0 = ball-> x(); //coordinates of the ball
    int y0 = ball-> y();

    return fabs(a*x0 - b*y0 + c)/length;
};

int Driver::length2(int p1x, int p1y, int p2x, int p2y)
// length2 - the square of the distanse between two points
{
    return (p2y-p1y)*(p2y-p1y) + (p2x-p1x)*(p2x-p1x);
};

void Driver::print_obstacles()
{
    std::cout << "\tThere are " << vector_obstacles.size() << " obstacles ---" << std::endl;    
    for (int i=0; i!= vector_obstacles.size(); ++i)
    {
        std::cout << "\t obstacle\t" << i << std::endl;
        vector_obstacles[i] -> print();
    };
}

void Driver::prevent_looping()
{
    --collision;
    if (collision == 0)
    {
        ball->set_direction(0.125*M_PI + ball->angle());
        collision = Settings::collision;
    }
}