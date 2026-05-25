#include "headers/enemies/Spider.h"

Spider::Spider(int id, const int width, const int height, Vec2d position)
    : Enemy(id, width, height, position) {

}

void Spider::drawSelf() const {
    attron(COLOR_PAIR(13));

    mvprintw(position.y - 1, position.x - 1, "/ _ \\");
    mvprintw(position.y, position.x - 3, "\\_\\(_)/_/");
    mvprintw(position.y + 1, position.x - 2, "_//\"\\\\_");
    mvprintw(position.y + 2, position.x - 1, "/");
    mvprintw(position.y + 2, position.x + 3, "\\");

    attroff(COLOR_PAIR(13));
}