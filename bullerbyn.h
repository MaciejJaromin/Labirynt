#ifndef BULLERBYN_H_INCLUDED
#define BULLERBYN_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

const int AGENTS_AMOUNT = 2;


// main class for all agents
class agents
{
    protected:
    //Data you can use to remember sth
    //Changed to protected so that classes inheriting from agents can access the data - Maciej
    int  data_int[5];
    char data_char[3][20];

    public:
    agents(){};

    virtual char** move(int items[3][3],int mates[3][3],int reading[3][3][20]) = 0;

    //setting agents picture - don't work now
    char image[10];
};

// This agents are stupid!

// agents 1 and 2 - the group members

class bullerbyn1 : public agents
{
    public:
    bullerbyn1(){};

    //function making decisions - what to do
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};

class bullerbyn2 : public agents
{
    public:
    bullerbyn2(){};
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};




#endif // BULLERBYN_H_INCLUDED
