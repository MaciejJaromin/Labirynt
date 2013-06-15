#ifndef AGENTS_PIOTR_H_INCLUDED
#define AGENTS_PIOTR_H_INCLUDED

#include <string>
#include "bullerbyn.h"

#define M_WALL 3

class random_walker : public agents
{
public:
    random_walker();
    std::pair<int, std::string> move(int items[3][3], int mates[20], std::string reading[3][3]);
};

class sealing_random_walker : public agents
{
public:
    sealing_random_walker(int id);
    std::pair<int, std::string> move(int items[3][3], int mates[20], std::string reading[3][3]);
};

class refactored_solo_leftwall : public agents
{
public:
    refactored_solo_leftwall();
    std::pair<int, std::string> move(int items[3][3], int mates[20], std::string reading[3][3]);
};

#endif // AGENTS_PIOTR_H_INCLUDED
