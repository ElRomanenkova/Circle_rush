#pragma once

#include <vector>
#include <memory>

#include "FlyObjects.h"
//#include "Objects.h"
#include "View.h"
#include "Engine.h"


class PlayerCircle : public Objects {
public:
    static const int CIRCLE_RAD = 20;

    PlayerCircle(bool isSideLeft);
    virtual ~PlayerCircle() = default;

    void checkCoord();
    void startCrashing();
    bool getAliveness();
    void makeInvisible();

    void draw() override;
    void move(float dt) override;

private:
    void moveLiving(float dt);
    void moveDying(float dt);
};

class FlyObject;

class Player {
public:
    static const int PLAYER_RAD = 140;
    static const int NUMBER_OF_LIVES = 1;

    Player();

    void draw();
    void move(float dt);

    void changeRotation();

    void findCollision(FlyObject* object);

    bool getAliveness();
    int getScore();
    int getNumOfLives();

private:
    int lives;
    int score;

    int speed_;

    bool isClockwise_;
    bool isAlive_;

    PlayerCircle left;
    PlayerCircle right;
};