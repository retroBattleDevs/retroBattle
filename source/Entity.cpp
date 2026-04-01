#include "headers/Entity.h"

int Entity::nextId = 1;

Entity::Entity() {

	position = Vec2d(0, 0);
	min = Vec2d(0, 0);
	max = Vec2d(0, 0);
	id = nextId++;

	health = 100;
	hitPoints = 100;
	attack = 10;
	defence = 5;
}


// Testing Julian
Entity::Entity(int id, Vec2d min, Vec2d max, Vec2d position) {
	this->id = id;
	this->min = min;
	this->max = max;
	this->position = position;

	id = nextId++;
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

int Entity::getHealth() const{
	return this->health;
}

int Entity::getHitPoints() const {
	return this->hitPoints;
}

int Entity::getAttack() const {
	return this->attack;
}

int Entity::getDefence() const {
	return this->defence;
}


void Entity::setHealth(int h) {
	if (h < 0) h = 0;
	if (h > hitPoints) h = hitPoints;
	health = h;
}

void Entity::setHitPoints(int hp) {
	if (hp < 1) hp = 1; // mindestens 1

	hitPoints = hp;

	// health anpassen, falls zu hoch
	if (health > hitPoints) {
		health = hitPoints;
	}
}

void Entity::setAttack(int a) {
	if (a < 0) a = 0;
	attack = a;
}

void Entity::setDefence(int d) {
	if (d < 0) d = 0;
	defence = d;
}

void Entity::drawSelf() const {
	std::cout << "Entity ID: " << id << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
	std::cout << "Bounding Box Min: (" << min.x << ", " << min.y << ")\n";
	std::cout << "Bounding Box Max: (" << max.x << ", " << max.y << ")\n";
}


void Entity::drawTesting() const {
	attron(COLOR_PAIR(1));
	mvprintw(position.y - 2, position.x - 2, "#####");
	mvprintw(position.y - 1, position.x - 2, "#   #");
	mvprintw(position.y, position.x - 2, "#   #");
	mvprintw(position.y + 1, position.x - 2, "#   #");
	mvprintw(position.y + 2, position.x - 2, "#####");
	attroff(COLOR_PAIR(1));
	mvprintw(position.y, position.x, "#");
}
Vec2d Entity::getPosition() const {
	return position;
}

Vec2d Entity::getMin() const {
	return min;
}

Vec2d Entity::getMax() const {
	return max;
}

int Entity::getId() const {
	return id;
}

void Entity::setPosition(Vec2d newPosition) {
	position = newPosition;
}

void Entity::setMin(Vec2d newMin) {
	min = newMin;
}

void Entity::setMax(Vec2d newMax) {
	max = newMax;
}

void Entity::move(Vec2d delta) {
	position.x += delta.x;
	position.y += delta.y;
}
void Entity::takeDamage(int damage) {
	int actualDamage = damage - defence;
	if (actualDamage < 0) {
		actualDamage = 0;
	}

	health -= actualDamage;
	if (health < 0) {
		health = 0;
	}
}
void Entity::heal(int amount) {
	health += amount;
	if (health > hitPoints) {
		health = hitPoints;
	}
}
bool Entity::isAlive()const {
	return health > 0;
}