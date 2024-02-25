#include "Screen.h"
#include <iostream>

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

void Screen::reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

void Screen::input(char text, int x, int y) {
    if (x < 0 || y < 0) {
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
    std::string printout = "\033[1;1H";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printout += screenMatrix[i][j];
        }
        if (i < height - 1) {
            printout += "\n";
        }
    }

    std::cout << printout;
}