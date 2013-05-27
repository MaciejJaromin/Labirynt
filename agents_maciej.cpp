#include "agents_maciej.h"

solo_straight::solo_straight()
{
    data_int[0] = 4;
}

char** solo_straight::move(int items[3][3],int mates[3][3],char reading[3][3][40])
{

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */



    int direction = data_int[0]; //load the last choice made
    if (direction == 1)
    {
        if (items[0][1] != M_WALL)
            decision[0] = "1";
        else
        {
            decision[0] = "4";
            data_int[0] = 4;
        }
    }
    else if (direction == 2)
    {
        if (items[2][1] != M_WALL)
            decision[0] = "2";
        else
        {
            decision[0] = "3";
            data_int[0] = 3;
        }

    }
    else if (direction == 3)
    {
        if (items[1][0] != M_WALL)
            decision[0] = "3";
        else
            {
            decision[0] = "1";
            data_int[0] = 1;
        }
    }
    else
    {
        if (items[1][2] != M_WALL)
            decision[0] = "4";
        else
            {
            decision[0] = "2";
            data_int[0] = 2;
        }
    }


    decision[1]="";

    //and returning it
    return decision;

}



solo_leftwall::solo_leftwall()
{
    data_int[0] = 1;
}

char** solo_leftwall::move(int items[3][3],int mates[3][3],char reading[3][3][40])
{

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */




    int direction = data_int[0]; //load the last choice made
    if (direction == 1)
    {
        if (items[1][0] != M_WALL && items[2][0] == M_WALL)
        {
            data_int[0] = 3;
            decision[0] = "3";
        }
        else if (items[0][1] != M_WALL)
        {
            decision[0] = "1";
        }
        else if (items[1][2] != M_WALL)
        {
            data_int[0] = 4;
            decision[0] = "4";
        }
        else
        {
            data_int[0] = 2;
            decision[0] = "2";
        }

    }
    else if (direction == 2)
    {
        if (items[1][2] != M_WALL && items[0][2] == M_WALL)
        {
            data_int[0] = 4;
            decision[0] = "4";
        }
        else if (items[2][1] != M_WALL)
        {
            decision[0] = "2";
        }
        else if (items[1][0] != M_WALL)
        {
            data_int[0] = 3;
            decision[0] = "3";
        }
        else
        {
            data_int[0] = 1;
            decision[0] = "1";
        }
    }
    else if (direction == 3)
    {
        if (items[2][1] != M_WALL && items[2][2] == M_WALL)
        {
            data_int[0] = 2;
            decision[0] = "2";
        }
        else if (items[1][0] != M_WALL)
        {
            decision[0] = "3";
        }
        else if (items[0][1] != M_WALL)
        {
            data_int[0] = 1;
            decision[0] = "1";
        }
        else
        {
            data_int[0] = 4;
            decision[0] = "4";
        }
    }
    else
    {
        if (items[0][1] != M_WALL && items[0][0] == M_WALL)
        {
            data_int[0] = 1;
            decision[0] = "1";
        }
        else if (items[1][2] != M_WALL)
        {
            decision[0] = "4";
        }
        else if (items[2][1] != M_WALL)
        {
            data_int[0] = 2;
            decision[0] = "2";
        }
        else
        {
            data_int[0] = 3;
            decision[0] = "3";
        }
    }


    decision[1]="";

    //and returning it
    return decision;

}
