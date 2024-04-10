#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include<Windows.h>
#include <SDL_render.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle);
void logSDLError(const char* msg, const char* error);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

#endif
