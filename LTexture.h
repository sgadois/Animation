#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Load image at specified path
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

    //Render texture at given point
    void render(SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set position image
    void setPosition(int x, int y);

    //Deallocate texture
    void free();

    //Get image dimensions
    int getWidth();
    int getHeight();

    //Get positions
    int getX();
    int getY();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;

    //Positions
    int x;
    int y;
};

#endif // LTEXTURE_H_INCLUDED
