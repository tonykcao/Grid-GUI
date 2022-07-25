#pragma once
#include <SDL2/SDL.h>

const int cellSize = 30;
const int gridW = 32;
const int gridH = 24;
const int winW = gridW*cellSize +1;
const int winH = gridH*cellSize +1;

SDL_Color background = {20, 20, 20, 255}; // Almost black
SDL_Color lineColor = {50, 50, 50, 255}; // Dark grey
SDL_Color ghostCursorColor = {50, 50, 50, 255};
SDL_Color gridCursorColor = {255, 255, 255, 255}; // White

// for light theme
// SDL_Color background = {235, 235, 235, 255}; // Almost while
// SDL_Color lineColor = {175, 175, 175, 255}; // Light grey
// SDL_Color ghostCursorColor = {175, 175, 175, 255};
// SDL_Color cursorColor = {160, 160, 160, 255}; // grey