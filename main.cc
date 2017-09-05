/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"
#include <iostream>
#include <cmath>


//#include<boost/thread.hpp>



std::vector<Obstacle*> Settings::vector_obstacles; 

int main(int argc, char**argv) {

    Ball* ball = new Ball(500, 495, M_PI/4, Settings::ball_radius, Settings::ball_speed);     
    
    Parser pars = Parser();
    pars.parse_file("config1");
//    pars.print();

    pars.create_obstacles( Settings::vector_obstacles );
//    Settings::print_obstacles();

    std::cout << "\t\tBEGIN" << std::endl;
    
    Driver game = Driver(Settings::vector_obstacles, ball, Settings::collision);
//~    game.print_obstacles();


    
    while( game.is_in_vector_deletable_obstacle())
    {
        game.move_ball(ball);
    };
   
    std::cout << "Game over" << std::endl;
    game.print_obstacles();    

    std::cout << "ball : " << ball->x() << " , " << ball->y() << std::endl;
    delete ball;
    
    return 0;
}
