
#include "headers/Items/Item.h"
#include "headers/Vec2D.h"



Item::Item(): position(0, 0), symbol('?') {
}


Item::Item(const Vec2d& pos, char sym): position(pos), symbol(sym) {
}


Item::Item(const Item& other): position(other.position), symbol(other.symbol) {
}


Item& Item::operator=(const Item& other) {
    if (this != &other) {
        position = other.position;
        symbol = other.symbol;
    }
    return *this;
}


Item::Item(Item&& other) noexcept: position(other.position), symbol(other.symbol) {
}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        position = other.position;
        symbol = other.symbol;
    }
    return *this;
}


Item::~Item() = default;


Vec2d Item::getPosition() const {
    return position;
}

char Item::getSymbol() const {
    return symbol;
}
