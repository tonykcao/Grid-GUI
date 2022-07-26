#include "game.h"

Game* game = nullptr;

int main(int argc, const char* argv[]) {
    game = new Game();

    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW-1, winH-1, false);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    return 0;
};