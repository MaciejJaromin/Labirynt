#include "bullerbyn.h"

//first type of agent - moving down
char** bullerbyn1::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */

    //setting "stupid" decision
    decision[0]="2";
    decision[1]="juhu1";

    //and returning it
    return decision;
}

//first type of agent - moving right
char** bullerbyn2::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);
    decision[0]="4";
    decision[1]="juhu2";
    return decision;
}



