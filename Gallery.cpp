#include<iostream>
#include <SDL_image.h>

#include "Gallery.h"
#include "SDL_utils.h"

using namespace std;

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
}

SDL_Texture* Gallery::loadTexture(string path )
{
    SDL_Texture* newTexture = NULL;
          SDL_Surface* loadedSurface = IMG_Load(path.c_str());

          if( loadedSurface == nullptr)
          {

            cout<< " Unable to load image " << path << " SDL_image Error: "
                    <<  IMG_GetError() << endl;

         } else {
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == nullptr )
                cout<< " Unable to create texture from " << path <<  " SDL Error: "
                        << SDL_GetError() << endl;
           SDL_FreeSurface( loadedSurface );

          }
          return newTexture;
}

void Gallery::loadGamePictures()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);



}

int SDL_main(int argc, char* argv[]) {
    // Your code here
    return 0;
}
