#pragma once 
#include "headers/items/Item.h"
#include "external_libraries/PDCurses/curses.h"
#include "headers/textures/Animator.h"
#include <memory>

class Player;

enum class RelicType {
    AttackBoost,
    SpeedBoost,
    HealthBoost

};


class Relic : public Item {
private:
    
    RelicType type;
    std::shared_ptr<Animator> animation;

public:
    Relic();
    Relic(const Vec2d& pos, RelicType type, std::shared_ptr<Animator> animation);

    // Rule of Five
    Relic(const Relic& other);
    Relic& operator=(const Relic& other);
    Relic(Relic&& other) noexcept;
    Relic& operator=(Relic&& other) noexcept;
    ~Relic();

   
    
   
    void drawSelf() const override;
    void onPickUp(Player& player) override;

};



