#include "gather_team.h"

//choosing agents for your team
void gather_team(agents *agenci[AGENTS_AMOUNT], int option)
{
    if(option == 0)
    {
        agenci[0]= new bullerbyn1;
        agenci[1]= new bullerbyn2;
    }
    else if (option == 1)
    {
        agenci[0] = new solo_straight;
        agenci[1] = new solo_leftwall;
    }
}
