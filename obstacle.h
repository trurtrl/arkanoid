/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<string>
#include<vector>
//#include<stdexcept>
#include<iostream>

struct Point {
    int x,y;
    Point(int pos_x, int pos_y)
        :x{pos_x}, y{pos_y}
        {    
//            if (pos_x <0 || pos_x > 1000 || pos_y <0 || pos_y > 1000) 
//                {throw std::invalid_argument ("Coordinates of X or/and Y are wrong!");}; 
        };
    ~Point(){};
};

class Line {
private:
    Point* p_begin;
    Point* p_end;  // !!! check & for a second lement !!!
    float _a, _b, _c, _length, _length2;
/* distance = |(y2-y1)x0 - (x2-x1)y0 + x2y1 - y2x1| / sqrt( (y2-y1)^2 + (x2-x1)^2 )
 * - the formula for defining a distance(perpendicular) between a line and a point p(x0, y0).
 * a=y2-y1; b=x2-x1; c=x2y1-y2x1; length2=(y2-y1)^2 + (x2-x1)^2; length = sqrt(length2)  
 * Variables a,b,c,length, length2 are calculated here for saving time later 
*/
    Line (const Line&);
    Line& operator=(const Line&);
    Line (Line&&);
    Line& operator=(Line&&);
    
public:
    Line(Point* begin, Point* end, char s)
        : p_begin{begin}, p_end{end}, side{s}
        {
            _a = set_a();
            _b = set_b();
            _c = set_c();
            _length2 = set_length2();            
            _length = set_length();
        };
    ~Line(){delete p_begin, p_end; };
    char side;
    float set_a();
    float set_b();
    float set_c();
    float set_length2(); //length^2
    float set_length();
    Point* begin(){return p_begin;};
    Point* end(){ return p_end;};
    float a()  {return _a;};
    float b() const {return _b;};
    float c() const {return _c;};
    float length() const {return _length;};
    float length2() const {return _length2;};
};


class Obstacle {
private:
    Line* _up;
    Line* _right;
    Line* _down;
    Line* _left;
    
    Obstacle (const Obstacle&);
    Obstacle& operator=(const Obstacle&);
    Obstacle (Obstacle&&);
    Obstacle& operator=(Obstacle&&);
    
public:
    int counter; // defines quantity of collision after which the object can be destoyed
    bool destroyable;
    Obstacle(Point* p1, Point* p2, Point* p3, Point* p4, bool destr = false, int count = 8) // '8' implies infinity
    :destroyable{destr}, counter{count}
    {
        _left  = new Line (p1, p2, 'l');
        _up    = new Line (p2, p3, 'u');
        _right = new Line (p4, p3, 'r');
        _down  = new Line (p1, p4, 'd');
    };
    ~Obstacle()
    {
        delete _up, _right, _down, _left;
    };
  
    Line* up()   { return _up;};
    Line* right(){ return _right;};
    Line* down() { return _down;};
    Line* left() { return _left;};
    
    virtual void touch(){};
    void print()
    {
        std::cout << "( " << _left -> begin() -> x << " , " << _left -> begin() -> y << " )" << std::endl; //p1
        std::cout << "( " << _up   -> begin() -> x << " , " << _up   -> begin() -> y << " )" << std::endl; //p2
        std::cout << "( " << _up   -> end()   -> x << " , " << _up   -> end()   -> y << " )" << std::endl; //p3
        std::cout << "( " << _down -> end()   -> x << " , " << _down -> end()   -> y << " )" << std::endl; //p4  
        std::cout << "counter = " << counter << std::endl;
    };
};


class Brick : public Obstacle{
public:   
    Brick(Point* p1, Point* p2, Point* p3, Point* p4, bool destr, int count)
    : Obstacle(p1, p2, p3, p4, destr, count)
    {};
    void touch()
    {
        --counter;
    }    
};


#endif /* OBSTACLE_H */

