#include "headers/movements/ChaseMovement.h"
#include "headers/general_funcs.h"
#include "headers/textures/TextureManager.h"
#include "headers/textures/AsciiTexture.h"

ChaseMovement::ChaseMovement(Entity* targetPlayer, Entity* self, int speed, int aggressionRadius) : target(targetPlayer), self(self), speed(speed), aggressionRadius(aggressionRadius) {
    type = chase_movement;
    movementName = "chaseMovement";
    speedCounter = 0;
    simpleMovementCounter = 0;
    state = MovementState::IDLE;
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

void ChaseMovement::setTextureForState() {
    TextureManager texManager;
    auto position = self->getPosition();
    std::shared_ptr<AsciiTexture> tex;

    switch (state) {
    case IDLE:
        tex = texManager.getTexture("neutralChaseEnemy");
        attron(COLOR_PAIR(3));
        tex->printTexture(position.y, position.x);
        attroff(COLOR_PAIR(3));
        break;
    case AGGRESSIVE:
        tex = texManager.getTexture("aggressiveChaseEnemy");
        attron(COLOR_PAIR(4));
        tex->printTexture(position.y, position.x);
        attroff(COLOR_PAIR(4));
        break;
    }
}

// Min Max Terrain Grenzen ueberpruefen
void ChaseMovement::movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) {
    setTextureForState();
    if (speedCounter == speed) {

        int realX = pos.x;
        int realY = pos.y;

        Vec2d pos_cache = pos;
        Vec2d desired_Point = target->getPosition();

        if (inAggressionRadius(target, self, 20)) {
            // if in aggression radius follow player
            state = AGGRESSIVE;

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
            state = IDLE;
            // else simple movement
            switch (simpleMovementCounter) {
            case 0:
                if (pos.y - moveAmountY >= minHeight) {
                    pos.y -= moveAmountY;
                }
                simpleMovementCounter++;
                break;
            case 1:
                if (pos.x + moveAmountX <= maxWidth) {
                    pos.x += moveAmountX;
                }
                simpleMovementCounter++;
                break;
            case 2:
                if (pos.y + moveAmountY <= maxHeight) {
                    pos.y += moveAmountY;
                }
                simpleMovementCounter++;
                break;
            case 3:
                if (pos.x - moveAmountX >= minWidth) {
                    pos.x -= moveAmountX;
                }
                simpleMovementCounter = 0;
                break;
            }
        }


        Vec2d diff = pos - pos_cache;
        min += diff;
        max += diff;
        speedCounter = 0;
    }
    else {
        speedCounter++;
    }
}