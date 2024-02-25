#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include "Screen.h"

class Vector {
public:
    int x;
    int y;

    Vector() {
        this->x = NULL;
        this->y = NULL;
    }

    Vector(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Vector add(Vector v) {
        x += v.x;
        y += v.y;
        return Vector(x, y);
    }

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class GameObject {
public:
    Vector pos;
    Vector vel;
    int width;
    int height;
    std::string text;

    GameObject() {
        this->width = NULL;
        this->height = NULL;
    }

    GameObject(int x, int y, int width, int height, std::string text) {
        this->pos = Vector(x, y);
        this->vel = Vector(0, 0);
        this->width = width;
        this->height = height;
        this->text = text;
    }

    void update() {
        pos = pos.add(vel);
    }

    void show(Screen& screen, std::string text) {
        screen.rect(text, pos.x, pos.y, width, height);
    }

    int getEdge(std::string edge) {
        if (edge == "left") {
            return pos.x;
        }
        else if (edge == "right") {
            return pos.x + width - 1;
        }
        else if (edge == "up") {
            return pos.y;
        }
        else if (edge == "down") {
            return pos.y + height - 1;
        }

        return NULL;
    }

    void setEdge(std::string edge, int axisPos) {
        if (edge == "left") {
            pos.x = axisPos;
        }
        else if (edge == "right") {
            pos.x = axisPos - width + 1;
        }
        else if (edge == "up") {
            pos.y = axisPos;
        }
        else if (edge == "down") {
            pos.y = axisPos - height + 1;
        }
    }
};

int main() {
    bool UP1;
    bool DOWN1;
    bool UP2;
    bool DOWN2;
    bool SPACE;

    Screen screen = Screen(237, 63);

    GameObject player1 = GameObject(30, 30, 5, 10, "O");
    GameObject player2 = GameObject(202, 30, 5, 10, "O");
    GameObject ball = GameObject(118, 30, 2, 2, "B");

    ball.vel.set(0, 0);

    bool gameRunning = false;
    int player1Score = 0;
    int player2Score = 0;

    while (true) {
        UP1 = GetAsyncKeyState(0x57);
        DOWN1 = GetAsyncKeyState(0x53);
        UP2 = GetAsyncKeyState(VK_UP);
        DOWN2 = GetAsyncKeyState(VK_DOWN);
        SPACE = GetAsyncKeyState(VK_SPACE);

        if (SPACE && !gameRunning) {
            gameRunning = true;
            ball.vel.set(-2, 1);
        }

        player1.vel.set(0, 0);
        if (UP1) {
            player1.vel.y -= 2;
        }
        if (DOWN1) {
            player1.vel.y += 2;
        }

        player2.vel.set(0, 0);
        if (UP2) {
            player2.vel.y -= 2;
        }
        if (DOWN2) {
            player2.vel.y += 2;
        }

        if (player1.getEdge("up") + player1.vel.y <= 0) {
            player1.setEdge("up", 0);
            player1.vel.y = 0;
        }
        else if (player1.getEdge("down") + player1.vel.y >= screen.height - 1) {
            player1.setEdge("down", screen.height - 1);
            player1.vel.y = 0;
        }

        if (player2.getEdge("up") + player2.vel.y <= 0) {
            player2.setEdge("up", 0);
            player2.vel.y = 0;
        }
        else if (player2.getEdge("down") + player2.vel.y >= screen.height - 1) {
            player2.setEdge("down", screen.height - 1);
            player2.vel.y = 0;
        }

        if (ball.getEdge("up") <= 0) {
            ball.setEdge("up", 0);
            ball.vel.y = 1;
        }
        else if (ball.getEdge("down") >= screen.height - 1) {
            ball.setEdge("down", screen.height - 1);
            ball.vel.y = -1;
        }
        
        if (ball.getEdge("left") <= 0) {
            gameRunning = false;
            
            ball.pos.set(118, 30);
            ball.vel.set(0, 0);

            player2Score += 1;
        }
        else if (ball.getEdge("right") >= screen.width - 1) {
            gameRunning = false;

            ball.pos.set(118, 30);
            ball.vel.set(0, 0);

            player1Score += 1;
        }

        if (ball.getEdge("left") <= player1.getEdge("right") && ball.getEdge("right") >= player1.getEdge("left") && ball.getEdge("down") >= player1.getEdge("up") && ball.getEdge("up") <= player1.getEdge("down")) {
            ball.setEdge("left", player1.getEdge("right"));
            ball.vel.x = 2;
        }

        if (ball.getEdge("right") >= player2.getEdge("left") && ball.getEdge("left") <= player2.getEdge("right") && ball.getEdge("down") >= player2.getEdge("up") && ball.getEdge("up") <= player2.getEdge("down")) {
            ball.setEdge("right", player2.getEdge("left"));
            ball.vel.x = -2;
        }
        
        screen.reset();

        player1.update();
        player1.show(screen, "O");

        player2.update();
        player2.show(screen, "O");

        ball.update();
        ball.show(screen, "B");

        screen.text("Player 1 score: " + std::to_string(player1Score), 50, 5);
        screen.text("Player 2 score: " + std::to_string(player2Score), 160, 5);

        screen.print();

        Sleep(20);
    }
}
