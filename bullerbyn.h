#ifndef BULLERBYN_H_INCLUDED
#define BULLERBYN_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
<<<<<<< HEAD
#include <utility>
=======
>>>>>>> b5fb966b2946302bc8093b1ec2d5df0c668d3b9d

const int AGENTS_AMOUNT = 2;


// main class for all agents
class agents
{
    protected:
    //Data you can use to remember sth
    //Changed to protected so that classes inheriting from agents can access the data - Maciej
    int  data_int[5];
    char data_char[3][40];

    int id;

    public:
    agents(){};

    virtual std::pair<int, char*> move(int items[3][3],int mates[20],char reading[3][3][40]) = 0;

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
    std::pair<int, char*> move(int items[3][3],int mates[20],char reading[3][3][40]);
};

class bullerbyn2 : public agents
{
    public:
    bullerbyn2(int give_id)
    {
    id=give_id;
    }
    std::pair<int, char*> move(int items[3][3],int mates[20],char reading[3][3][40]);
};




#endif // BULLERBYN_H_INCLUDED
