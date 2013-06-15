#ifndef AGENTS_PIOTR_H_INCLUDED
#define AGENTS_PIOTR_H_INCLUDED


#include "bullerbyn.h"

#define M_WALL 3

class random_walker : public agents
{
public:
    random_walker();
    std::pair<int, char*> move(int items[3][3], int mates[20], char reading[3][3][40]);
};

class sealing_random_walker : public agents
{
public:
    sealing_random_walker(int id);
    std::pair<int, char*> move(int items[3][3], int mates[20], char reading[3][3][40]);
};

class refactored_solo_leftwall : public agents
{
public:
    refactored_solo_leftwall();
    std::pair<int, char*> move(int items[3][3], int mates[20], char reading[3][3][40]);
};

#endif // AGENTS_PIOTR_H_INCLUDED
