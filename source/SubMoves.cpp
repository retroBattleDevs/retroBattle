#include "headers/SubMoves.h"
#include <iostream>
#include <random>

// --- AttackMove --- // -----------------------------------
AttackMove::AttackMove(std::string name, int acc, int val):BattleMove(name,acc,val){
    
}

bool AttackMove::execute(Entity& executor, Entity& target){
    int roll = rand() % 100;

    if (roll < accuracy) {
        
        int damage = value + executor.getFinalAttack();

        target.takeDamage(damage);
        return true;
    }
    return false;
}

MoveCategory AttackMove::getCategory() const {
    return MoveCategory::ATTACK;
}

// --- HealMove --- // -----------------------------------
HealMove::HealMove(std::string name, int acc, int val):BattleMove(name, acc, val) {

}

bool HealMove::execute(Entity& executor, Entity& target) {
    int roll = rand() % 100;

    if (roll < accuracy) {

        int heal = value;

        target.heal(heal);
        return true;
    }
    return false;
}

MoveCategory HealMove::getCategory() const {
    return MoveCategory::HEAL;
}

// --- BuffMove --- // -----------------------------------
BuffMove::BuffMove(std::string name, int acc, int val, TargetStat target,bool buff):BattleMove(name, acc, val){
    statTarget = target;
    isBuff = buff;
}

bool BuffMove::execute(Entity& executor, Entity& target) {
    int roll = rand() % 100;

    if (roll < accuracy) {
        // If it's a buff, value is positive. If debuff, value is negative.
        int modifier = isBuff ? value : -value;

        // Determine who gets affected
        // Buffs (isBuff = true) -> affect the User (executor)
        // Debuffs (isBuff = false) -> affect the Enemy (target)
        Entity& affectedEntity = isBuff ? executor : target;

        switch (statTarget) {
        case TargetStat::ATTACK:
            affectedEntity.modifyAttackBuffStage(modifier);
            break;

        case TargetStat::DEFENSE:
            affectedEntity.modifyDefenceBuffStage(modifier);
            break;

        case TargetStat::SPEED:
            affectedEntity.modifySpeedBuffStage(modifier);
            break;

        default:
            return false;
        }
        return true;
    }
    return false;
}

MoveCategory BuffMove::getCategory() const {
    // If isBuff is true, return BUFF (target self). 
    // If false, return DEBUFF (target enemy).
    return isBuff ? MoveCategory::BUFF : MoveCategory::DEBUFF;
}