#include "agents_common_tools.h"
#include <cassert>

int rotate_direction_clockwise(int direction, int rotation_clockwise)
{
    if(rotation_clockwise>0)
    {
        rotation_clockwise %= 4;
        int new_direction = direction;
        for(int i=0;i<rotation_clockwise;++i)
            new_direction = rotate_direction_clockwise(new_direction);
        return new_direction;
    }
    else if(rotation_clockwise<0)
    {
        int rotation_counterclockwise = -rotation_clockwise;
        rotation_counterclockwise %= 4;
        int new_direction = direction;
        for(int i=0;i<rotation_counterclockwise;++i)
            new_direction = rotate_direction_counterclockwise(new_direction);
        return new_direction;
    }
    else
        return direction;
}

int rotate_direction_clockwise(int direction)
{
    /*
    1 - move up
    2 - move down
    3 - move left
    4 - move right
    */
    if(direction==1)
        return 4;
    if(direction==2)
        return 3;
    if(direction==3)
        return 1;
    if(direction==4)
        return 2;
    assert(false);
}

int rotate_direction_counterclockwise(int direction)
{
    if(direction==4)
        return 1;
    if(direction==3)
        return 2;
    if(direction==1)
        return 3;
    if(direction==2)
        return 4;
    assert(false);
}
