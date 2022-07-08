#include "Player.h"
#include <math.h>
#include <iostream>


////////////////////    Player    ////////////////////

Player::Player() : left(true), right(false), isClockwise_{true}, isAlive_{true},
                    score{0}, lives{NUMBER_OF_LIVES}, speed_{3} {}

bool Player::getAliveness()  { return isAlive_; }

int Player::getScore()  { return score; }

int Player::getNumOfLives()  { return lives; }

void Player::move(float dt)
{
    float phi;
    int speed = speed_ + score / 10;
    if (isClockwise_)
        phi = abs(speed * dt);
    else
        phi = - abs(speed * dt);

    left.move(phi);
    right.move(phi);

    left.checkCoord();
    right.checkCoord();

    if (!(left.getAliveness() || right.getAliveness()))
    {
        isAlive_ = false;
        left.makeInvisible();
        right.makeInvisible();
    }
}

void Player::draw()
{
    drawCircle(static_cast<int>(SCREEN_WIDTH / 2), static_cast<int>(SCREEN_HEIGHT / 2),
               PLAYER_RAD, Color::VIOLET);
    left.draw();
    right.draw();
}

void Player::changeRotation()
{
    isClockwise_ = !isClockwise_;
}

void Player::findCollision(FlyObject* object)
{
    char l = object->isCollide(&left);
    char r = object->isCollide(&right);

    if ((l == 'f') || (r == 'f'))
        score++;
    else if ((l == 'e') || (r == 'e'))
    {
        lives--;
        if (lives == 0) {
            left.startCrashing();
            right.startCrashing();
        }
    }
}

////////////////////    PlayerCircle    ////////////////////


PlayerCircle::PlayerCircle(bool isSideLeft) : Objects(CIRCLE_RAD, Color::WHITE)
{
    if (isSideLeft)
        x_ = (SCREEN_WIDTH / 2) - Player::PLAYER_RAD;
    else
        x_ = (SCREEN_WIDTH / 2) + Player::PLAYER_RAD;

    y_ = (SCREEN_HEIGHT / 2);
}

bool PlayerCircle::getAliveness()
{
    return (isAlive_ || isCrashing_);
}

void PlayerCircle::startCrashing()
{
    isCrashing_ = true;
    isAlive_ = false;
}

void PlayerCircle::makeInvisible()
{
    x_ = -10;
    y_ = -10;
}

void PlayerCircle::draw()
{
    drawCircle(static_cast<int>(x_), static_cast<int>(y_), rad_, color_);
}

void PlayerCircle::move(float dt)
{
    if (isAlive_)
        moveLiving(dt);
    else if (isCrashing_)
        moveDying(dt);
}

void PlayerCircle::moveLiving(float dt)
{
    double cos_ = cos(dt);
    double sin_ = sin(dt);

    double x_0 = (SCREEN_WIDTH / 2);
    double y_0 = (SCREEN_HEIGHT / 2);

    double xx = (x_ - x_0) * cos_ - (y_ - y_0) * sin_ + x_0;
    double yy = (x_ - x_0) * sin_ + (y_ - y_0) * cos_ + y_0;

    x_ = xx;
    y_ = yy;
}

void PlayerCircle::moveDying(float dt)
{
    if (increase_) {
        if (rad_ < CIRCLE_RAD + 20)
            rad_++;
        else
            increase_ = false;
    }
    else
    if (rad_ > 0)
        rad_--;
    else {
        isCrashing_ = false;
    }
}

void PlayerCircle::checkCoord()
{
    if (x_ > SCREEN_WIDTH - 1)   { x_ -= SCREEN_WIDTH;  }
    if (x_ <= 0)                 { x_ += SCREEN_WIDTH;  }

    if (y_ > SCREEN_HEIGHT - 1)  { y_ -= SCREEN_HEIGHT; }
    if (y_ <= 0)                 { y_ += SCREEN_HEIGHT; }
}