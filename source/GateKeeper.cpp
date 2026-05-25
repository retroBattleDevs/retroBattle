#include "headers/GateKeeper.h"
#include <utility>

GateKeeper::GateKeeper() : Entity() {
    movement = nullptr;
}

GateKeeper::GateKeeper(int id, const int width, const int height, Vec2d position) : Entity(id, width, height, position) {
    movement = nullptr;
}

GateKeeper::~GateKeeper() {}

GateKeeper::GateKeeper(const GateKeeper& other) : Entity(other) {}

GateKeeper& GateKeeper::operator=(const GateKeeper& other) {
    if (this != &other) {
        Entity::operator=(other);}
    return *this;
}

GateKeeper::GateKeeper(GateKeeper&& other) noexcept : Entity(std::move(other)) {}


GateKeeper& GateKeeper::operator=(GateKeeper&& other) noexcept {
    if (this != &other) {
        Entity::operator=(std::move(other));}
    return *this;
}

// --- Overridden Methods ---


void GateKeeper::drawSelf() const {
    attron(COLOR_PAIR(4));
    mvprintw(position.y - 1, position.x - 2, "[___]");
    mvprintw(position.y, position.x - 2,     "(o_o)");
    mvprintw(position.y + 1, position.x - 2, "/ | \\");
    attroff(COLOR_PAIR(4));
}

EntityTypes::Type GateKeeper::getType() const {
    return EntityTypes::Type::Gatekeeper;
}