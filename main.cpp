//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WALKING_ANIMATION_FRAMES = 4;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Scene sprites
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if(!init()) {
        printf( "Failed to initialize!\n" );
    } else {
        //Load media
        if(!loadMedia()) {
            printf( "Failed to load media!\n" );
        } else {

            bool quit = false;
            SDL_Event e;
            int frame = 4;
            SDL_Rect* currentClip = &gSpriteClips[0];
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            while(!quit) {
                //Handle events on queue
                while(SDL_PollEvent( &e ) != 0)
                {
                    //User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT))
                    {
                        currentClip = &gSpriteClips[frame/4];
                        ++frame;
                        //Cycle frame animation
                        if(frame/4 >= WALKING_ANIMATION_FRAMES)
                        {
                            frame = 0;
                        }

                        switch(e.key.keysym.sym)
                        {
                        case SDLK_LEFT:
                            flipType = SDL_FLIP_NONE;
                            if((frame % 4) == 1)
                            {
                                gSpriteSheetTexture.setPosition(gSpriteSheetTexture.getX() - 10, gSpriteSheetTexture.getY());
                            }
                            break;

                        case SDLK_RIGHT:
                            flipType = SDL_FLIP_HORIZONTAL;
                            if((frame % 4) == 1)
                            {
                                gSpriteSheetTexture.setPosition(gSpriteSheetTexture.getX() + 10, gSpriteSheetTexture.getY());
                            }
                            break;
                        }
                    }
                    else if(e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT))
                    {
                        frame = frame + (4 - frame%4);
                        //Cycle frame animation
                        if(frame/4 >= WALKING_ANIMATION_FRAMES)
                        {
                            frame = 0;
                        }
                    }
                }
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear( gRenderer );

                //Render current frame
                gSpriteSheetTexture.render(gRenderer, currentClip, flipType);

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

	return 0;
}

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL){
                printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                 //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    if(!gSpriteSheetTexture.loadFromFile("foo.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 64;
        gSpriteClips[0].h = 205;

        gSpriteClips[1].x = 64;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 64;
        gSpriteClips[1].h = 205;

        gSpriteClips[2].x = 128;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 64;
        gSpriteClips[2].h = 205;

        gSpriteClips[3].x = 192;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 64;
        gSpriteClips[3].h = 205;
    }


    return success;
}

void close() {
    //Free loaded image
    gSpriteSheetTexture.free();

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
