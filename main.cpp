//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include "main.h"
#include "bullerbyn.h"
#include "agents_maciej.h"
#include "agents_piotr.h"
#include "gather_team.h"

using namespace std;

int main( int argc, char* args[] )
{
    //storing "floor writing"
    char *writings[LEVEL_W][LEVEL_H][20];

    agents *agenci[AGENTS_AMOUNT];

    //placements agents on map
    Dot dots[AGENTS_AMOUNT];

    //surroundings

    int items[3][3];
    int mates[3][3];
    int reading[3][3][20];

    //which agent moves now?
    int tura=0;

    gather_team(agenci, 2);

    char** decision;


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

            items[0][0] = (*tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile-2 ]).get_type();
            items[0][1] = (*tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile-1 ]).get_type();
            items[0][2] = (*tiles[ (dots[tura].yTile-2) * LEVEL_W + dots[tura].xTile ]).get_type();

            items[1][0] = (*tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-2 ]).get_type();
            items[1][1] = (*tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]).get_type();
            items[1][2] = (*tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile ]).get_type();

            items[2][0] = (*tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile-2 ]).get_type();
            items[2][1] = (*tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile-1 ]).get_type();
            items[2][2] = (*tiles[ (dots[tura].yTile) * LEVEL_W + dots[tura].xTile ]).get_type();

            decision = (*agenci[tura]).move(items,mates,reading);
            dots[tura].handle_movement(decision[0][0], tiles);

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
