#include "headers/Enemy.h"

Enemy::Enemy() : Entity() {}

Enemy::Enemy(int id, const int width, const int height, Vec2d position) : Entity(id, width, height, position) {
	movement = new RandomMovement();
}

Enemy::~Enemy() {
	delete movement;
}

EntityTypes::Type Enemy::getType() const {
	return EntityTypes::Type::Enemy;
}

void Enemy::drawSelf() const {
	attron(COLOR_PAIR(2));
	mvprintw(position.y - 1, position.x - 2, "\\_O_/");
	mvprintw(position.y,     position.x,        "H");
	mvprintw(position.y + 1, position.x - 1,    "/");
	mvprintw(position.y + 1, position.x + 1,    "\\");
	attroff(COLOR_PAIR(2));
}
