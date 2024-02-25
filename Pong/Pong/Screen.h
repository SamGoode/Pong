#pragma once
#include <string>

class Screen {
public:
    int width;
    int height;
    std::string screenMatrix[200];

    Screen(int width, int height);

    void reset();

    void input(std::string text, int x, int y);

    void rect(std::string text, int x, int y, int width, int height);

    void text(std::string text, int x, int y);

    void print();
};