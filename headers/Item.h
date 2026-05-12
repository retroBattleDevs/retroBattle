#pragma once
#include <iostream>
#include "Vec2d.h"
#include "Player.h"
#include "external_libraries/PDCurses/curses.h"

class Item {
protected:
    Vec2d position;
    char symbol;

public:
 
    Item();
    Item(const Vec2d& pos, char sym);

    //Rule of Five
    Item(const Item& other);                 
    Item& operator=(const Item& other);      
    Item(Item&& other) noexcept;             
    Item& operator=(Item&& other) noexcept;  
    virtual ~Item();                         

  
    Vec2d getPosition() const;
    char getSymbol() const;

    
    virtual void onPickup(Player& player) = 0; //Verhalten 
    virtual void drawSelf() const = 0;

};


