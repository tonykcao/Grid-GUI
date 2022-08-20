#pragma once
#include <SDL2/SDL.h>

const int cellSize = 30;
const int gridW = 32;
const int gridH = 24;
const int winW = gridW*cellSize +1;
const int winH = gridH*cellSize +1;

const SDL_Color background = {20, 20, 20, 255}; // Almost black
const SDL_Color lineColor = {50, 50, 50, 255}; // Dark grey
const SDL_Color ghostCursorColor = {50, 50, 50, 255}; // light grey
const SDL_Color startCursorColor = {255, 255, 255, 255}; // White
const SDL_Color targetCursorColor = {0, 95, 105, 255}; // Dark cyan
const SDL_Color wallColor = {200, 95, 105, 255}; // Dark red