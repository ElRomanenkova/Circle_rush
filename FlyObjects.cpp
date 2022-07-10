#include "FlyObjects.h"

#include <random>

FlyObject::FlyObject(uint32_t color, unsigned int reward, unsigned int speed) : Objects(0, std::rand() % SCREEN_HEIGHT, FLY_OBJECT_RAD, color),
                                                                                speed_{speed}, reward_{reward}
{
    sin_phi_ = FlyObject::findSinPhi(y_);
}

bool FlyObject::getIsAlive() { return isAlive_; }

bool FlyObject::getIsCrashing() { return isCrashing_; }

void FlyObject::checkIsOnField()
{
    isAlive_ = !((x_ >= SCREEN_WIDTH) || (x_ <= 0) || (y_ >= SCREEN_HEIGHT) || (y_ <= 0));
}

double FlyObject::findSinPhi(float y)
{
    double dist = fabs(SCREEN_HEIGHT / 2 - y);
    double hypot = sqrt(static_cast<double>((SCREEN_WIDTH / 2) * (SCREEN_WIDTH / 2)) + dist * dist);

    double sin_t = (SCREEN_WIDTH / 2) / hypot;
    double cos_t = 1 - sin_t * sin_t;
    double sin_f = Player::PLAYER_RAD / hypot;
    double cos_f = 1 - sin_f * sin_f;

    double beg_sin = sin_t * cos_f - cos_t * sin_f;
    double end_sin = sin_t * cos_f + cos_t * sin_f;

    double res_sin = beg_sin + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (fabs(end_sin - beg_sin))));

    res_sin = (y > SCREEN_HEIGHT / 2) ? fabs(res_sin) : -fabs(res_sin);

    return res_sin;
}

void FlyObject::move(float dt)
{
    if (isAlive_)
        moveLiving(dt);
    else if (isCrashing_)
        moveDying();
}

void FlyObject::moveLiving(float dt)
{
    double ch = 200 * static_cast<double>(dt) * speed_;

    double step = ch * sqrt(1 / (sin_phi_ * sin_phi_) - 1);

    x_ += ch;
    step *= 0.85;
    y_ = (sin_phi_ > 0) ? y_ - step : y_ + step;

    checkIsOnField();
}

void FlyObject::moveDying()
{
    if (increase_)
    {
        if (rad_ < FLY_OBJECT_RAD + 10)
            rad_++;
        else
            increase_ = false;
    }
    else
        if (rad_ > 0)
            rad_--;
        else
            isCrashing_ = false;
}


////////////////////    Food & Enemy    ////////////////////


Food::Food(uint32_t color, unsigned int reward, unsigned int speed) : FlyObject(color, reward, speed) {}

unsigned int Food::getReward() { return reward_; }

void Food::draw()
{
    drawCircle(static_cast<int>(x_), static_cast<int>(y_), rad_, color_);
}

CollisionFlag Food::isCollide(Objects* that)
{
    double dist = Objects::distance(this, that);
    if (dist < rad_ + PlayerCircle::CIRCLE_RAD)
    {
        isAlive_ = false;
        isCrashing_ = true;
        return CollisionFlag::FOOD;
    }
    return CollisionFlag::NONE;
}

RegularFood::RegularFood() : Food(Color::WHITE, 1, 1) {}

SuperFood::SuperFood()  : Food(Color::GOLD, 2, 2) {}



Enemy::Enemy() : FlyObject(Color::BLACK, 0, 1) {}

void Enemy::draw()
{
    drawCube(static_cast<int>(x_), static_cast<int>(y_), rad_, color_);
}

CollisionFlag Enemy::isCollide(Objects* that)
{
    double dist = Objects::distance(this, that);
    if (dist < rad_ + PlayerCircle::CIRCLE_RAD)
    {
        isAlive_ = false;
        isCrashing_ = true;
        return CollisionFlag::ENEMY;
    }
    return CollisionFlag::NONE;
}