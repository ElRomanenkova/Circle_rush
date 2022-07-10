#include "View.h"
#include "Engine.h"
#include <math.h>


const int SIZE_OF_CUBE = 7;

void drawPoint(int x, int y, uint32_t color)
{
    if (!((x >= SCREEN_WIDTH) || (x <= 0) || (y >= SCREEN_HEIGHT) || (y <= 0)))
        buffer[y][x] = color;
}

void drawCircle(int x, int y, int r, uint32_t color)
{
    int rr = r * r;
    for (int i = x - r; i <= x + r; ++i)
    {
        int root = sqrt(rr - (i - x) * (i - x));
        int j_min = y - root;
        int j_max = y + root;
        for (int j = j_min; j <= j_max; ++j)
            drawPoint(i, j, color);
    }
}

void drawCube(int x, int y, int half_a, uint32_t color)
{
    for (int i = x - half_a; i < x + half_a; ++i)
        for (int j = y - half_a; j < y + half_a; ++j)
            drawPoint(i, j, color);
}

void drawRectangle(int x, int y, int a_x, int b_y, uint32_t color)
{
    for (int i = x; i < x + a_x; ++i)
        for (int j = y; j < y + b_y; ++j)
            drawPoint(i, j, color);
}

void drawCross(int x, int y, int half_a, uint32_t color)
{
    int min_j = y - half_a;
    int max_j = y + half_a;
    for (int i = x - half_a; i < x + half_a; ++i)
    {
        for (int s = 0; s < 15; ++s) {
            if ((i + s < x + half_a) && (min_j < y + half_a))
                drawPoint(i + s, min_j, color);
            if ((i + s < x + half_a) && (max_j < y + half_a))
                drawPoint(i + s, max_j, color);
            if ((i < x + half_a) && (min_j + s < y + half_a))
                drawPoint(i, min_j + s, color);
            if ((i < x + half_a) && (max_j - s > y - half_a))
                drawPoint(i, max_j - s, color);
        }
        min_j++;
        max_j--;
    }
}





void drawBack()
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
        for(int j = 0; j < SCREEN_HEIGHT; ++j)
            buffer[j][i] = Color::SKYBLUE;
}





bool first = false;
bool second = false;
bool third = false;

float counter = 0;

void drawEndOfGame()
{
    if (first)
        drawCube(static_cast<int>(SCREEN_WIDTH / 2 - 150), static_cast<int>(SCREEN_HEIGHT / 2), 50, Color::MAROON);
    if (second)
        drawCross(static_cast<int>(SCREEN_WIDTH / 2), static_cast<int>(SCREEN_HEIGHT / 2), 50, Color::MAROON);
    if (third)
        drawCube(static_cast<int>(SCREEN_WIDTH / 2 + 150), static_cast<int>(SCREEN_HEIGHT / 2), 50, Color::MAROON);
}

void moveEnding(float dt)
{
    counter += dt;
    if (counter >= 0)
        first = true;
    if (counter >= 1)
        second = true;
    if (counter >= 2)
        third = true;
}





void parse(int n, std::vector<unsigned int>& vec)
{
    vec.push_back(n % 10);
    unsigned int temp = static_cast<unsigned int>(n / 10);
    if (temp == 0 ) return;
    parse(temp, vec);
}

std::vector<unsigned int> makeVectorFromNum(unsigned int num)
{
    if      (num == 0) return {1, 1, 1, 1, 1, 1, 0};
    else if (num == 1) return {0, 1, 1, 0, 0, 0, 0};
    else if (num == 2) return {1, 1, 0, 1, 1, 0, 1};
    else if (num == 3) return {1, 1, 1, 1, 0, 0, 1};
    else if (num == 4) return {0, 1, 1, 0, 0, 1, 1};
    else if (num == 5) return {1, 0, 1, 1, 0, 1, 1};
    else if (num == 6) return {1, 0, 1, 1, 1, 1, 1};
    else if (num == 7) return {1, 1, 1, 0, 0, 0, 0};
    else if (num == 8) return {1, 1, 1, 1, 1, 1, 1};
    else if (num == 9) return {1, 1, 1, 1, 0, 1, 1};
    else return {};
}

void drawNumByIndicator(int x, int y, std::vector<unsigned int> num)
{
    uint32_t color = Color::MAROON;

    if (num[0] == 1) drawRectangle(x + SIZE_OF_CUBE, y, 4 * SIZE_OF_CUBE, SIZE_OF_CUBE, color);
    if (num[1] == 1) drawRectangle(x + 5 * SIZE_OF_CUBE, y + SIZE_OF_CUBE, SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, color);
    if (num[2] == 1) drawRectangle(x + 5 * SIZE_OF_CUBE, y + 6 * SIZE_OF_CUBE, SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, color);
    if (num[3] == 1) drawRectangle(x + SIZE_OF_CUBE, y + 10 * SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, SIZE_OF_CUBE, color);
    if (num[4] == 1) drawRectangle(x, y + 6 * SIZE_OF_CUBE, SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, color);
    if (num[5] == 1) drawRectangle(x, y + SIZE_OF_CUBE, SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, color);
    if (num[6] == 1) drawRectangle(x + SIZE_OF_CUBE, y + 5 * SIZE_OF_CUBE, 4 * SIZE_OF_CUBE, SIZE_OF_CUBE, color);
}

void drawDigit(unsigned int score)
{
    std::vector<unsigned int> nums_of_score;
    parse(score, nums_of_score);
    int y = 35;
    int x = SCREEN_WIDTH - 70;

    for (auto& num : nums_of_score)
    {
        drawNumByIndicator(x, y, makeVectorFromNum(num));
        x -= 50;
    }
}

void drawLives(unsigned int lives)
{
    int x = 50;
    int y = 50;
    int rad = 15;

    for (int i = 0; i < lives; ++i)
    {
        drawCube(x, y, rad, Color::MAROON);
        x += 50;
    }
}
