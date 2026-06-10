#include "headers/Items/Item.h"
#include "headers/Vec2D.h"
#include "headers/Player.h"

Item::Item(): position(0, 0) {
}

Item::Item(const Vec2d& pos): position(pos) {
    position.x = rng.getRandomNumber(2, 153);
    position.y = rng.getRandomNumber(2, 37);

}

Item::Item(const Item& other): position(other.position) {
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        position = other.position;
        
    }
    return *this;
}

Item::Item(Item&& other) noexcept: position(other.position) {}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        position = other.position;
        
    }
    return *this;
}

Item::~Item() = default;

Vec2d Item::getPosition() const {
    return position;
}