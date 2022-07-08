#pragma once

#include "Objects.h"
#include "View.h"
#include "Engine.h"
#include "Player.h"


class FlyObject : public Objects {
public:
    static const int FLY_OBJECT_RAD = 15;

    virtual ~FlyObject() = default;

    void move(float dt) override;
    bool getIsAlive();
    bool getIsCrashing();

    virtual char isCollide(Objects* that) = 0;

protected:
    FlyObject(uint32_t color);

    void moveLiving(float dt);
    void moveDying(float dt);
    void checkIsOnField();
    static double findSinPhi(float y);

    double sin_phi_;
};


class Food : public FlyObject {
public:
    Food();
    virtual ~Food() = default;

    void draw() override;
    char isCollide(Objects* that) override;
};


class Enemy : public FlyObject {
public:
    Enemy();
    virtual ~Enemy() = default;

    void draw() override;
    char isCollide(Objects* that) override;
};