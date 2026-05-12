#include "headers/Relic.h"


Relic::Relic(const Vec2d& pos, int bonus)
    : Item(pos, 'R'), bonusAmount(bonus) {
}


Relic::Relic(const Relic& other)
    : Item(other), bonusAmount(other.bonusAmount) {
}


Relic& Relic::operator=(const Relic& other) {
    if (this != &other) {
        Item::operator=(other);
        bonusAmount = other.bonusAmount;
    }
    return *this;
}


Relic::Relic(Relic&& other) noexcept
    : Item(std::move(other)), bonusAmount(other.bonusAmount) {
}


Relic& Relic::operator=(Relic&& other) noexcept {
    if (this != &other) {
        Item::operator=(std::move(other));
        bonusAmount = other.bonusAmount;
    }
    return *this;
}


Relic::~Relic() = default;

// Verhalten beim Aufheben
void Relic::onPickup(Player& player) {
    player.modifyAttackBuffStage(+1);   // +20% Attack
}


// Darstellung
void Relic::drawSelf() const {
    mvaddch((int)position.y, (int)position.x, symbol);
}
