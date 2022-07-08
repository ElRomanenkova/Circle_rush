#pragma once

#include "View.h"
#include "Engine.h"


class Objects {
public:
    Objects() = default;
    Objects(int rad, uint32_t color);
    Objects(double x, double y, int rad, uint32_t color);
    virtual ~Objects() = default;

    static double distance(Objects* first, Objects* second);

    virtual void move(float dt) = 0;
    virtual void draw() = 0;

protected:
    bool isAlive_;
    bool isCrashing_;

    bool increase_;

    double x_;
    double y_;
    int rad_;
    uint32_t color_;
};