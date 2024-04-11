#ifndef UI__H_
#define UI__H_

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_Utils.h"

enum PictureID {
    PIC_FROG = 0, PIC_SNAKE_VERTICAL,
    PIC_SNAKE_HORIZONTAL, PIC_SNAKE_HEAD, PIC_COUNT, PIC_BACKGROUND
};

const int CELL_SIZE = 30;

const SDL_Color BOARD_COLOR = {0, 0, 0};
const SDL_Color LINE_COLOR = {128, 128, 128};


class UI {
public:
    const int SCREEN_WIDTH = 900;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Snake Game";

    const int BOARD_WIDTH;
    const int BOARD_HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* pictures[PIC_COUNT];


    UI( int boardWidth, int boardHeight) :BOARD_WIDTH(boardWidth), BOARD_HEIGHT(boardHeight)
    {
        initSDL(window, renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

        pictures[PIC_FROG] = loadTexture("frog.png", renderer);
        pictures[PIC_SNAKE_VERTICAL] = loadTexture("snake_vertical.png", renderer);
        pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("snake_horizontal.png", renderer);
        pictures[PIC_SNAKE_HEAD] = loadTexture("snake_head.png", renderer);
        pictures[PIC_BACKGROUND] = loadTexture("background.png", renderer);

    }

    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }

    void clearScreen() {
        SDL_RenderClear(renderer);
    }

    void renderGameOver() {
        clearScreen();
        SDL_RenderPresent( renderer );
    }

    void destroy() {
        for (SDL_Texture* texture : pictures)
            SDL_DestroyTexture(texture);
        quitSDL(window, renderer);
    }

    void drawCell(int left, int top, Position pos, SDL_Texture* texture)
    {
        SDL_Rect cell;
        cell.x = left + pos.x * CELL_SIZE + 5;
        cell.y = top + pos.y * CELL_SIZE + 5;
        cell.w = CELL_SIZE-10;
        cell.h = CELL_SIZE-10;
        SDL_RenderCopy(renderer, texture, NULL, &cell);
    }

    void drawBackground() {
    SDL_Texture* background = pictures[PIC_BACKGROUND];
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, background, NULL, &destRect);
}

    void drawFrog(int left, int top, Position pos)
{
    int newWidth = CELL_SIZE * 1.5;
    int newHeight = CELL_SIZE * 1.5;

    // Vị trí mới của frog
    int newX = left + pos.x * CELL_SIZE + 5 - (newWidth - CELL_SIZE) / 2;
    int newY = top + pos.y * CELL_SIZE + 5 - (newHeight - CELL_SIZE) / 2;

    SDL_Rect destinationRect = {newX, newY, newWidth, newHeight};
    SDL_Texture* frogTexture = getImage(PIC_FROG);
    SDL_RenderCopy(renderer, frogTexture, NULL, &destinationRect);
}

void drawSnake(int left, int top, const vector<Position>& pos)
{
    int newWidth = CELL_SIZE;
    int newHeight = CELL_SIZE;

    drawCell(left, top, pos[pos.size()-1], getImage(PIC_SNAKE_HEAD), newWidth, newHeight);

    for (int i = pos.size() - 2; i >= 0; i--) {
        SDL_Texture* texture = getImage(
            pos[i].y == pos[i+1].y ? PIC_SNAKE_HORIZONTAL : PIC_SNAKE_VERTICAL);
        drawCell(left, top, pos[i], texture, newWidth, newHeight);
    }
}

void drawCell(int left, int top, Position pos, SDL_Texture* texture, int width, int height)
{
    int newX = left + pos.x * CELL_SIZE + 5 - (width - CELL_SIZE) / 2;
    int newY = top + pos.y * CELL_SIZE + 5 - (height - CELL_SIZE) / 2;

    SDL_Rect destinationRect = {newX, newY, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}

    void drawVerticalLine(int left, int top, int cells)
    {
        SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
        SDL_RenderDrawLine(renderer, left, top, left, top + cells * CELL_SIZE);
    }

    void drawHorizontalLine(int left, int top, int cells)
    {
        SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
        SDL_RenderDrawLine(renderer, left, top, left + cells * CELL_SIZE, top);
    }

    void renderGamePlay(const Game& game)
    {
        int top = 0, left = 0;
        SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
        SDL_RenderClear(renderer);

        for (int x = 0; x <= BOARD_WIDTH; x++)
            drawVerticalLine(left + x*CELL_SIZE, top, BOARD_HEIGHT);
        for (int y = 0; y <= BOARD_HEIGHT; y++)
            drawHorizontalLine(left, top+y * CELL_SIZE, BOARD_WIDTH);

            drawBackground();

        drawFrog(left, top, game.getFrogPosition());
        drawSnake(left, top, game.getSnakePositions());

        SDL_RenderPresent(renderer);
    }

    void renderGameOver(const Game& game)
    {

    }
};

#endif
