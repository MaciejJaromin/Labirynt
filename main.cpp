//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include <utility>
#include "main.h"
#include "bullerbyn.h"
#include "agents_maciej.h"
#include "agents_piotr.h"
#include "gather_team.h"

using namespace std;

int main( int argc, char* args[] )
{
    //storing "floor writing"
    char writings[LEVEL_W][LEVEL_H][40];

    agents *agenci[AGENTS_AMOUNT];

    //placements agents on map
    Dot dots[AGENTS_AMOUNT];

    //surroundings

    int items[3][3];
    int mates[AGENTS_AMOUNT];

    /* 1 2 3
       4 5 6
       7 8 9
       0-not near to you
       */
    char reading[3][3][40];

    //which agent moves now?
    int tura=0;

    gather_team(agenci, 2);

    pair<int, char*> decision;


    //Quit flag
    bool quit = false;

    //The dot
    Dot myDot;

    //The tiles that will be used
    Tile *tiles[ TOTAL_TILES ];

    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Clip the tile sheet
    clip_tiles();

    //Set the tiles
    if( set_tiles( tiles ) == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            myDot.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        if(tura<AGENTS_AMOUNT)
        {

            //cutting whole map to agent 3x3 surronding
            items[0][0] = tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile-2 ]->get_type();
            items[0][1] = tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile-1 ]->get_type();
            items[0][2] = tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile ]->get_type();

            items[1][0] = tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-2 ]->get_type();
            items[1][1] = tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->get_type();
            items[1][2] = tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile ]->get_type();

            items[2][0] = tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile-2 ]->get_type();
            items[2][1] = tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile-1 ]->get_type();
            items[2][2] = tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile ]->get_type();

            for(int i=0; i<3; ++i)
            {
                for(int i2=0; i<3; ++i)
                {
                    if(items[i][i2]==10)
                        items[i][i2]==0;
                }
            }

            //cutting writings from whole map to agent 3x3 surronding

            *reading[0][0] = *writings[dots[tura].yTile-2][dots[tura].xTile-2];
            *reading[0][1] = *writings[dots[tura].yTile-2][dots[tura].xTile-1];
            *reading[0][2] = *writings[dots[tura].yTile-2][dots[tura].xTile];

            *reading[1][0] = *writings[dots[tura].yTile-1][dots[tura].xTile-2];
            *reading[1][1] = *writings[dots[tura].yTile-1][dots[tura].xTile-1];
            *reading[1][2] = *writings[dots[tura].yTile-1][dots[tura].xTile];

            *reading[2][0] = *writings[dots[tura].yTile][dots[tura].xTile-2];
            *reading[2][1] = *writings[dots[tura].yTile][dots[tura].xTile-1];
            *reading[2][2] = *writings[dots[tura].yTile][dots[tura].xTile];

            //geting mates
            int h1,h2;
            for(int i=0; i<AGENTS_AMOUNT; ++i)
            {
                h1 = dots[i].yTile-dots[tura].yTile;
                h2 = dots[i].xTile-dots[tura].xTile;
                    if(i!=tura &&  abs(h1) < 2 &&  abs(h2) < 2)
                    {
                        mates[i]= (h1+1)*3 + h2+2;
                    }else
                    {
                        mates[i]= 0;
                    }
            }



            decision = agenci[tura]->move(items,mates,reading);
            dots[tura].handle_movement(decision.first, items);

            //if writing
            if(decision.first==0)
            {
                *writings[dots[tura].yTile-1][dots[tura].xTile-1]= *decision.second;
            }

            int help=tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->get_type();

            if (decision.first>0 && (help==0 || help==2))
                decision.first=2;
            if (decision.first==0 && decision.second == "")
                decision.first=1;

            tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->change_type(decision.first);




        }
        ++tura;

        if(tura==20)
            tura=0;

        for(int i=0; i<AGENTS_AMOUNT;++i)
        {
            dots[i].move(tiles);
        }


        //Move the dot
        myDot.move( tiles );

        //Set the camera
        myDot.set_camera();

        //Show the tiles
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            tiles[ t ]->show();
        }

        //Show the dot on the screen
        myDot.show();
        for(int i=0; i<AGENTS_AMOUNT;++i)
        {
            dots[i].show();
        }


        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    //Clean up
    clean_up( tiles );

    return 0;
}
