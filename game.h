#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "constants.h"

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void clean();

        bool running() {return isRunning;};

    private:
        SDL_bool mouseActive = SDL_FALSE;
        SDL_bool mouseHover = SDL_FALSE;

        int count;
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect cursorGrid = {
            .x = (gridW - 1) / 2 * cellSize,
            .y = (gridH - 1) / 2 * cellSize,
            .w = cellSize,
            .h = cellSize,
        };

        SDL_Rect cursorGhost = {cursorGrid.x, cursorGrid.y, cellSize, cellSize};
};