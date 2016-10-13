#include "LTexture.h"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    x = 0;
    y = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    //Get rid of preexisting texture
    free();

    //Final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface loaded
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::free()
{
    //Free texture if it exist
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip)
{
    //Get x & y
    int w, h;
    SDL_GetRendererOutputSize(gRenderer, &w, &h);

    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
        renderQuad.x = (w - clip->w) / 2 + x;
        renderQuad.y = (h - clip->h) / 2 + y;
    }

    //SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, 0, NULL, flip);
}

void LTexture::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture:: getHeight()
{
    return mHeight;
}

int LTexture::getX()
{
    return x;
}

int LTexture::getY()
{
    return y;
}
