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

std::vector<message> writer::parse(std::string m)
{
    std::vector<message> v;
    std::vector<int> ints;
    std::size_t i = 0;
    //std::size_t j = m.find("|", i);
    while (i != std::string::npos)
    {
        std::string num = m.substr(i, std::string::npos);
        const char* x = num.c_str();
        int y = atoi(x);
        ints.push_back(y);
        //i = j + 1;
        i = m.find("|", i);
        if (i != 0 && i != std::string::npos)
            i++;

    }
    for (int i = 0; i+2 < ints.size(); i += 3)
    {
        message msg;
        msg.id = ints[i];
        msg.from = ints[i+1];
        msg.to = ints[i+2];

        v.push_back(msg);
    }
    return v;
}

std::string writer::append(std::string orig, message m)
{
    //std::string n;
    //n = orig;
    //n += std::to_string(m.id); //bugged in MinGW apparently

    std::stringstream n;
    n.str(orig);
    n << m.id << "|" << m.from << "|" << m.to << "|";
    std::string ns = n.str();
    return ns;
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
        state = 1;
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
            // previous_direction = direction;
            int came_from = direction - 1 + 2*(direction % 2);
            bool loop = false;
            message loop_msg;
            int orig = 0;

            state = 0; //write this turn, move the next

            std::string writing = reading[1][1];

            std::vector<message> msgs = parse(writing);

            int dir_priorities[5];
            for (int i = 0; i < 5; i++)
                dir_priorities[i] = 0;


            for (int i = 0; i < msgs.size(); i++)
            {
                if (msgs[i].id == id)
                {
                    if (msgs[i].to != came_from)
                    {
                        loop = true;
                        loop_msg = msgs[i];
                    }
                    else
                        loop = false;

                    if (orig == 0)
                        orig = msgs[i].from;

                    if (msgs[i].to == msgs[i].from && i != orig)
                        dir_priorities[msgs[i].to] += 100; //if you looped to here, ignore the looped direction

                }

                dir_priorities[msgs[i].from] += 1;
                dir_priorities[msgs[i].to] += 1;
                if (msgs[i].from == msgs[i].to)
                    dir_priorities[msgs[i].from] += 100; //evidence of looping
            }
            dir_priorities[came_from] += 5; //don't like to turn back


            if (items[0][1] == M_WALL)
                dir_priorities[1] = -1;
            if (items[2][1] == M_WALL)
                dir_priorities[2] = -1;
            if (items[1][0] == M_WALL)
                dir_priorities[3] = -1;
            if (items[1][2] == M_WALL)
                dir_priorities[4] = -1;


            for (int i = 1; i < 5; i++)
            {
                if (i != orig && dir_priorities[i] == 0)
                    dir_priorities[orig] += 100; //don't give up if there's unexplored passages
            }


            message m;
            m.id = id;



            if (loop)
            {
                direction = came_from;
            }
            else
            {
                for (int i = 1; i < 5; i++)
                {
                    if ((dir_priorities[i] < dir_priorities[direction] && dir_priorities[i] >= 0) || dir_priorities[direction] < 0)
                        direction = i;
                }
            }

            m.from = came_from;
            m.to = direction;

            writing = append(writing, m);
            if (loop)
                writing = append(writing, loop_msg);

            decision.second = writing;

            return decision;

            //I hate parsing strings for info

        }
    }

}
