/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "parser.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


Obstacle* Parser::create_obstacle(Object* p_obj)
{
    Obstacle* p;
    char ch = p_obj -> symbol;
    switch (ch)
    {        
        case 'v':
            p = new Obstacle(p_obj->p1, p_obj->p2, p_obj->p3, p_obj->p4);
            break;
        case 'w':
            p = new Obstacle(p_obj->p1, p_obj->p2, p_obj->p3, p_obj->p4);
            break;
        case 'a':
            p = new Brick(p_obj->p1, p_obj->p2, p_obj->p3, p_obj->p4, true,  1); 
            break;
        case 'b':
            p = new Brick(p_obj->p1, p_obj->p2, p_obj->p3, p_obj->p4, true, 1);
            break;
        default:
            std::cout << "wrong symbol: " << ch << std::endl;
    };
    return p;
}


void Parser::create_obstacles(std::vector<Obstacle*> &vector_obstacles)
{
    for (Object* p_obj:vector_objects)
    {
        Obstacle* p_obs = create_obstacle(p_obj);
        vector_obstacles.push_back(p_obs);
    };
};

void Parser::check_symbol(char ch, int x, int y)
{
    if (ch == '.') return;
    changed = false;
    if (vector_objects.empty()) 
    {
        vector_objects.push_back(new Object(ch, x, y));
        changed = true;
    } else 
    { 
        for (int i = 0; i< vector_objects.size(); ++i)
        // extend an existent object or create new one
        {
            if (vector_objects[i]->is_neighbour_left(ch, x, y)) 
            {
                vector_objects[i]->add_right(x,y);
                changed = true;
//                std::cout << "neighbour from left" << std::endl;
//                return;
            };
            if (vector_objects[i]->is_neighbour_up(ch, x, y)) 
            {
                vector_objects[i]->add_down(x,y);
                changed = true;
//                return;
            };    
        };
    };    
    if (!changed) vector_objects.push_back( new Object(ch, x, y));
};

void Parser::parse_line (std::string &str, int x, int y)
{
    std::stringstream ifs_line {str};
    char ch;
    while(ifs_line >> ch)
    {
        check_symbol (ch, x, y);
        x+=size;
    };
};


void Parser::parse_file (const std::string& file_name)
{
    std::ifstream ifs{file_name};
    if (!ifs)
    {
        std::cerr <<"Impossible to open a file " << file_name << std::endl;
        return;
    };     
    int y = 0;
    std::string str;
    while (ifs >> str){
        int x = 0;
        parse_line(str, x, y);
        y+=size;
    };
    std::cout << "Parsing is finished" << std::endl;
};

void Parser::print()
{
    for (int i=0; i<vector_objects.size(); ++i)
    {

        std::cout << "Object " << i << "\t" ;
        (vector_objects[i])->print();
    };
};



