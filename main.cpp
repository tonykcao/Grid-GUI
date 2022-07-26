#include "GUI.h"

GUI* gui = nullptr;

int main(int argc, const char* argv[]) {
    gui = new GUI();

    gui->init("GameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW-1, winH-1, false);

    while (gui->running()) {
        gui->handleEvents();
        gui->update();
        gui->render();
    }

    gui->clean();
    return 0;
};