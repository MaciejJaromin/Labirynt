#include "agents_maciej.h"

solo_straight::solo_straight(int give_id)
{
    id = give_id;
}

std::pair<int, std::string> solo_straight::move (int items[3][3],int mates[20],std::string reading[3][3])
{

    /* decision - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing
    */


    if (direction == 1 && items[0][1] == M_WALL)
        direction = 4;
    else if (direction == 2 && items[2][1] == M_WALL)
        direction = 3;
    else if (direction == 3 && items[1][0] == M_WALL)
        direction = 1;
    else if (items[1][2] == M_WALL)
        direction = 2;

    //and returning it
    std::pair<int, std::string> decision;
    decision.first = direction;
    decision.second = "";
    return decision;

}



solo_leftwall::solo_leftwall(int give_id)
{
    id=give_id;
    direction = 1;
}

std::pair<int, std::string> solo_leftwall::move(int items[3][3],int mates[20],std::string reading[3][3])
{

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */




    if (direction == 1)
    {
        if (items[1][0] != M_WALL && items[2][0] == M_WALL)
            direction = 3;
        else if (items[0][1] != M_WALL)
            direction = 1;
        else if (items[1][2] != M_WALL)
            direction = 4;
        else
            direction = 2;

    }
    else if (direction == 2)
    {
        if (items[1][2] != M_WALL && items[0][2] == M_WALL)
            direction = 4;
        else if (items[2][1] != M_WALL)
            direction = 2;
        else if (items[1][0] != M_WALL)
            direction = 3;
        else
            direction = 1;
    }
    else if (direction == 3)
    {
        if (items[2][1] != M_WALL && items[2][2] == M_WALL)
            direction = 2;
        else if (items[1][0] != M_WALL)
            direction = 3;
        else if (items[0][1] != M_WALL)
            direction = 1;
        else
            direction = 4;
    }
    else
    {
        if (items[0][1] != M_WALL && items[0][0] == M_WALL)
            direction = 1;
        else if (items[1][2] != M_WALL)
            direction = 4;
        else if (items[2][1] != M_WALL)
            direction = 2;
        else
            direction = 3;
    }

    //and returning it
    std::pair<int, std::string> decision;
    decision.first = direction;
    decision.second = "";
    return decision;

}


writer::writer(int give_id)
{
    id = give_id;
    direction = 1;
    state = 1;
}

std::pair<int, std::string> writer::move(int items[3][3],int mates[20],std::string reading[3][3])
{

    /* decision - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing
    */

    std::pair<int, std::string> decision;
    decision.first = 0;
    decision.second = "";

    if (state == 0)
    {
        //state = 1;
        decision.first = direction;
        decision.second = "";
        return decision;
    }
    else
    {
        //count the number of ways to go
        int dir_number = 0;
        if (items[0][1] != M_WALL)
            dir_number++;
        if (items[2][1] != M_WALL)
            dir_number++;
        if (items[1][0] != M_WALL)
            dir_number++;
        if (items[1][2] != M_WALL)
            dir_number++;

        if (dir_number == 0) //trivial
            return decision;
        else if (dir_number == 1) //trivial
        {
            if (items[0][1] != M_WALL)
                direction = 1;
            else if (items[2][1] != M_WALL)
                direction = 2;
            else if (items[1][0] != M_WALL)
                direction = 3;
            else if (items[1][2] != M_WALL)
                direction = 4;
            decision.first = direction;
            return decision;
        }
        else if (dir_number == 2) //pick the direction you didn't come from
        {
            if (direction != 2 && items[0][1] != M_WALL)
                direction = 1;
            else if (direction != 1 && items[2][1] != M_WALL)
                direction = 2;
            else if (direction != 4 && items[1][0] != M_WALL)
                direction = 3;
            else if (direction != 3 && items[1][2] != M_WALL)
                direction = 4;
            decision.first = direction;
            return decision;
        }
        else
        {
            int previous_dir = direction;
            int came_from = previous_dir - 1 + (previous_dir % 2);

            int dir_priorities[5];
            for (int i = 0; i < 5; i++)
                dir_priorities[i] = 0;

            //walls
            if (items[0][1] == M_WALL)
                dir_priorities[1] = -1;
            else if (items[2][1] == M_WALL)
                dir_priorities[2] = -1;
            else if (items[1][0] == M_WALL)
                dir_priorities[3] = -1;
            else if (items[1][2] == M_WALL)
                dir_priorities[4] = -1;

            //analyze writing
            std::string msg = reading[1][1];
            bool loop = false;

            for (int i = 0; i < msg.length() - 2; i += 3)
            {
/*
                if (msg[i] == id)
                    loop = true;//(msg[i+2] != came_from);

                int from = msg[i+1];
                int to = msg[i+2];

                if (dir_priorities[from] == 0)
                    dir_priorities[from] = 2;
                else if (dir_priorities[from] == 1)
                    dir_priorities[from] = 3;

                if (dir_priorities[to] == 0)
                    dir_priorities[to] = 1;
                else if (dir_priorities[to] == 2)
                    dir_priorities[to] = 3;*/
            }


            if (loop)
            {
                msg.push_back(id);
                msg.push_back(came_from);
                msg.push_back(came_from);
                direction = came_from;
            }
            else
            {
                for (int i = 3; i >= 0; i--)
                {
                    for (int j = 1; j < 5; j++)
                    {
                        if (dir_priorities[j] == i)
                            direction = j;
                    }
                }

                msg.push_back(id);
                msg.push_back(came_from);
                msg.push_back(direction);
            }
            state = 0;
            decision.first = 0;
            //std::strcpy (decision.second, msg.c_str());
            return decision;

            //I hate parsing strings for info

        }
    }

}
