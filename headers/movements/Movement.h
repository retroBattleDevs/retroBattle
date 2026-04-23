#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include "headers/MersenneTwister.h"
#include "headers/Enums.h"
#include "headers/Vec2D.h"

class Movement {
public:
    Movement();
    virtual ~Movement();

    virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) = 0;

    MersenneTwister* rng;
    std::string getTypeName() const;
    std::string movementName;
    int type;
protected:

private:

};

#endif // MOVEMENT_H