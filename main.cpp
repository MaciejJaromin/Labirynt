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
#include <cassert>

using namespace std;

void play_game(int team, bool fast, int steps_limit, ofstream& log, int logging_interval_in_steps=5)
{
    int steps = 0;

    //storing "floor writing"
    std::string writings[LEVEL_H][LEVEL_W];

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
    std::string reading[3][3];

    //which agent moves now?
    int tura=0;

    gather_team(agenci, team);

    pair<int, std::string> decision;


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
        assert(false);
    }

    //Load the files
    if( load_files() == false )
    {
        assert(false);
    }

    //Clip the tile sheet
    clip_tiles();

    //Set the tiles
    if( set_tiles( tiles ) == false )
    {
        assert(false);
    }

    int total_treasures = 0;
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        if(tiles[t]->get_type()==TILE_TREASURE)
            ++total_treasures;
    }

    // Piotrek graphics
    class Piotrek_writings
    {
        SDL_Surface* arrows_image;
    public:
        Piotrek_writings()
        {
            arrows_image = load_image( "arrows.png" );
        }
        void draw(std::string (&writings)[LEVEL_H][LEVEL_W])
        {
            SDL_Rect right_arrow = { 0, 0,40,40};
            SDL_Rect down_arrow  = {40, 0,40,40};
            SDL_Rect left_arrow  = { 0,40,40,40};
            SDL_Rect up_arrow    = {40,40,40,40};

            for(int x=0;x<LEVEL_W;++x)
                for(int y=0;y<LEVEL_H;++y)
                {
                    if(writings[y][x]!=std::string(""))
                    {
                        if(writings[y][x].length()>=5)
                        {
                            int current_x = (x+1)*TILE_HEIGHT-camera.y;
                            int current_y = (y-1)*TILE_WIDTH-camera.x;
                            if(writings[y][x][1]=='1')
                                apply_surface( current_x, current_y, arrows_image, screen, &up_arrow);
                            if(writings[y][x][2]=='1')
                                apply_surface( current_x, current_y, arrows_image, screen, &down_arrow);
                            if(writings[y][x][3]=='1')
                                apply_surface( current_x, current_y, arrows_image, screen, &left_arrow);
                            if(writings[y][x][4]=='1')
                                apply_surface( current_x, current_y, arrows_image, screen, &right_arrow);
                        }
                    }
                }
        }
    } piotrek_writings;

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

            //cutting writings from whole map to agent 3x3 surronding

            for(int i=0;i<3;++i)
                for(int j=0;j<3;++j)
                    reading[i][j] = writings[dots[tura].yTile-2+i][dots[tura].xTile-2+j];

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
                writings[dots[tura].yTile-1][dots[tura].xTile-1] = decision.second;
            }

            int current_tile_type=tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->get_type();

            if (decision.first>0)
            {
                if(current_tile_type==TILE_UNVISITED || current_tile_type==TILE_TREASURE)
                    tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->set_type(TILE_VISITED);
            }
            else if (decision.first==0 && decision.second == "")
            {
                tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->set_type(TILE_VISITED);
            }
            else if (decision.first==0 && decision.second != "")
            {
                tiles[ (dots[tura].yTile-1) * LEVEL_W + dots[tura].xTile-1 ]->set_type(TILE_WRITINGS);
            }
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
        // Show additional graphical information for Piotrek's agents
        if(team==3 || team==4 || team==5)
            piotrek_writings.draw(writings);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            assert(false);
        }

        //Cap the frame rate
        if(!fast)
        {
            if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            {
                SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
            }
        }

        if(tura==0)
        {
            ++steps;
            if(steps>=steps_limit)
                break;
            // Logging
            if(tura%logging_interval_in_steps==0)
            {
                int visited_tiles = 0;
                int visitable_tiles = 0;
                int treasures_left = 0;
                for(int i=0;i<TOTAL_TILES;++i)
                {
                    if(tiles[i]->get_type()==TILE_VISITED || tiles[i]->get_type()==TILE_WRITINGS)
                    {
                        ++visited_tiles;
                        ++visitable_tiles;
                    }
                    else if(tiles[i]->get_type()==TILE_UNVISITED || tiles[i]->get_type()==TILE_TREASURE)
                        ++visitable_tiles;

                    if(tiles[i]->get_type()==TILE_TREASURE)
                        ++treasures_left;
                }
                double percent_visited = double(visited_tiles)/visitable_tiles;
                log << team << ";" << visited_tiles << ";" << visitable_tiles << ";" << percent_visited << ";"
                    << (total_treasures-treasures_left) << ";" << total_treasures << endl;
            }
        }
    }

    //Clean up
    clean_up( tiles );

}

int main( int argc, char* args[] )
{
     //ostream& log = cout;
    ofstream log("log.txt",ios::out | ios::app);
    play_game(3,true,100000,log);
    //for(int i=0;i<4;++i)
        //play_game(i,true,300,log);
    return 0;
}
