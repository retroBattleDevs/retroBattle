#ifndef SUBMOVES_H
#define SUBMOVES_H

#include "BattleMove.h"
#include <string>

enum class TargetStat { 
    ATTACK, 
    DEFENSE, 
    SPEED 
};

// --- AttackMove --- //
class AttackMove : public BattleMove {
public:
    AttackMove(std::string name, int acc, int val);
    bool execute(Entity& executor, Entity& target) override;
    MoveCategory getCategory() const override;
};

// --- HealMove --- //
class HealMove : public BattleMove {
public:
    HealMove(std::string name, int acc, int val);
    bool execute(Entity& executor, Entity& target) override;
    MoveCategory getCategory() const override;
};

// --- BuffMove --- //
class BuffMove : public BattleMove {
private:
    TargetStat statTarget;
    bool isBuff;
public:
    
    BuffMove(std::string name, int acc, int val,TargetStat target,bool buff);
    bool execute(Entity& executor, Entity& target) override;
    MoveCategory getCategory() const override;

};

#endif