#include "headers/movements/RandomMovement.h"

RandomMovement::RandomMovement() {
    type = random_movement;
    movementName = "randomMovement";
    rng = new MersenneTwister();
}

RandomMovement::~RandomMovement() {
    delete rng;
}

void RandomMovement::movingPatern(Vec2d &pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) {
    int realX = pos.x;
    int realY = pos.y;
    int moveUnits = 1;

    Vec2d pos_cache = pos;

    int moveX = rng->getRandomNumber(-1, 1);
    int moveY = rng->getRandomNumber(-1, 1);

    while ((moveX != 0 && moveY != 0) || (moveX == 0 && moveY == 0)) {
        moveX = rng->getRandomNumber(-1, 1);
        moveY = rng->getRandomNumber(-1, 1);
    }

    if (moveX < 0) {
        if (min.x == 1) {
            pos.x += moveAmountX;
        } else {
            pos.x -= moveAmountX;
        }
    } else if (moveX > 0) {
        if (max.x == 154) {
            pos.x -= moveAmountX;
        } else {
            pos.x += moveAmountX;
        }
    }

    if (moveY > 0) {
        if (max.y == 40) {
            pos.y -= moveAmountY;
        } else {
            pos.y += moveAmountY;
        }
    } else if (moveY < 0) {
        if (min.y == 0) {
            pos.y += moveAmountY;
        } else {
            pos.y -= moveAmountY;
        }
    }

    Vec2d diff = pos - pos_cache;
    min += diff;
    max += diff;
}
