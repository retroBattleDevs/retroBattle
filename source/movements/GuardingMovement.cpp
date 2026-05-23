#include "headers/movements/GuardingMovement.h"
#include "headers/general_funcs.h"
#include <functional>

GuardingMovement::GuardingMovement(Vec2d positionA, Vec2d positionB) : positionA(positionA), positionB(positionB), desiredPoint(positionA) {
    moveToPosA = false;
    initMovement = true;
    counter = 0;
    initializeWalkable();
}

GuardingMovement::~GuardingMovement() {}

void GuardingMovement::initializeWalkable() {
    int _rows = 0,
        _cols = 0;
    getmaxyx(stdscr, _rows, _cols);

    maxWidth = _cols;
    maxHeight = _rows;
    minWidth = 0;
    minHeight = 0;
}

void GuardingMovement::movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) {
    if (initMovement) {
        pos = positionA;
        initMovement = false;
    }
    
    if (counter == 2) {
        int realX = pos.x;
        int realY = pos.y;
        Vec2d pos_cache = pos;

        int xDistance = std::abs(desiredPoint.x - realX);
        int yDistance = std::abs(desiredPoint.y - realY);

        if (pos.x == positionA.x && pos.y == positionA.y) {
            desiredPoint = positionB;
        }
        if (pos.x == positionB.x && pos.y == positionB.y) {
            desiredPoint = positionA;
        }

        if (xDistance == 0) {
            if (pos.y > desiredPoint.y) { pos.y -= moveAmountY; }
            if (pos.y < desiredPoint.y) { pos.y += moveAmountY; }
        }
        else if (yDistance == 0) {
            if (pos.x > desiredPoint.x) { pos.x -= moveAmountX; }
            if (pos.x < desiredPoint.x) { pos.x += moveAmountX; }
        }
        else if (xDistance < yDistance) {
            if (desiredPoint.x > realX) {
                pos.x += moveAmountX;
            }
            else if (desiredPoint.x < realX) {
                pos.x -= moveAmountX;
            }
        }
        else if (xDistance > yDistance) {
            if (desiredPoint.y > realY) {
                pos.y += moveAmountY;
            }
            else if (desiredPoint.y < realX) {
                pos.y -= moveAmountY;
            }
        }

        Vec2d diff = pos - pos_cache;
        min += diff;
        max += diff;
        counter = 0;
    }
    else {
        counter++;
    }
}