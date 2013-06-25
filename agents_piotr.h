#ifndef AGENTS_PIOTR_H_INCLUDED
#define AGENTS_PIOTR_H_INCLUDED

#include <string>
#include <cassert>
#include "bullerbyn.h"

#define M_WALL 3

class Choice_strategy
{
protected:
    bool contains(int options[3], int options_len, int value)
    {
        for(int i=0;i<options_len;++i)
            if(options[i]==value)
                return true;
        return false;
    }
public:
    virtual int choose(int options[3], int i) = 0;
};
class Random_choice : public Choice_strategy
{
public:
    Random_choice()
    {
        srand(time(NULL));
    }
    virtual int choose(int options[3], int i)
    {
        return options[rand()%i];
    }
};
class Leftwall_choice : public Choice_strategy
{
public:
    virtual int choose(int options[3], int options_len)
    {
        if(contains(options,options_len,3))
            return 3;
        if(contains(options,options_len,1))
            return 1;
        if(contains(options,options_len,4))
            return 4;
        assert(false);
    }
};

class Rightwall_choice : public Choice_strategy
{
public:
    virtual int choose(int options[3], int options_len)
    {
        if(contains(options,options_len,4))
            return 4;
        if(contains(options,options_len,1))
            return 1;
        if(contains(options,options_len,3))
            return 3;
        assert(false);
    }
};

/////////////////////////////////
class blind_walker : public agents
{
    Choice_strategy& strategy;
public:
    blind_walker(Choice_strategy& strategy);
    std::pair<int, std::string> move(int items[3][3], int mates[20], std::string reading[3][3]);
};

class sealing_walker : public agents
{
    Choice_strategy& strategy;
public:
    sealing_walker(int id, Choice_strategy& strategy);
    std::pair<int, std::string> move(int items[3][3], int mates[20], std::string reading[3][3]);
};

#endif // AGENTS_PIOTR_H_INCLUDED
