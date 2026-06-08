
#include "headers/Items/Item.h"
#include "headers/Vec2D.h"
#include "headers/Player.h"


Item::Item(): position(0, 0) {
}


Item::Item(const Vec2d& pos): position(pos) {
    position.x = rng.getRandomNumber(0, 156);
    position.y = rng.getRandomNumber(0, 39);

}


Item::Item(const Item& other): position(other.position) {
}


Item& Item::operator=(const Item& other) {
    if (this != &other) {
        position = other.position;
        
    }
    return *this;
}


Item::Item(Item&& other) noexcept: position(other.position) {
}

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


