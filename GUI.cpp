#include "GUI.h"

GUI::GUI() {
}

GUI::~GUI() {
}

void GUI::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
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

void GUI::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                // case SDLK_w:
                // case SDLK_UP:
                //     cursorStart.y -= cellSize;
                //     break;
                // case SDLK_s:
                // case SDLK_DOWN:
                //     cursorStart.y += cellSize;
                //     break;
                // case SDLK_a:
                // case SDLK_LEFT:
                //     cursorStart.x -= cellSize;
                //     break;
                // case SDLK_d:
                // case SDLK_RIGHT:
                //     cursorStart.x += cellSize;
                //     break;
                case SDLK_c:
                    board->clear();
                    break;
            }
            active = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION: {
            int x = event.motion.x / cellSize;
            int y = event.motion.y / cellSize;
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    board->wallOn(y, x);
                    break;
                case SDL_BUTTON_MIDDLE:
                    board->setStart(y,x);
                    break;
                case SDL_BUTTON_RIGHT:
                    board->setEnd(y,x);
                    break;
                default:
                    cursorGhost.x = x * cellSize;
                    cursorGhost.y = y * cellSize;
                    break;
            }
            active = true;
            break;
        }
        case SDL_MOUSEBUTTONUP:
            active = true;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouseHover)
                mouseHover = SDL_TRUE;
            else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouseHover)
                mouseHover = SDL_FALSE;
            active = true;
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void GUI::update() {
    // count++;
    cursorStart.x = board->getStartCol() * cellSize;
    cursorStart.y = board->getStartRow() * cellSize;
    cursorTarget.x = board->getEndCol() * cellSize;
    cursorTarget.y = board->getEndRow() * cellSize;
}

void GUI::renderRect(SDL_Rect rect, SDL_Color color) {
    // Draw grid cursor.
    SDL_SetRenderDrawColor(renderer, color.r,
                            color.g, color.b,
                            color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void GUI::render() {
    if (active) {
        SDL_SetRenderDrawColor(renderer, background.r, background.g,background.b, background.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        //draw walls
        for (int row = 0; row < gridW; row++) {
                for (int col = 0; col < gridH; col++) {
                    if (board->isWall(row, col)) {
                        SDL_Rect wall = {col*cellSize, row*cellSize, cellSize, cellSize};
                        renderRect(wall, wallColor);
                    }
                }
            }
        // Draw grid cursors.
        renderRect(cursorStart, startCursorColor);
        renderRect(cursorTarget, targetCursorColor);
        if (mouseHover) {
            renderRect(cursorGhost, ghostCursorColor);
        }


        //draw gridlines
        SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g,
                                lineColor.b, lineColor.a);

        for (int x = 0; x < 1 + gridW * cellSize; x += cellSize) {
            SDL_RenderDrawLine(renderer, x, 0, x, winH);
        }

        for (int y = 0; y < 1 + gridH * cellSize; y += cellSize) {
            SDL_RenderDrawLine(renderer, 0, y, winW, y);
        }


        // present
        SDL_RenderPresent(renderer);
        active = false;
    }
}

void GUI::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete board;
    SDL_Quit();
    std::cout << "GUI cleaned!\n";
}
