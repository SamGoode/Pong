#include "Screen.h"
#include <iostream>

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;

    screenMatrix = new char*[height];
    for (int i = 0; i < height; i++) {
        screenMatrix[i] = new char[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

Screen::~Screen() {
    for (int i = 0; i < height; i++) {
        delete[] screenMatrix[i];
    }

    delete[] screenMatrix;
}

void Screen::reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

void Screen::input(char text, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    screenMatrix[y][x] = text;
}

void Screen::rect(char text, int x, int y, int width, int height) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            input(text, i, j);
        }
    }
}

void Screen::text(std::string text, int x, int y) {
    for (int i = 0; i < text.length(); i++) {
        input(text[i], x + i, y);
    }
}

void Screen::print() {
    std::string printout = "\x1b[?25l\x1b[1;1H";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printout += screenMatrix[i][j];
        }
        if (i < height - 1) {
            printout += "\n";
        }
    }
    //printout += "\x1b[?25h";

    std::cout << printout;
}