#pragma once
#include <string>

class Screen {
public:
    int width;
    int height;
    char screenMatrix[200][400];

    Screen(int width, int height);

    void reset();

    void input(char text, int x, int y);

    void rect(char text, int x, int y, int width, int height);

    void text(std::string text, int x, int y);

    void print();
};