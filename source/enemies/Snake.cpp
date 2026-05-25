#include "headers/enemies/Snake.h"

Snake::Snake(int id, const int width, const int height, Vec2d position)
    : Enemy(id, width, height, position) {
}

void Snake::drawSelf() const {

    attron(COLOR_PAIR(13));

    mvprintw(position.y, position.x - 4, "~^~^~@");

    attroff(COLOR_PAIR(13));
}
