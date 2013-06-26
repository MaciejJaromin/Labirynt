#include "gather_team.h"

//choosing agents for your team
void gather_team(agents *agenci[AGENTS_AMOUNT], int option)
{
    if(option == 0)
    {

        agenci[0]= new bullerbyn1(0);
        agenci[1]= new bullerbyn2(1);
    }
    else if (option == 1)
    {
        agenci[0] = new writer(0);//straight;
        agenci[1] = new writer(1);
    }
    else if (option == 2)
    {
        Random_choice* random = new Random_choice();
        agenci[0] = new blind_walker(*random);
        agenci[1] = new blind_walker(*random);
    }
    else if (option == 3)
    {
        Random_choice* random = new Random_choice();
        agenci[0] = new sealing_walker(0,*random);
        agenci[1] = new sealing_walker(1,*random);
    }
    else if (option == 4)
    {
        Leftwall_choice* leftwall = new Leftwall_choice();
        Rightwall_choice* rightwall = new Rightwall_choice();

        agenci[0] = new sealing_walker(0,*leftwall);
        agenci[1] = new sealing_walker(1,*rightwall);
    }
    else if (option == 5)
    {
        Leftwall_choice* leftwall = new Leftwall_choice();
        Explorer*   leftwall_explorer = new Explorer(*leftwall);
        Rightwall_choice* rightwall = new Rightwall_choice();

        agenci[0] = new sealing_walker(0,*leftwall_explorer);
        agenci[1] = new sealing_walker(1,*rightwall);
    }
}
