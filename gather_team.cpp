#include "gather_team.h"

//choosing agents for your team
void gather_team(agents *agenci[AGENTS_AMOUNT], int option)
{
    if(option == 0)
    {

        agenci[0]= new bullerbyn1(0);
        agenci[1]= new bullerbyn2(1);
    }
/*    else if (option == 1)
    {
        agenci[0] = new solo_leftwall;//straight;
        agenci[1] = new solo_leftwall;
    }
    else if (option == 2)
    {
        agenci[0] = new random_walker;
        agenci[1] = new random_walker;

    }
    */
}