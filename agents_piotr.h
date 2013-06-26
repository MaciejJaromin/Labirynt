#ifndef AGENTS_PIOTR_H_INCLUDED
#define AGENTS_PIOTR_H_INCLUDED

#include <string>
#include <vector>
#include <cassert>
#include <ctime>
#include "bullerbyn.h"
#include "agents_common_tools.h"

#define M_WALL 3

class Choice_strategy
{
protected:
    bool contains(std::vector<int> options, int value)
    {
        for(unsigned int i=0;i<options.size();++i)
            if(options[i]==value)
                return true;
        return false;
    }
public:
    virtual int choose(std::vector<int> options, rotated_view_of_square_matrix<int,3>& items) = 0;
};

class Explorer : public Choice_strategy
{
    Choice_strategy& strategy;
public:
    Explorer(Choice_strategy& strategy):strategy(strategy)
    {}
    virtual int choose(std::vector<int> options, rotated_view_of_square_matrix<int,3>& items)
    {
        std::vector<int> filtered_options;
        for(unsigned int i=0;i<options.size();++i)
        {
            const int TILE_UNVISITED = 0;//fixme
            const int TILE_TREASURE = 2;//fixme
            if( (options[i]==1 && (items.get(0,1)==TILE_UNVISITED || items.get(0,1)==TILE_TREASURE)) ||
                (options[i]==3 && (items.get(1,0)==TILE_UNVISITED || items.get(1,0)==TILE_TREASURE)) ||
                (options[i]==4 && (items.get(1,2)==TILE_UNVISITED || items.get(1,2)==TILE_TREASURE))  )
                    filtered_options.push_back(options[i]);
        }
        if(filtered_options.size()==0)
            return strategy.choose(options,items);
        else
            return strategy.choose(filtered_options,items);
    }
};

class Random_choice : public Choice_strategy
{
public:
    Random_choice()
    {
        srand(time(NULL));//just in case
    }
    virtual int choose(std::vector<int> options, rotated_view_of_square_matrix<int,3>& items)
    {
        if(options.size()==0)
            return 2;//turn back
        else
            return options[rand()%options.size()];
    }
};
class Leftwall_choice : public Choice_strategy
{
public:
    virtual int choose(std::vector<int> options, rotated_view_of_square_matrix<int,3>& items)
    {
        if(contains(options,3)) // This part is more complex to avoid going in circles while using this strategy with Explorer strategy
        {
            const int TILE_WALL = 3;//fixme

            if( items.get(2,0)!=TILE_WALL )// if we lost the wall we were following
            {
                if( items.get(0,1)!=TILE_WALL )// if we don't have the wall in front of us
                    return 1;// then go straight to avoid going in circles forever
                else
                    return 4;// when no wall on the left, but we hit a wall in front of us then follow right
            }
            else
                return 3;
        }
        if(contains(options,1))
            return 1;
        if(contains(options,4))
            return 4;
        assert(false);
    }
};

class Rightwall_choice : public Choice_strategy
{
public:
    virtual int choose(std::vector<int> options, rotated_view_of_square_matrix<int,3>& items)
    {
        if(contains(options,4)) // This part is more complex to avoid going in circles while using this strategy with Explorer strategy
        {
            const int TILE_WALL = 3;//fixme

            if( items.get(2,2)!=TILE_WALL )// if we lost the wall we were following
            {
                if( items.get(0,1)!=TILE_WALL )// if we don't have the wall in front of us
                    return 1;// then go straight to avoid going in circles forever
                else
                    return 3;// when no wall on the left, but we hit a wall in front of us then follow right
            }
            else
                return 4;
        }
        if(contains(options,1))
            return 1;
        if(contains(options,3))
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
