#include "agents_piotr.h"
#include "agents_common_tools.h"

blind_walker::blind_walker(Choice_strategy& strategy):strategy(strategy)
{
    data_int[0] = 1;
    srand(time(NULL));
}

std::pair<int, std::string> blind_walker::move(int items[3][3], int mates[20], std::string reading[3][3])
{
    int direction = data_int[0]; //load the last choice made

    // Set up a reference frame (such that we are facing north)
    rotated_view_of_square_matrix<int,3> rotated_items(items);
    rotated_view_of_square_matrix<std::string,3> rotated_reading(reading);
    int clockwise_rotation=0;
    while(direction!=1)
    {
        direction = rotate_direction_clockwise(direction);
        rotated_items.rotate_clockwise();
        rotated_reading.rotate_clockwise();
        ++clockwise_rotation;
    }
    // Do the logic, make decision
    int final_decision=0;
    bool can_go_left = rotated_items.get(1,0) != M_WALL;
    bool can_go_right = rotated_items.get(1,2) != M_WALL;
    bool can_go_straight = rotated_items.get(0,1) != M_WALL;
    {
        int options[3];
        int i=0;
        if(can_go_left)
            options[i++] = 3;
        if(can_go_right)
            options[i++] = 4;
        if(can_go_straight)
            options[i++] = 1;
        if(i==0)
            final_decision = 2;//turn back
        else
            final_decision = strategy.choose(options,i);
    }

    //Revert to proper reference frame
    for(int i=0;i<clockwise_rotation;++i)
        final_decision = rotate_direction_counterclockwise(final_decision);
    //
    data_int[0] = final_decision;
    return std::make_pair<int,std::string>(final_decision,"");
}

sealing_walker::sealing_walker(int id, Choice_strategy& strategy):agents(id),strategy(strategy)
{
    data_int[0] = 1;
    data_int[1] = false;
    srand(time(NULL));
}

bool is_dead_end_sign(std::string reading)
{
    if(reading.length()<5)
        return false;
    if(reading[0]=='d')
    {
        for(int i=1;i<=4;++i)
            if(reading[i]!='0' && reading[i]!='1')
                return false;
        return true;
    }
    else
        return false;
}
bool is_dead_end(std::string reading, int direction)
{
    if(!is_dead_end_sign(reading))
        return false;
    else
        return reading[direction]=='1';
}
std::string append_dead_end_sign(std::string reading, int direction)
{
    if(is_dead_end_sign(reading))
    {
        reading[direction] = '1';
        return reading;
    }
    else
    {
        std::string ret = "d0000";
        ret[direction] = '1';
        return ret;
    }
}

std::pair<int, std::string> sealing_walker::move(int items[3][3], int mates[20], std::string reading[3][3])
{
    int& direction = data_int[0];
    int& dead_end = data_int[1];
    std::string writing;

    // Set up a reference frame (such that we are facing north)
    rotated_view_of_square_matrix<int,3> rotated_items(items);
    rotated_view_of_square_matrix<std::string,3> rotated_reading(reading);
    int clockwise_rotation=0;
    while(direction!=1)
    {
        direction = rotate_direction_clockwise(direction);
        rotated_items.rotate_clockwise();
        rotated_reading.rotate_clockwise();
        ++clockwise_rotation;
    }
    // Do the logic, make decision
    int final_decision = 0;
    bool can_go_left     = rotated_items.get(1,0) != M_WALL && !is_dead_end(reading[1][1],rotate_direction_counterclockwise(3,clockwise_rotation));
    bool can_go_right    = rotated_items.get(1,2) != M_WALL && !is_dead_end(reading[1][1],rotate_direction_counterclockwise(4,clockwise_rotation));
    bool can_go_straight = rotated_items.get(0,1) != M_WALL && !is_dead_end(reading[1][1],rotate_direction_counterclockwise(1,clockwise_rotation));
    {
        int options[3];
        int i=0;
        if(can_go_left)
            options[i++] = 3;
        if(can_go_right)
            options[i++] = 4;
        if(can_go_straight)
            options[i++] = 1;
        if(i==0)
        {
            final_decision = 2;//turn back
            dead_end = true;
        }
        else if(i==1)
        {
            final_decision = options[0];
        }
        else
        {
            if(dead_end)
            {
                writing = append_dead_end_sign(reading[1][1], rotate_direction_counterclockwise(2,clockwise_rotation));
                dead_end = false;
            }
            final_decision = strategy.choose(options,i);
        }
    }

    //Revert to proper reference frame
    for(int i=0;i<clockwise_rotation;++i)
        final_decision = rotate_direction_counterclockwise(final_decision);
    //
    direction = final_decision;
    if(writing!="")
        final_decision = 0;
    std::cout << id << "-" << dead_end << ":" << writing << "=" << reading[1][1] << std::endl;
    return std::make_pair<int,std::string>(final_decision,writing);
}

