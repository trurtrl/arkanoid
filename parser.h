/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef PARSER_H
#define PARSER_H

#include "obstacle.h"
#include <iostream>
#include <vector>

struct Settings
{
    static const int ball_radius = 3;
    static const int ball_speed = 5;
    static const int block_size = 10;
    static const int collision = 20; // after this amount of collision a reflection angle will be changed for preventing looping
    static std::vector<Obstacle*> vector_obstacles;
    static void print_obstacles()
    {
        std::cout << "\tThere are " << vector_obstacles.size() << " obstacles" << std::endl;
        for (int i=0; i<vector_obstacles.size(); ++i)
        {
            std::cout << "Obstacle " << i << "\t" ;
            (vector_obstacles[i])->print();            
        };
    };
    
};

//std::vector<Obstacle*> Settings::vector_obstacles {};


struct Object{
    Point* p1;
    Point* p2;
    Point* p3;
    Point* p4;
    int size; //size of block
    char symbol; //defines type of object
   
    Object(char sym, int x, int y)
    :symbol{sym}, size{Settings::block_size}    
    {
        p1 = new Point (x, y);
        p2 = new Point (x, y+size);
        p3 = new Point (x+size, y+size);
        p4 = new Point (x+size, y);    
    }

    Object()
    {
        p1 = 0; 
        p2 = 0; 
        p3 = 0; 
        p4 = 0;
    };
    ~Object()
    {
        delete p1, p2, p3, p4;
    };
       
    void add_right(int x, int y)
    {
        (p3->x) += size;        
        (p4->x) += size;        
    };    
    void add_down(int x, int y)
    {
        p2->y += size;
        p3->y += size;         
    };
    
    bool is_neighbour_left(char ch, int x, int y)
    {
        return (symbol == ch && p3->x == x && p3->y == y+size && p4->x == x && p4->y == y);
    };
    
    bool is_neighbour_up(char ch, int x, int y)
    {
        return (symbol == ch && p2->x == x && p2->y == y && p3->x == x+size && p3->y == y);
    };   
    
    void print()
    {
        std::cout << "=== " <<  symbol << " ===" << std::endl;        
        std::cout << "\t" << p1->x << "," << p1->y << std::endl;
        std::cout << "\t" << p2->x << "," << p2->y << std::endl;
        std::cout << "\t" << p3->x << "," << p3->y << std::endl;        
        std::cout << "\t" << p4->x << "," << p4->y << std::endl;
    }
};


struct Parser{
//    int block_size;
    std::vector<Object*> vector_objects;
    bool changed; // whether any object was changed
    int size; //size of blocks
    Parser()
    :size{Settings::block_size}
    {};
    ~Parser()
    {
        for(Object* p_obj:vector_objects) delete p_obj;
        vector_objects.clear();
    }
    Obstacle* create_obstacle(Object* p_obj);
    void create_obstacles(std::vector<Obstacle*> &vector_obstacles);
    void check_symbol(char ch, int x, int y);
    void parse_line (std::string &str, int x, int y);
    void parse_file (const std::string& file_name);
    void print();
};



#endif /* PARSER_H */

