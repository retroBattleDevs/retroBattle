#ifndef MOVE_H
#define MOVE_H

#include "Entity.h";
#include <string>

enum class MoveCategory {
    ATTACK,
    HEAL,
    BUFF,
    DEBUFF
};

class BattleMove {
protected:
    std::string moveName;
    int accuracy;
    int value;

public:
    BattleMove(std::string name, int acc, int val);
    virtual ~BattleMove() {} // Virtual destructor

    virtual bool execute(Entity& executor,Entity& target) = 0;
    virtual MoveCategory getCategory() const = 0;

    std::string getName() const;
    int getValue() const;
    int getAccuracy() const;
};

#endif