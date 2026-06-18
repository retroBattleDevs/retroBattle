#include "headers/items/Relic.h"
#include "headers/items/Item.h"
#include "headers/Vec2D.h"
#include "headers/Player.h"

Relic::Relic(const Vec2d& pos, int bonus, RelicType type, Animator* animation)
    : Item(pos), bonusAmount(bonus), type(type) {
    this->animation = std::make_shared<Animator>(*animation);
}

Relic::Relic(const Relic& other)
    : Item(other), bonusAmount(other.bonusAmount), type(other.type), animation(other.animation) {}

Relic& Relic::operator=(const Relic& other) {
    if (this != &other) {
        Item::operator=(other);
        bonusAmount = other.bonusAmount;
    }
    return *this;
}

Relic::Relic(Relic&& other) noexcept
    : Item(std::move(other)), bonusAmount(other.bonusAmount), type(other.type), animation(other.animation) {}

Relic& Relic::operator=(Relic&& other) noexcept {
    if (this != &other) {
        Item::operator=(std::move(other));
        bonusAmount = other.bonusAmount;
    }
    return *this;
}

Relic::~Relic() = default;

// Darstellung
void Relic::drawSelf() const {
    attron(COLOR_PAIR(9));
    if (animation != nullptr) {
        animation->draw(this->position);
    }
    else {
        mvprintw(position.y - 2, position.x - 2, " .-. ");
        mvprintw(position.y - 1, position.x - 2, "( * )");
        mvprintw(position.y, position.x - 2, " \\_/ ");
        mvprintw(position.y + 1, position.x - 2, " / \\ ");
        mvprintw(position.y + 2, position.x - 2, " ' ' ");
        mvprintw(position.y, position.x, "+");
    }
    attroff(COLOR_PAIR(9));
}

void Relic::onPickUp(Player& player) {
    switch (type) {
        case RelicType::AttackBoost:
            player.setAttack(player.getAttack() + 10);
            break;

        case RelicType::SpeedBoost:
            player.setSpeed(player.getSpeed() + 5);
            break;

        case RelicType::HealthBoost:
            player.heal(20);   
            break;

        case RelicType::DefenceBoost:
            player.setDefence(player.getDefence() + 1);
            break;
    }
    player.addRelic();
}


