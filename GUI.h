#pragma once
#include <SDL2/SDL.h>
#include <iostream> // debugging
#include "board.cpp"
#include "constants.h"

class GUI {
    public:
        GUI();
        ~GUI();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void renderRect(SDL_Rect rect, SDL_Color);
        void render();
        void clean();

        bool running() {return isRunning;}

    private:
        SDL_bool mouseHover = SDL_FALSE;
        bool active = false; // only render when update occurs

        int count;
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;


        SDL_Rect cursorStart = {
            .x = (gridW - 1) / 2 * cellSize,
            .y = (gridH - 1) / 2 * cellSize,
            .w = cellSize,
            .h = cellSize,
        };
        SDL_Rect cursorTarget = {cursorStart.x+cellSize, cursorStart.y, cellSize, cellSize};
        SDL_Rect cursorGhost = {cursorStart.x, cursorStart.y, cellSize, cellSize};
        SDL_Rect* activeCursor = &cursorGhost;
        Board* board= new Board(gridH, gridW, (gridH - 1) / 2, (gridW - 1) / 2, gridH/2, gridW/2);
};