/*#ifndef AGENTS_MACIEJ_H_INCLUDED
#define AGENTS_MACIEJ_H_INCLUDED


#include "bullerbyn.h"

#define M_WALL 3

//All my agents inherit from this abstract base class
//In case we want to check whose agent found the treasure or something like that
class maciej_base : public agents
{
    public:

    //function making decisions - what to do
    virtual char** move(int items[3][3],int mates[3][3],char reading[3][3][40]) = 0;
};

class solo_straight : public maciej_base
{
public:
    solo_straight();
    char** move(int items[3][3],int mates[3][3],char reading[3][3][40]);
};

class solo_leftwall : public maciej_base
{
public:
    solo_leftwall();
    char** move(int items[3][3],int mates[3][3],char reading[3][3][40]);
};

#endif // AGENTS_MACIEJ_H_INCLUDED
*/
