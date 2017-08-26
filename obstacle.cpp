/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "obstacle.h"
#include <math.h>

/* For Line:
 *  distance = |(y2-y1)x0 - (x2-x1)y0 + x2y1 - y2x1| / sqrt( (y2-y1)^2 + (x2-x1)^2 )
 * - the formula for defining a distance(perpendicular) between a line and a point p(x0, y0).
 * a=y2-y1; b=x2-x1; c=x2y1-y2x1; length=sqrt( (y2-y1)^2 + (x2-x1)^2 ) 
 * Variables a,b,c,length are calculated here for saving time later 
*/

float Line::set_a(){return (*p_end).y - (*p_begin).y;};
float Line::set_b(){return p_end->x - p_begin->x;};
float Line::set_c(){return p_end->x * p_begin->y - p_end->y * p_begin->x;};
float Line::set_length2(){return ((p_end->y - p_begin->y)*(p_end->y - p_begin->y) + (p_end->x - p_begin->x)*(p_end->x - p_begin->x));};
float Line::set_length(){return sqrt(_length2);};
