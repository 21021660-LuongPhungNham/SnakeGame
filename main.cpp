#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include "SDL_Utils.h"
#include "Game.h"
#include "UI.h"
#include <SDL_mixer.h>

#include <cmath>
#include <chrono>

using namespace std;

const double STEP_DELAY = 0.2;
#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;

void start()
{
    cout << "Press any key to start game" << endl;
    waitUntilKeyPressed();
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Khởi tạo SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    // Tải âm thanh
    Mix_Chunk* eatSound = Mix_LoadWAV("eat_sound.wav");
    if (eatSound == NULL) {
        cout << "Failed to load eat sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    Mix_Chunk* gameOverSound = Mix_LoadWAV("gameover_sound.wav");
    if (gameOverSound == NULL) {
        cout << "Failed to load game over sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    srand(time(0));
    UI ui(BOARD_WIDTH, BOARD_HEIGHT);
    Game game(BOARD_WIDTH, BOARD_HEIGHT);

    start();

    auto start = CLOCK_NOW();
    ui.renderGamePlay(game);
    SDL_Event e;
    while (game.isGameRunning()) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP: game.processUserInput(UP); break;
                    case SDLK_DOWN: game.processUserInput(DOWN); break;
                    case SDLK_LEFT: game.processUserInput(LEFT); break;
                    case SDLK_RIGHT: game.processUserInput(RIGHT); break;
                }
            }
        }

        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY) {
            game.nextStep();
            ui.renderGamePlay(game);
            start = end;
        }
        SDL_Delay(1);
    }

    // am thanh tro choi ket thuc
    Mix_PlayChannel(-1, gameOverSound, 0);
    ui.renderGameOver();
    waitUntilKeyPressed();

    Mix_FreeChunk(eatSound);
    Mix_FreeChunk(gameOverSound);

    Mix_CloseAudio();

    SDL_Quit();

    return 0;
}
