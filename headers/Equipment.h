#pragma once 
#include "headers/Item.h"

enum class EquipmentSlot {
    Weapon,
    Armor,
    Shield
};

class Equipment : public Item {
private:
    int attack;
    int defense;
    int speed;
    EquipmentSlot slot;

public:
    Equipment(int id,const std::string& name,const std::string& description,const char* asciiSymbol,EquipmentSlot slot,
              int attack,int defense,int speed);

 
    
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    EquipmentSlot getSlot() const;

    // Overrides
    void use() override;       
    void inspect() const override;
};

