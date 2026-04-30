#include "headers/movements/RandomMovement.h"

RandomMovement::RandomMovement() {
    type = random_movement;
    movementName = "randomMovement";
    rng = new MersenneTwister();
    initializeWalkable();
}

RandomMovement::~RandomMovement() {
    delete rng;
}

void RandomMovement::initializeWalkable() {
    int _rows = 0,
        _cols = 0;
    getmaxyx(stdscr, _rows, _cols);

    maxWidth = _cols;
    maxHeight = _rows;
    minWidth = 0;
    minHeight = 0;
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

    if (moveX > minWidth) {
        if (max.x >= maxWidth - 1) {
            pos.x -= moveAmountX;
        } else {
            pos.x += moveAmountX;
        }
    } else if (moveX < minWidth) {
        if (min.x == minWidth) {
            pos.x += moveAmountX;
        } else {
            pos.x -= moveAmountX;
        }
    }

    if (moveY > minHeight) {
        if (max.y >= maxHeight - 1) {
            pos.y -= moveAmountY;
        } else {
            pos.y += moveAmountY;
        }
    } else if (moveY < minHeight) {
        if (min.y == minHeight) {
            pos.y += moveAmountY;
        } else {
            pos.y -= moveAmountY;
        }
    }

    Vec2d diff = pos - pos_cache;
    min += diff;
    max += diff;
}
