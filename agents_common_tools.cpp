#include "agents_common_tools.h"
#include <cassert>
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
