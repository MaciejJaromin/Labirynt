#ifndef BULLERBYN_H_INCLUDED
#define BULLERBYN_H_INCLUDED

const int AGENTS_AMOUNT = 2;


// main class for all agents
class agents
{
    private:
    //Data you can use to remember sth
    int  data_int[5];
    char data_char[3][20];

    public:
    agents(){};

    virtual char** move(int items[3][3],int mates[3][3],int reading[3][3][20]){};

    //setting agents picture - don't work now
    char image[10];
};

// This agents are stupid!

// agents 1 and 2 - the group members

class bullerbyn1 : public agents
{
    public:
    bullerbyn1(){};

    //function making decisions - what to do
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};

class bullerbyn2 : public agents
{
    public:
    bullerbyn2(){};
    char** move(int items[3][3],int mates[3][3],int reading[3][3][20]);
};


//first type of agent - moving down
char** bullerbyn1::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);

    /* decision[0] - what action will agent take
    1 - move up
    2 - move down
    3 - move left
    4 - move right

    0 - writing if(decision[1]!="") and nothing otherwise
    */

    //setting "stupid" decision
    decision[0]="2";
    decision[1]="juhu1";

    //and returning it
    return decision;
}

//first type of agent - moving right
char** bullerbyn2::move(int items[3][3],int mates[3][3],int reading[3][3][20])
{
    char** decision = (char**) malloc(sizeof(char)*21);
    decision[0]="4";
    decision[1]="juhu2";
    return decision;
}


//choosing agents for your team
void gather_team(agents *agenci[AGENTS_AMOUNT], int option)
{
    if(option == 0)
    {
        agenci[0]= new bullerbyn1;
        agenci[1]= new bullerbyn2;
    }
}

#endif // BULLERBYN_H_INCLUDED
