#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int ZOOM=2;
//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dot dimensions
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

//Tile constants
const int TILE_WIDTH = 80/ZOOM;
const int TILE_HEIGHT = 80/ZOOM;
const int TOTAL_TILES = 192;
const int TILE_SPRITES = 12;

//The dimensions of the level
const int LEVEL_WIDTH = 1280/ZOOM;
const int LEVEL_HEIGHT = 960/ZOOM;

const int LEVEL_H = LEVEL_HEIGHT/TILE_WIDTH;
const int LEVEL_W = LEVEL_WIDTH/TILE_HEIGHT;


//The different tile sprites
const int TILE_UNVISITED = 0;
const int TILE_VISITED = 1;
const int TILE_TREASURE = 2;
const int TILE_WALL = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_WRITINGS = 10;
const int TILE_TOPLEFT = 11;

//The surfaces
SDL_Surface *dot = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;

//Sprite from the tile sheet
SDL_Rect clips[ TILE_SPRITES ];

//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//The tile
class Tile
{
    private:
    //The attributes of the tile
    SDL_Rect box;

    //The tile type
    int type;

    public:
    //Initializes the variables
    Tile( int x, int y, int tileType );

    //Shows the tile
    void show();

    //Get the tile type
    int get_type();
    void set_type(int new_type);

    //Get the collision box
    SDL_Rect get_box();
};

//The dot
class Dot
{
    private:
    //The dot's collision box
    SDL_Rect box;

    //The velocity of the dot
    int xVel, yVel;


    public:
    //Initializes the variables
    Dot();
    int xTile, yTile;
    //Takes key presses and adjusts the dot's velocity
    void handle_input();

    void handle_movement(char option, int items[3][3]);

    //Moves the dot
    void move( Tile *tiles[] );

    //Shows the dot on the screen
    void show();

    //Sets the camera over the dot
    void set_camera();
};

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Move the Dot", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the dot image
    dot = load_image( "dot-red.png" );

    //If there was a problem in loading the dot
    if( dot == NULL )
    {
        return false;
    }

    //Load the tile sheet
    tileSheet = load_image( "tiles.png" );

    //If there was a problem in loading the tiles
    if( tileSheet == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up( Tile *tiles[] )
{
    //Free the surfaces
    SDL_FreeSurface( dot );
    SDL_FreeSurface( tileSheet );

    //Free the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];
    }

    //Quit SDL
    SDL_Quit();
}

void clip_tiles()
{
    //Clip the sprite sheet
    clips[ TILE_UNVISITED ].x = 0;
    clips[ TILE_UNVISITED ].y = 0;
    clips[ TILE_UNVISITED ].w = TILE_WIDTH;
    clips[ TILE_UNVISITED ].h = TILE_HEIGHT;

    clips[ TILE_VISITED ].x = 0;
    clips[ TILE_VISITED ].y = 40;
    clips[ TILE_VISITED ].w = TILE_WIDTH;
    clips[ TILE_VISITED ].h = TILE_HEIGHT;

    clips[ TILE_TREASURE ].x = 0;
    clips[ TILE_TREASURE ].y = 80;
    clips[ TILE_TREASURE ].w = TILE_WIDTH;
    clips[ TILE_TREASURE ].h = TILE_HEIGHT;

    clips[ TILE_TOPLEFT ].x = 40;
    clips[ TILE_TOPLEFT ].y = 0;
    clips[ TILE_TOPLEFT ].w = TILE_WIDTH;
    clips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

    clips[ TILE_WRITINGS ].x = 40;
    clips[ TILE_WRITINGS ].y = 40;
    clips[ TILE_WRITINGS ].w = TILE_WIDTH;
    clips[ TILE_WRITINGS ].h = TILE_HEIGHT;

    clips[ TILE_BOTTOMLEFT ].x = 40;
    clips[ TILE_BOTTOMLEFT ].y = 80;
    clips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

    clips[ TILE_TOP ].x = 80;
    clips[ TILE_TOP ].y = 0;
    clips[ TILE_TOP ].w = TILE_WIDTH;
    clips[ TILE_TOP ].h = TILE_HEIGHT;

    clips[ TILE_WALL ].x = 80;
    clips[ TILE_WALL ].y = 40;
    clips[ TILE_WALL ].w = TILE_WIDTH;
    clips[ TILE_WALL ].h = TILE_HEIGHT;

    clips[ TILE_BOTTOM ].x = 80;
    clips[ TILE_BOTTOM ].y = 80;
    clips[ TILE_BOTTOM ].w = TILE_WIDTH;
    clips[ TILE_BOTTOM ].h = TILE_HEIGHT;

    clips[ TILE_TOPRIGHT ].x = 120;
    clips[ TILE_TOPRIGHT ].y = 0;
    clips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
    clips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

    clips[ TILE_RIGHT ].x = 120;
    clips[ TILE_RIGHT ].y = 40;
    clips[ TILE_RIGHT ].w = TILE_WIDTH;
    clips[ TILE_RIGHT ].h = TILE_HEIGHT;

    clips[ TILE_BOTTOMRIGHT ].x = 120;
    clips[ TILE_BOTTOMRIGHT ].y = 80;
    clips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
}

bool set_tiles( Tile *tiles[] )
{
    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "basic.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        return false;
    }


    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile will be made
        int tileType = -1;

        //Read tile from map file

        map >> tileType;

        //If the was a problem in reading the map
        if( map.fail() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y, tileType );
        }
        //If we don't recognize the tile type
        else
        {
            //Stop loading map
            map.close();
            return false;
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return true;
}

bool touches_wall( SDL_Rect box, Tile *tiles[] )
{
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( tiles[ t ]->get_type() ==3 )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;
}

void Tile::show()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        //Show the tile
        apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ type ] );
    }
}

int Tile::get_type()
{
    return type;
}
void Tile::set_type(int new_type)
{
    type = new_type;
}

SDL_Rect Tile::get_box()
{
    return box;
}

Dot::Dot()
{
    //Initialize the offsets
    xTile=2;
    yTile=6;
    box.x = (xTile-1)*TILE_WIDTH+(TILE_WIDTH-20)/2;
    box.y = (yTile-1)*TILE_HEIGHT+(TILE_HEIGHT-20)/2;
    box.w = DOT_WIDTH;
    box.h = DOT_HEIGHT;
    xTile=2;
    yTile=6;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Dot::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += DOT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += DOT_WIDTH / 2; break;
            default: break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += DOT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel -= DOT_WIDTH / 2; break;
            default: break;
        }
    }
}
void Dot::handle_movement(char option, int items[3][3])
{
    xVel=0;
    yVel=0;
    switch (option)
    {
            case 1:
            if(items[0][1]!=3)
            {
                yVel = -TILE_WIDTH/20;
                --yTile;
            }
            break;
            case 2:
            if(items[2][1]!=3)
            {
                yVel = TILE_WIDTH/20;
                ++yTile;
            }
            break;
            case 3:
            if(items[1][0]!=3)
            {
                xVel = -TILE_WIDTH/20;
                --xTile;
            }
            break;
            case 4:
            if(items[1][2]!=3)
            {
                xVel = TILE_WIDTH/20;
                ++xTile;
            }
            break;
            default: break;
    }
    if(yTile<2)
    {
        yTile=1;
        yVel=0;
    }

    if(yTile>LEVEL_H-1)
    {
       yTile=LEVEL_H-1;
       yVel=0;
    }

    if(xTile<2)
    {
        xTile=1;
        xVel=0;
    }

    if(xTile>LEVEL_W-1)
    {
        xTile=LEVEL_W-1;
        xVel=0;
    }


}

void Dot::move( Tile *tiles[] )
{
    //Move the dot left or right
    box.x += xVel;

    //If the dot went too far to the left or right or touched a wall
    if( ( box.x < 0 ) || ( box.x + DOT_WIDTH > LEVEL_WIDTH ) || touches_wall( box, tiles ) )
    {
        //move back
        box.x -= xVel;
    }

    //Move the dot up or down
    box.y += yVel;

    //If the dot went too far up or down or touched a wall
    if( ( box.y < 0 ) || ( box.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touches_wall( box, tiles ) )
    {
        //move back
        box.y -= yVel;
    }
}

void Dot::show()
{
    //Show the dot
    apply_surface( box.x - camera.x, box.y - camera.y, dot, screen );
}

void Dot::set_camera()
{
    //Center the camera over the dot
    camera.x = ( box.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( box.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

#endif // MAIN_H_INCLUDED
