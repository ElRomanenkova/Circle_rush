#pragma once

#include "Objects.h"
#include "View.h"
#include "Engine.h"
#include "Player.h"

enum CollisionFlag {
    FOOD,
    ENEMY,
    NONE
};

class FlyObject : public Objects {
public:
    static const int FLY_OBJECT_RAD = 15;

    virtual ~FlyObject() = default;

    void move(float dt) override;
    bool getIsAlive();
    bool getIsCrashing();
    virtual unsigned int getReward() = 0;

    virtual CollisionFlag isCollide(Objects* that) = 0;

protected:
    FlyObject(uint32_t color, unsigned int reward, unsigned int speed);

    void moveLiving(float dt);
    void moveDying();
    void checkIsOnField();
    static double findSinPhi(float y);

    double sin_phi_;
    unsigned int reward_;
    unsigned int speed_;
};


class Food : public FlyObject {
public:
    virtual ~Food() = default;

    void draw() override;
    CollisionFlag isCollide(Objects* that) override;
    unsigned int getReward() override;

protected:
    Food(uint32_t color, unsigned int reward, unsigned int speed);
};

class RegularFood : public Food {
public:
    RegularFood();
    virtual ~RegularFood() = default;
};

class SuperFood : public Food {
public:
    SuperFood();
    virtual ~SuperFood() = default;
};

class Enemy : public FlyObject {
public:
    Enemy();
    virtual ~Enemy() = default;

    void draw() override;
    CollisionFlag isCollide(Objects* that) override;
    unsigned int getReward() override { return 0; };
};