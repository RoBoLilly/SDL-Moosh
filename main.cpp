//
//  main.cpp
//  Moosh Vr.3.0
//
//  Created by Lilly Fiorino on 5/25/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "map.hpp"
#include "player.hpp"
#include "enemy.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 700;

int meta = NULL;
bool rainbowMode = false;

bool init(); //Starts up SDL and creates window
bool loadMedia();
void close();
//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

void printGrid(player player, map map);
void askCommand(player player, map map);
int checkAroundFor(player player, map map, int i);
void rainbowColor(int speed);

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "Moosh Vr.3.0 SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Nothing to load
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

void printGrid(player player, map map)
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );
    SDL_Rect outlineRect = { 15, 75, 610, 610 };
    if(!rainbowMode)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );

    }else{
        rainbowColor(1);
    }
    SDL_RenderFillRect( gRenderer, &outlineRect );

    for (int a = 1; a < 11; a++)
    {
        for (int b = 1; b < 11; b++)
        {
            outlineRect = { b * 60 - 40, a * 60 + 20, 58, 58 };
            if(map.gridValue(a, b) ==-1){SDL_SetRenderDrawColor( gRenderer, 0x8A, 0x2B, 0xE2, 0xFF );} // NULL
            if(map.gridValue(a, b) == 0){SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );} // Wall - Red
            if(map.gridValue(a, b) == 1){SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );} // Ground - Green
            if(map.gridValue(a, b) == 2){SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );} // Key - Yellow
            if(map.gridValue(a, b) == 3){SDL_SetRenderDrawColor( gRenderer, 0xfe, 0x87, 0x00, 0xFF );} // Door_Locked - Red
            if(map.gridValue(a, b) == 4){SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );} // Door_Unlocked - Green
            if(map.gridValue(a, b) == 5){SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );} // End_Point - Cyan
            if(map.gridValue(a, b) == 6){SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFA, 0x7F, 0xFF );} // Reverse - Green
            if(map.gridValue(a, b) == 7){SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );} // 3_Key_Door - Blue
            if(map.gridValue(a, b) == 8){SDL_SetRenderDrawColor( gRenderer, 0xB2, 0x22, 0x22, 0xFF );} // Enemy - Off Red
            //if(rainbowMode){rainbowColor(12);} // FOR THE PARTY!
            SDL_RenderFillRect( gRenderer, &outlineRect );
            if (a == player.getLocation(0) && b == player.getLocation(1))
            {
                outlineRect = { b * 60 - 35, a * 60 + 25, 48, 48 };
                SDL_SetRenderDrawColor( gRenderer, 0xce, 0x11, 0x76, 0xFF );
                SDL_RenderFillRect( gRenderer, &outlineRect );
            }
        }
    }
    for(int a = 0; a < player.getInventorySize();a++)
    {
        SDL_Rect outlineRect = { a*50 + 10, 10, 40 , 60 };
        SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &outlineRect );
    }
    //Update screen
    SDL_RenderPresent( gRenderer );
}

int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            boss boss1;
            map map1;
            player player1;
            meta = -1;
            
            map1.setLoadedGrid(1, 3); // Loads first grid
            player1.setLocation(0, 7); //Y Places player1 on grid
            player1.setLocation(1, 4); //X
            boss1.setMapLocation(0, 1);
            boss1.setMapLocation(1, 3);
            boss1.setLocation(0, 4);
            boss1.setLocation(1, 4);
            boss1.setAIstate(0);
            boss1.setTimeInterval(100);
            player1.addKey();
            player1.addKey();
            player1.addKey();
            player1.addKey();
            
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_UP:
                                player1.moveForward(map1);
                                break;
                            case SDLK_DOWN:
                                player1.moveBackward(map1);
                                break;
                            case SDLK_LEFT:
                                player1.moveLeft(map1);
                                break;
                            case SDLK_RIGHT:
                                player1.moveRight(map1);
                                break;
                            case SDLK_e:
                                if(player1.gridValueUnderneath(map1) == 2)
                                {
                                    player1.pickUpKey(map1);
                                }else{
                                    player1.useKey(map1);
                                }
                                break;
                            case SDLK_F9:
                                if(!rainbowMode)
                                {
                                    rainbowMode = true;
                                }else{
                                    rainbowMode = false;
                                }
                                break;
                        }
                        
                    }
                }
                // Boss Code
                if(boss1.getMapLocation(0) == map1.getLoadedGrid(0)&& boss1.getMapLocation(1) == map1.getLoadedGrid(1))
                {
                    if(meta > boss1.getTimeInterval() || meta == -1)
                    {
                        for(int a=1;a<11;a++)
                        {
                            for(int b=1;b<11;b++)
                            {
                                if(map1.gridValue(a, b) == 8)
                                {
                                    map1.setGridValueNoSave(a, b, 1);
                                }
                                if(boss1.getLocation(0) == a && boss1.getLocation(1) == b)
                                {
                                    map1.setGridValueNoSave(a, b, 8);
                                }
                            }
                        }
                        meta = 0;
                    }
                    meta += 1;
                }
                if(boss1.getAIstate() == 0){
                    if (map1.isPermeable(boss1.getLocation(0), boss1.getLocation(1) + 1)){
                        boss1.moveRight(map1);
                    }
                    if(boss1.getLocation(1) > 6){
                        boss1.setAIstate(1);
                    }
                }else if(boss1.getAIstate() == 1){
                    if (map1.isPermeable(boss1.getLocation(0) + 1, boss1.getLocation(1))){
                        boss1.moveBackward(map1);
                    }
                    if(boss1.getLocation(0) > 6){
                        boss1.setAIstate(2);
                    }
                }else if(boss1.getAIstate() == 2){
                    if (map1.isPermeable(boss1.getLocation(0), boss1.getLocation(1) - 1)){
                        boss1.moveLeft(map1);
                    }
                    if(boss1.getLocation(1) < 5){
                        boss1.setAIstate(3);
                    }
                }else if(boss1.getAIstate() == 3){
                    if (map1.isPermeable(boss1.getLocation(0) - 1, boss1.getLocation(1))){
                        boss1.moveForward(map1);
                    }
                    if(boss1.getLocation(0) < 5){
                        boss1.setAIstate(0);
                    }
                }
                // End of Boss Code
                
                if(map1.gridValue(player1.getLocation(0), player1.getLocation(1))==6) // checks if controls should be inverted
                {
                    player1.setInvertControls(1);
                }
                else{
                    player1.setInvertControls(0);
                }
                
                printGrid(player1, map1); // prints grid
                
                // If player is over the edge of the grid
                if(map1.gridValue(player1.getLocation(0), player1.getLocation(1))== -1)
                {
                    // Teleport player to oposing side and load grid from the same side the player telported from
                    if(player1.getLocation(0) == 0){
                        map1.loadForwardGrid();
                        player1.setLocation(0, 10);
                    }
                    if(player1.getLocation(0) == 11){
                        map1.loadBackwardGrid();
                        player1.setLocation(0, 1);
                    }
                    if(player1.getLocation(1) == 0){
                        map1.loadLeftGrid();
                        player1.setLocation(1, 10);
                    }
                    if(player1.getLocation(1) == 11){
                        map1.loadRightGrid();
                        player1.setLocation(1, 1);
                    }
                }
                if(map1.gridValue(player1.getLocation(0), player1.getLocation(1)) == 5)
                {
                    for(int a = 610; a > 1; a -= 5)
                    {
                        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //SDL_Rect Rect = { 15, 75, 610, 610  };
                        SDL_Rect Rect = { 15 + ((a*-1)/2)+305, 75 + ((a*-1)/2)+305, a, a };
                        rainbowColor(10);
                        SDL_RenderFillRect( gRenderer, &Rect );
                        SDL_RenderPresent( gRenderer );
                    }
                    quit = true;
                }
            }
        }
        close();
        return 0;
    }
}

int rain = 0;
int red = 255;
int green = 0;
int blue = 0;
void rainbowColor(int speed)
{
    switch (rain) {
        case 0:
            green += speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(green >= 255){rain = 1;}
            break;
        case 1:
            red -= speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(red <= 0){rain = 2;}
            break;
        case 2:
            blue += speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(blue >= 255){rain = 3;}
            break;
        case 3:
            green -= speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(green <= 0){rain = 4;}
            break;
        case 4:
            red += speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(red >= 255){rain = 5;}
            break;
        case 5:
            blue -= speed;
            SDL_SetRenderDrawColor( gRenderer, red, green, blue, 255 );
            if(blue <= 0){rain = 0;}
            break;
    }
}

