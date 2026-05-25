#pragma once 
#include "headers/items/Item.h"
#include "external_libraries/PDCurses/curses.h"

enum class RelicType {
    AttackBoost,
    SpeedBoost,
    HealthBoost

};


class Relic : public Item {
private:
    int bonusAmount;  
    RelicType type;

public:
  
    Relic(const Vec2d& pos, int bonus, RelicType type);

    // Rule of Five
    Relic(const Relic& other);
    Relic& operator=(const Relic& other);
    Relic(Relic&& other) noexcept;
    Relic& operator=(Relic&& other) noexcept;
    ~Relic() override;

   
    
   
    void drawSelf() const override;
    void onPickUp(Player& player) override;

};



