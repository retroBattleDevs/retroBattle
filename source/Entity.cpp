#include "headers/Entity.h"
#include "headers/general_funcs.h"


int Entity::nextId = 1;

Entity::Entity() {

	position = Vec2d(0, 0);
	min = Vec2d(0, 0);
	max = Vec2d(0, 0);
	size = Vec2d(0, 0);
	id = nextId++;

	health = 100;
	hitPoints = 100;
	attack = 10;
	defence = 5;
	speed = 10;

	attackBuffStage = 0;
	defenceBuffStage = 0;
	speedBuffStage = 0;

	direction = Vec2d(0, 1);
	rng = new MersenneTwister();
	movement = nullptr;
}


// Testing Julian
Entity::Entity(int id, const int width, const int height, Vec2d position) {
	this->id = nextId++;
	size = Vec2d(width, height);
	this->min = position - (floorVec2d(size * 0.5));
	this->max = position + (floorVec2d(size * 0.5));

	this->position = position;


	health = 100;
	hitPoints = 100;
	attack = 10;
	defence = 5;
	speed = 10;

	attackBuffStage = 0;
	defenceBuffStage = 0;
	speedBuffStage = 0;

	direction = Vec2d(0, 1);
	rng = new MersenneTwister();
	movement = nullptr;
}

Entity::~Entity() {
	if (rng != nullptr)
	    delete rng;
};

Entity::Entity(const Entity& other) {
	position = other.position;
	min = other.min;
	max = other.max;
	size = other.size;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
	speed = other.speed;

	attackBuffStage = 0;
	defenceBuffStage = 0;
	speedBuffStage = 0;
	rng = other.rng;
	movement = other.movement;
}
Entity& Entity::operator=(const Entity& other) {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		size = other.size;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
		speed = other.speed;
		rng = other.rng;
		movement = other.movement;

		attackBuffStage = 0;
		defenceBuffStage = 0;
		speedBuffStage = 0;
	}
	return *this;
}
Entity::Entity(Entity&& other) noexcept {
	position = other.position;
	min = other.min;
	max = other.max;
	size = other.size;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
	speed = other.speed;
	rng = other.rng;
	movement = other.movement;

	attackBuffStage = 0;
	defenceBuffStage = 0;
	speedBuffStage = 0;
}
Entity& Entity::operator=(Entity&& other) noexcept {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		size = other.size;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
		speed = other.speed;
		rng = other.rng;
		movement = other.movement;

		attackBuffStage = 0;
		defenceBuffStage = 0;
		speedBuffStage = 0;
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

int Entity::getSpeed() const{
	return this->speed;
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

void Entity::setSpeed(int s){
	if (s < 0) s = 0;
	speed = s;
}

void Entity::drawBoundingBox() const {
	attron(COLOR_PAIR(1));
	int i = min.x;
	while (i <= max.x) {
		mvprintw(min.y, i, "#");
		mvprintw(max.y, i, "#");
		i++;
	}

	i = min.y;
	while (i <= max.y) {
		mvprintw(i, min.x, "#");
		mvprintw(i, max.x, "#");
		i++;
	}

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
	Vec2d diff = newPosition - position;
	if (diff.x != 0.0f || diff.y != 0.0f) {
		direction = diff;
		direction.normalize();
	}
	position = newPosition;

	min += diff;
	max += diff;
}

void Entity::setMin(Vec2d newMin) {
	min = newMin;
}

void Entity::setMax(Vec2d newMax) {
	max = newMax;
}

void Entity::move(Vec2d delta) {
	if (delta.x != 0.0f || delta.y != 0.0f) {
		direction = delta;
		direction.normalize();
	}

	position += delta;
	min += delta;
	max += delta;
}
void Entity::takeDamage(int damage) {
	int currentDef = getFinalDefence();
	int actualDamage = damage - currentDef;
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

void Entity::modifyAttackBuffStage(int amount){
	attackBuffStage += amount;
	if (attackBuffStage < -5)
		attackBuffStage = -5;
	if (attackBuffStage > 5)
		attackBuffStage = 5;
}

void Entity::modifyDefenceBuffStage(int amount){
	defenceBuffStage += amount;
	if (defenceBuffStage < -5)
		defenceBuffStage = -5;
	if (defenceBuffStage > 5)
		defenceBuffStage = 5;
}

void Entity::modifySpeedBuffStage(int amount){
	speedBuffStage += amount;
	if (speedBuffStage < -5)
		speedBuffStage = -5;
	if (speedBuffStage > 5)
		speedBuffStage = 5;
}

void Entity::resetBuffStages(){
	attackBuffStage = 0;
	speedBuffStage = 0;
	defenceBuffStage = 0;
}

float Entity::getStatMultiplier(int stage) const {
	return 1.0f + (stage * 0.20f);
}

int Entity::getFinalAttack() const {
	int final = (int)(attack * getStatMultiplier(attackBuffStage));
	return (final < 1) ? 1 : final;
}

int Entity::getFinalDefence() const {
	int final = (int)(defence * getStatMultiplier(defenceBuffStage));
	return (final < 1) ? 1 : final;
}

int Entity::getFinalSpeed() const {
	int final = (int)(speed * getStatMultiplier(speedBuffStage));
	return (final < 1) ? 1 : final;
}

EntityTypes::Type Entity::getType() const {
	return EntityTypes::Type::Entity;
}

Vec2d Entity::getDirection() const {
	return direction;
}