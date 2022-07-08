#include "Objects.h"

#include <math.h>

Objects::Objects(int rad, uint32_t color) : rad_{rad}, color_{color}, increase_{true},
                                            isAlive_{true}, isCrashing_{false} {}

Objects::Objects(double x, double y, int rad, uint32_t color) : x_{x}, y_{y}, rad_{rad}, color_{color},
                                            isAlive_{true}, isCrashing_{false}, increase_{true} {}

double Objects::distance(Objects* first, Objects* second)
{
    return sqrt((first->x_ - second->x_) * (first->x_ - second->x_) + (first->y_ - second->y_) * (first->y_ - second->y_));
}