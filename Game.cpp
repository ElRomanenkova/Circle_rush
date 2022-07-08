#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <memory>
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>

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
//std::vector<std::unique_ptr<Object>> fly_objects_;
std::vector<std::shared_ptr<FlyObject>> fly_objects_;
float objects_timer = OBJECTS_NEWBORN - 1;
float rotation_timer = 0;


// initialize game data in this function
void initialize()
{
    srand (static_cast <unsigned> (time(0)));
}

void handlingGameEvents()
{
    for (auto& ob : fly_objects_) {
        if (ob->getIsAlive())
            player.findCollision(ob.get());
    }

    auto newEnd = std::remove_if(fly_objects_.begin(), fly_objects_.end(), [](std::shared_ptr<FlyObject> ob) {
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

    if (is_key_pressed(VK_SPACE))
    {
        rotation_timer += dt;

        if (rotation_timer >= 7 * dt) {
            player.changeRotation();
            rotation_timer = 0;
        }
    }

    objects_timer += dt;

    if (objects_timer >= OBJECTS_NEWBORN) {
        float r = std::rand() % 3;
        std::shared_ptr <FlyObject> ob;
        if (r == 0) {
            auto enemy = std::make_shared<Enemy>();
            ob = std::static_pointer_cast<FlyObject>(enemy);
        } else {
            auto food = std::make_shared<Food>();
            ob = std::static_pointer_cast<FlyObject>(food);
        }
        fly_objects_.push_back(ob);
//    if (r == 0)
//            objects_.push_back(std::make_unique<Enemy>());
//        else
//            objects_.push_back(std::make_unique<Food>());

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
