#include "bullerbyn.h"

//first type of agent - moving down


std::pair<int, char*> bullerbyn1::move(int items[3][3],int mates[AGENTS_AMOUNT],char reading[3][3][40])
{
    std::pair<int, char*> decision;

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */

    //setting "stupid" decision
    decision.first=0;
    decision.second="juhu1";

    //and returning it
    return decision;
}

//first type of agent - moving right
std::pair<int, char*> bullerbyn2::move(int items[3][3],int mates[AGENTS_AMOUNT],char reading[3][3][40])
{
    std::pair<int, char*> decision;
    decision.first=4;
    decision.second="juhu2";
    return decision;
}



