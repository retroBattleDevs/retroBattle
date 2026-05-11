#include "headers/items/Equipment.h"
#include <iostream>

Equipment::Equipment(int id,const std::string& name,const std::string& description,const char* asciiSymbol,
                       EquipmentSlot slot,int attack,int defense,int speed)
                    : Item(id, ItemType::Equipment, name, description, asciiSymbol)
{
    this->slot = slot;
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
}

int Equipment::getAttack() const { return this->attack; }
int Equipment::getDefense() const { return this->defense; }
int Equipment::getSpeed() const { return this->speed; }
EquipmentSlot Equipment::getSlot() const { return this->slot; }

void Equipment::use()
{
    std::cout << "Du rüstest " << this->getName() << " aus.\n";
}

void Equipment::inspect() const
{
    std::cout << "=== " << this->getName() << " ===\n";
    std::cout << this->getDescription() << "\n";
    std::cout << "Slot: ";

    switch (this->slot) {
    case EquipmentSlot::Weapon: std::cout << "Waffe"; break;
    case EquipmentSlot::Armor:  std::cout << "Rüstung"; break;
    case EquipmentSlot::Shield: std::cout << "Schild"; break;
    }

    std::cout << "\nATK: " << this->attack
        << "  DEF: " << this->defense
        << "  SPD: " << this->speed << "\n";
}
