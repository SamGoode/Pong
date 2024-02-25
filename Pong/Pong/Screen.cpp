#include "Screen.h"
#include <iostream>

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i] += " ";
        }
    }
}

void Screen::reset() {
    for (int i = 0; i < height; i++) {
        screenMatrix[i] = "";
        for (int j = 0; j < width; j++) {
            screenMatrix[i] += " ";
        }
    }
}

void Screen::input(std::string text, int x, int y) {
    if (y < 0) {
        return;
    }

    std::string tempString = screenMatrix[y];
    screenMatrix[y] = "";

    for (int i = 0; i < tempString.length(); i++) {
        if (i != x) {
            screenMatrix[y] += tempString[i];
        }
        else {
            screenMatrix[y] += text;
        }
    }
}

void Screen::rect(std::string text, int x, int y, int width, int height) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            input(text, i, j);
        }
    }
}

void Screen::text(std::string text, int x, int y) {
    for (int i = 0; i < text.length(); i++) {
        std::string tempString = "";
        tempString += text[i];
        input(tempString, x + i, y);
    }
}

void Screen::print() {
    //system("cls");
    std::cout << "\033[1;1H";
    for (int i = 0; i < height; i++) {
        std::cout << screenMatrix[i];
        if (i < height - 1) {
            std::cout << std::endl;
        }
    }
}