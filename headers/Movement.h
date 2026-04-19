#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include "headers/MersenneTwister.h"
#include "Enums.h"

class Movement {
public:
    Movement();
    virtual ~Movement();

    virtual void movingPatern(int& x, int& y, int& moveAmountX, int& moveAmountY) = 0;

    MersenneTwister* rng;
    std::string getTypeName() const;
    std::string MovementName;
    int type;
protected:

private:

};

#endif // MOVEMENT_H