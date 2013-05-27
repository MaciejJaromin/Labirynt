#ifndef AGENTS_PIOTR_H_INCLUDED
#define AGENTS_PIOTR_H_INCLUDED


#include "bullerbyn.h"

#define M_WALL 3

class random_walker : public agents
{
public:
    random_walker();
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};

class refactored_solo_leftwall : public agents
{
public:
    refactored_solo_leftwall();
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};

#endif // AGENTS_PIOTR_H_INCLUDED
