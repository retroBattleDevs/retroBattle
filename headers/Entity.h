#pragma once
#include "headers/Vec2D.h"

#include <iostream>
#include "external_libraries/PDCurses/curses.h"
#include "headers/MersenneTwister.h"
#include "headers/movements/RandomMovement.h"

namespace EntityTypes {
	enum Type {
		Player,
		Enemy,
		Entity
	};
}

class Entity {

protected:
	static int nextId;
	int id;

	int health;
	int	hitPoints;
	int	attack;
	int defence;
	int speed;

	//vars for buffs ranging from -5 to 5 stating from 0
	//1 represends 20% stat increase
	//-1 represends -20% stat decrease
	//5 -> 100% (double)
	//-5 -> -100% (zero)
	//for example entity has 10 attack and buffStage 2,
	//final attack will be 10+(10 * (20% * 2)) = 10+4 = 4
	//At the start of each battle the BuffStages are set to 0
	int attackBuffStage;
	int defenceBuffStage;
	int speedBuffStage;

	Vec2d direction;

public:

	Entity();
	Entity(int id, const int width, const int height, Vec2d position);

	Vec2d getPosition() const;
	Vec2d getMin() const;
	Vec2d getMax() const;
	int getId() const;

	void setPosition(Vec2d newPosition);
	void setMin(Vec2d newMin);
	void setMax(Vec2d newMax);
	void setId(int newId); 

	virtual EntityTypes::Type getType() const;

	//Rule of Five
	virtual ~Entity();
	Entity(const Entity& other);
	Entity& operator=(const Entity& other);
	Entity(Entity&& other) noexcept;
	Entity& operator=(Entity&& other) noexcept;

	int getHealth() const;
	int	getHitPoints() const;
	int	getAttack() const;
	int getDefence() const;
	int getSpeed() const;
	void setHealth(int h);
	void setHitPoints(int hp);
	void setAttack(int a);
	void setDefence(int d);
	void setSpeed(int s);

	virtual void drawSelf() const = 0;
	void drawBoundingBox() const;
	void move(Vec2d delta);
	void takeDamage(int damage);
	void heal(int amount);
	bool isAlive() const;

	//buff methods
	void modifyAttackBuffStage(int amount);
	void modifyDefenceBuffStage(int amount);
	void modifySpeedBuffStage(int amount);
	void resetBuffStages();
	float getStatMultiplier(int stage) const;
	int getFinalAttack() const;
	int getFinalDefence() const;
	int getFinalSpeed() const;

	Vec2d position;
	Vec2d min;
	Vec2d max;
	Vec2d size;
	Vec2d getDirection() const;
	MersenneTwister* rng;

	Movement* movement;


	void updateBoundingBox();


};
