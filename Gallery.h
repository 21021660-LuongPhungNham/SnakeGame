#ifndef GALLERY_H
#define GALLERY_H

#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

enum PictureID {
    PIC_FROG = 0, PIC_SNAKE_VERTICAL,
    PIC_SNAKE_HORIZONTAL, PIC_SNAKE_HEAD, PIC_COUNT,PIC_BACKGROUND
};

class Gallery
{
    public:
    SDL_Texture* pictures[PIC_COUNT];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(string path);

    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif
