#include "headers/movements/ChaseMovement.h"
#include "headers/general_funcs.h"

ChaseMovement::ChaseMovement(Entity* targetPlayer, Entity* self) : target(targetPlayer), self(self) {
    type = chase_movement;
    movementName = "chaseMovement";
    counter = 0;
    simpleMovementCounter = 0;
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

// Min Max Terrain Grenzen ueberpruefen
void ChaseMovement::movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) {
    if (counter == 3) {

        int realX = pos.x;
        int realY = pos.y;

        Vec2d pos_cache = pos;
        Vec2d desired_Point = target->getPosition();

        if (inAggressionRadius(target, self, 30)) {
            // if in aggression radius follow player

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
        }
        else {
            // else simple movement
            switch (simpleMovementCounter) {
            case 0: 
                pos.y -= moveAmountY;
                simpleMovementCounter++;
                break;
            case 1:
                pos.x += moveAmountX;
                simpleMovementCounter++;
                break;
            case 2:
                pos.y += moveAmountY;
                simpleMovementCounter++;
                break;
            case 3:
                pos.x -= moveAmountX;
                simpleMovementCounter = 0;
                break;
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