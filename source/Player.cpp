#include "headers/Player.h"

Player::Player() : Entity() {}

Player::Player(int id, Vec2d min, Vec2d max, Vec2d position) : Entity(id, min, max, position) {}

EntityTypes::Type Player::getType() const {
	return EntityTypes::Type::Player;
}

/*
void Player::drawSelf(std::vector<std::vector<char*>> texture) {
	for (int y = 0; y < getHeigth(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			std::cout << texture[x][y];
		}
		std::cout << std::endl;
	}
}
int Player::getHeigth() const {
	return this->heigth;
}

int Player::getWidth() const {
	return this->width;
}
*/