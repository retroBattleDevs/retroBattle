#include "headers/BattleMove.h"

BattleMove::BattleMove(std::string name, int acc, int val) {
	this->moveName = name;
	this->accuracy = acc;
	this->value = val;
}

std::string BattleMove::getName() const
{
	return this->moveName;
}

int BattleMove::getValue() const
{
	return this->value;
}

int BattleMove::getAccuracy() const
{
	return this->accuracy;
}
