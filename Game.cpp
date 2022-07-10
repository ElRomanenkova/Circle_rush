#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <memory>
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>

#include "Player.h"
#include "FlyObjects.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()

#define OBJECTS_NEWBORN 2

Player player;
std::vector<std::unique_ptr<FlyObject>> fly_objects_;
float objects_timer = OBJECTS_NEWBORN - 1;
bool wasSpacePressed = false;


// initialize game data in this function
void initialize()
{
    srand(static_cast<unsigned>(time(0)));
}

void handlingGameEvents()
{
    for (auto& ob : fly_objects_) {
        if (ob->getIsAlive())
            player.findCollision(ob.get());
    }

    auto newEnd = std::remove_if(fly_objects_.begin(), fly_objects_.end(), [](std::unique_ptr<FlyObject>& ob) {
        return !(ob->getIsAlive() || ob->getIsCrashing());
    });
    fly_objects_.erase(newEnd, fly_objects_.end());
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{

    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    if (!is_key_pressed(VK_SPACE))
        wasSpacePressed = false;

    if (is_key_pressed(VK_SPACE))
    {
        if (!wasSpacePressed)
            player.changeRotation();
        wasSpacePressed = true;
    }

    objects_timer += dt;

    if (objects_timer >= OBJECTS_NEWBORN)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<std::mt19937::result_type> d(0, 5);

        if (d(g) == 0)
            fly_objects_.emplace_back(std::make_unique<Enemy>());
        else if (d(g) == 1)
            fly_objects_.emplace_back(std::make_unique<SuperFood>());
        else
            fly_objects_.emplace_back(std::make_unique<RegularFood>());

        objects_timer = 0;
    }

    handlingGameEvents();

    if (player.getAliveness())
        player.move(dt);

    for (const auto &ob: fly_objects_)
        ob->move(dt);

    if (!player.getAliveness())
        moveEnding(dt);
}


// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    drawBack();
    player.draw();

    for (const auto& o : fly_objects_)
        o->draw();

    drawDigit(player.getScore());
    drawLives(player.getNumOfLives());

    if (!player.getAliveness()) {
        drawEndOfGame();
    }
}

// free game data in this function
void finalize()
{

}
