#pragma once
#include <iostream>
#include "headers/Vec2D.h"
#include "headers/Player.h"
#include "headers/MersenneTwister.h"
#include "external_libraries/PDCurses/curses.h"

class Item {
protected:
    Vec2d position;
   

public:
 
    Item();
    Item(const Vec2d& pos);

    //Rule of Five
    Item(const Item& other);                 
    Item& operator=(const Item& other);      
    Item(Item&& other) noexcept;             
    Item& operator=(Item&& other) noexcept;  
    virtual ~Item();                         

  
    Vec2d getPosition() const;   
    
    virtual void drawSelf() const = 0;
    virtual void onPickUp(Player& player) = 0;
    MersenneTwister rng;

};


