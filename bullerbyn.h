#ifndef BULLERBYN_H_INCLUDED
#define BULLERBYN_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include <utility>

const int AGENTS_AMOUNT = 2;


// main class for all agents
class agents
{
    protected:
    //Data you can use to remember sth
    //Changed to protected so that classes inheriting from agents can access the data - Maciej
    int  data_int[5];
    char data_char[3][40];
    std::string data_string[3]; //replacing the char array agent data with strings, keeping the char arrays for backwards compatibility

    int id;

    public:
    agents(){};
    agents(int id):id(id){};

    virtual std::pair<int, std::string> move(int items[3][3],int mates[20],std::string reading[3][3]) = 0;

    //setting agents picture - don't work now
    char image[10];
};

// This agents are stupid!

// agents 1 and 2 - the group members

class bullerbyn1 : public agents
{
    public:
    bullerbyn1(int give_id)
    {
    id=give_id;
    }

    //function making decisions - what to do
    std::pair<int, std::string> move(int items[3][3],int mates[20],std::string reading[3][3]);
};

class bullerbyn2 : public agents
{
    public:
    bullerbyn2(int give_id)
    {
    id=give_id;
    }
    std::pair<int, std::string> move(int items[3][3],int mates[20],std::string reading[3][3]);
};




#endif // BULLERBYN_H_INCLUDED
