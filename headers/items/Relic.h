#pragma once 
#include "headers/Items/Item.h"
#include "external_libraries/PDCurses/curses.h"


class Relic : public Item {
private:
    int bonusAmount;   // z.B. +5 Attack

public:
  
    Relic(const Vec2d& pos, int bonus = 5);

    // Rule of Five
    Relic(const Relic& other);
    Relic& operator=(const Relic& other);
    Relic(Relic&& other) noexcept;
    Relic& operator=(Relic&& other) noexcept;
    ~Relic() override;

   
    void onPickup(Player& player) override;
   
    void drawSelf() const override;
};



