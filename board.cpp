// #include "constants.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <memory>


struct Tile {
    bool hasWall;
    bool hasTrack;
};

class Board {
    public:
        Board(int height, int width,
                int rStart, int cStart,
                int rEnd, int dcEnd) {
            rows = height;
            cols = width;
            startR = rStart;
            startC = cStart;
            endR = rEnd;
            endC = dcEnd;
            arrBoard = new Tile**[rows]{};
            for (int row = 0; row < rows; row++) {
                arrBoard[row] = new Tile*[cols];
                for (int col = 0; col < cols; col++) {
                    arrBoard[row][col] = new Tile();
                    arrBoard[row][col]->hasWall = false;
                    arrBoard[row][col]->hasTrack = false;

                }
            }
        };

        ~Board() {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    delete arrBoard[row][col];
                }
                delete[] arrBoard[row];
            }
            delete[] arrBoard;
        };

        int getStartCol() {return startC;}
        int getStartRow() {return startR;}
        int getEndCol() {return endC;}
        int getEndRow() {return endR;}

        void setStart(int col, int row) {
            startC = col;
            startR = row;
        }
        void setEnd(int col, int row) {
            endC = col;
            endR = row;
        }

        void clear() {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    arrBoard[row][col]->hasWall=false;
                    arrBoard[row][col]->hasTrack=false;

                }
            }
        }

        bool isWall(int x, int y) {return arrBoard[x][y]->hasWall;}
        bool isTrack(int x, int y) {return arrBoard[x][y]->hasTrack;}


        void wallOn(int x, int y) {arrBoard[x][y]->hasWall = true;}
        void trackOn(int x, int y) {arrBoard[x][y]->hasTrack = true;}

        void wallOff(int x, int y) {arrBoard[x][y]->hasWall = false;}
        void trackOff(int x, int y) {arrBoard[x][y]->hasTrack = false;}

        void print() {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    if (row == startR && col == startC) {
                        std::cout<< "S" << " ";
                    } else if (row == endR && col == endC) {
                        std::cout<< "E" << " ";
                    } else {
                        if (arrBoard[row][col]->hasWall) {
                            if (arrBoard[row][col]->hasTrack) {
                                std::cout << "W ";
                            } else {std::cout << "w ";}
                        }
                        else if (arrBoard[row][col]->hasTrack) {
                                std::cout << "- ";
                            } else {std::cout << ". ";}
                    }
                }
                std::cout << "\n";
            }
        }

    private:
        int rows, cols;
        int startR,startC;
        int endR, endC;
        Tile*** arrBoard = nullptr;
};