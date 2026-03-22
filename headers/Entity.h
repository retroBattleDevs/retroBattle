#pragma once
#include "headers/Vec2D.h"

class Entity {

protected:
	Vec2d position;
	Vec2d min;
	Vec2d max;
	int id;


	int health;
	int	hitPoints;
	int	attack;
	int defence;

public:
	Entity();
	//Rule of Five
	virtual ~Entity();
	Entity(const Entity& other);
	Entity& operator=(const Entity& other);
	Entity(Entity&& other) noexcept;
	Entity& operator=(Entity&& other) noexcept;

	int getHealth();
	int	getHitPoints();
	int	getAttack();
	int getDefence();
	void setHealth(int h);
	void setHitPoints(int hp);
	void setAttack(int a);
	void setDefence(int d);

	virtual void drawSelf() const = 0;

};
