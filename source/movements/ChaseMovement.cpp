#include "headers/movements/ChaseMovement.h"

ChaseMovement::ChaseMovement(Entity* targetPlayer) : target(targetPlayer) {
    type = chase_movement;
    movementName = "chaseMovement";
    counter = 0;
    initializeWalkable();
}

ChaseMovement::~ChaseMovement() {

}

void ChaseMovement::initializeWalkable() {
    int _rows = 0,
        _cols = 0;
    getmaxyx(stdscr, _rows, _cols);

    maxWidth = _cols;
    maxHeight = _rows;
    minWidth = 0;
    minHeight = 0;
}

void ChaseMovement::movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) {
    if (counter == 3) {

        int realX = pos.x;
        int realY = pos.y;

        Vec2d pos_cache = pos;
        Vec2d desired_Point = target->getPosition();

        int xDistance = std::abs(desired_Point.x - realX);
        int yDistance = std::abs(desired_Point.y - realY);

        if (xDistance == 0) {
            if (pos.y > desired_Point.y) { pos.y -= moveAmountY; }
            if (pos.y < desired_Point.y) { pos.y += moveAmountY; }
        }
        else if (yDistance == 0) {
            if (pos.x > desired_Point.x) { pos.x -= moveAmountX; }
            if (pos.x < desired_Point.x) { pos.x += moveAmountX; }
        }
        else if (xDistance < yDistance) {
            if (desired_Point.x > realX) {
                pos.x += moveAmountX;
            }
            else if (desired_Point.x < realX) {
                pos.x -= moveAmountX;
            }
        }
        else if (xDistance > yDistance) {
            if (desired_Point.y > realY) {
                pos.y += moveAmountY;
            }
            else if (desired_Point.y < realX) {
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