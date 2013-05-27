#include "agents_piotr.h"
#include "agents_common_tools.h"

random_walker::random_walker()
{
    data_int[0] = 1;
    srand(time(NULL));
}

char** random_walker::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);
    int direction = data_int[0]; //load the last choice made

    // Set up a reference frame (such that we are facing north)
    rotated_view_of_square_matrix<int,3> rotated_items(items);
    int clockwise_rotation=0;
    while(direction!=1)
    {
        direction = rotate_direction_clockwise(direction);
        rotated_items.rotate_clockwise();
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
            final_decision = options[rand()%i];
    }

    //Revert to proper reference frame
    for(int i=0;i<clockwise_rotation;++i)
        final_decision = rotate_direction_counterclockwise(final_decision);

    //
    static char digits[5][2] = {"0","1","2","3","4"};
    decision[0] = digits[final_decision];
    decision[1] = "";
    data_int[0] = final_decision;
    return decision;

}

refactored_solo_leftwall::refactored_solo_leftwall()
{
    data_int[0] = 1;
    srand(time(NULL));
}

char** refactored_solo_leftwall::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);
    int direction = data_int[0]; //load the last choice made

    // Set up a reference frame (such that we are facing north)
    rotated_view_of_square_matrix<int,3> rotated_items(items);
    int clockwise_rotation=0;
    while(direction!=1)
    {
        direction = rotate_direction_clockwise(direction);
        rotated_items.rotate_clockwise();
        ++clockwise_rotation;
    }
    // Do the logic, make decision
    int final_decision=0;
    if (rotated_items.get(1,0) != M_WALL && rotated_items.get(2,0) == M_WALL)
    {
        final_decision = 3;
    }
    else if (rotated_items.get(0,1) != M_WALL)
    {
        final_decision = 1;
    }
    else if (rotated_items.get(1,2) != M_WALL)
    {
        final_decision = 4;
    }
    else
    {
        final_decision = 2;
    }
    //Revert to proper reference frame
    for(int i=0;i<clockwise_rotation;++i)
        final_decision = rotate_direction_counterclockwise(final_decision);

    //
    static char digits[5][2] = {"0","1","2","3","4"};
    decision[0] = digits[final_decision];
    decision[1] = "";
    data_int[0] = final_decision;
    return decision;

}

