#pragma once

#include <cstdint>
#include <vector>

enum Color {
    WHITE   = 0xffffff,
    BLACK   = 0x000000,
    MAROON  = 0x800000,
    VIOLET  = 0x8080ff,
    SKYBLUE = 0x87CEEB,
    GOLD    = 0xFFD700
};


void drawPoint(int x, int y, uint32_t color);
void drawCircle(int x, int y, int r, uint32_t color);
void drawCube(int x, int y, int half_a, uint32_t color);
void drawRectangle(int x, int y, int a_x, int b_y, uint32_t color);
void drawCross(int x, int y, int half_a, uint32_t color);

void drawBack();

void drawLives(unsigned int lives);

void drawNumByIndicator(int x, int y, std::vector<unsigned int>& num);
void drawDigit(unsigned int score);

void moveEnding(float dt);
void drawEndOfGame();