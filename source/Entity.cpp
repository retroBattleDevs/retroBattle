#include "headers/Entity.h"
#include <iostream>

Entity::Entity() {

	position = Vec2d(0, 0);
	min = Vec2d(0, 0);
	max = Vec2d(0, 0);
	id = 0;

	health = 100;
	hitPoints = 100;
	attack = 10;
	defence = 5;
}
Entity::~Entity() = default;

Entity::Entity(const Entity& other) {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
}
Entity& Entity::operator=(const Entity& other) {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
	}
	return *this;
}
Entity::Entity(Entity&& other) noexcept {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
}
Entity& Entity::operator=(Entity&& other) noexcept {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
	}
	return *this;
}

int Entity::getHealth() {
	return this->health;
}

int Entity::getHitPoints() {
	return this->hitPoints;
}

int Entity::getAttack() {
	return this->attack;
}

int Entity::getDefence() {
	return this->defence;
}

void Entity::setHealth(int h) {
	this->health = h;
}

void Entity::setHitPoints(int hp) {
	this->hitPoints = hp;
}

void Entity::setAttack(int a) {
	this->attack = a;
}

void Entity::setDefence(int d) {
	this->defence = d;
}

void Entity::drawSelf() const {
	std::cout << "Drawing Entity with ID" << id << std::endl;
}
