#include "game.h"

Game::Game() {
}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized!\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer , background.r, background.g, background.b, background.a);
            std::cout << "Renderer created!\n";
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
}


void Game::handleEvents() {
    SDL_Event event;
    SDL_bool mouseActive = SDL_FALSE;
    SDL_bool mouseHover = SDL_FALSE;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                cursorGrid.y -= cellSize;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                cursorGrid.y += cellSize;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                cursorGrid.x -= cellSize;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                cursorGrid.x += cellSize;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            cursorGrid.x = (event.motion.x / cellSize) * cellSize;
            cursorGrid.y = (event.motion.y / cellSize) * cellSize;
            break;
        case SDL_MOUSEMOTION:
            cursorGhost.x = (event.motion.x / cellSize) * cellSize;
            cursorGhost.y = (event.motion.y / cellSize) * cellSize;

            if (!mouseActive)
                mouseActive = SDL_TRUE;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouseHover)
                mouseHover = SDL_TRUE;
            else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouseHover)
                mouseHover = SDL_FALSE;
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    SDL_RenderClear(renderer);
    //draw gridlines
    SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g,
                               lineColor.b, lineColor.a);

    for (int x = 0; x < 1 + gridW * cellSize; x += cellSize) {
        SDL_RenderDrawLine(renderer, x, 0, x, winH);
    }

    for (int y = 0; y < 1 + gridH * cellSize; y += cellSize) {
        SDL_RenderDrawLine(renderer, 0, y, winW, y);
    }

    // Draw grid ghost cursor.
    if (mouseActive && mouseHover) {
        SDL_SetRenderDrawColor(renderer, ghostCursorColor.r,
                                ghostCursorColor.g,
                                ghostCursorColor.b,
                                ghostCursorColor.a);
        SDL_RenderFillRect(renderer, &cursorGhost);
    }

    // Draw grid cursor.
    SDL_SetRenderDrawColor(renderer, gridCursorColor.r,
                            gridCursorColor.g, gridCursorColor.b,
                            gridCursorColor.a);
    SDL_RenderFillRect(renderer, &cursorGrid);

    SDL_RenderPresent(renderer);
}

void Game::update() {
    count++;
    // std::cout << count << "\n";
}

void Game::render() {
    SDL_RenderClear(renderer);
    //render things
    SDL_RenderPresent(renderer);


}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}
