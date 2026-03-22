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
	// Testing Julian
	Entity(int id, Vec2d min, Vec2d max, Vec2d position);
	void drawTesting() const;
	Vec2d getPosition() const;
	Vec2d getMin() const;
	Vec2d getMax() const;
	int getId() const;

	void setPosition(Vec2d newPosition);
	void setMin(Vec2d newMin);
	void setMax(Vec2d newMax);
	void setId(int newId); // fraglich ob das nötig ist


	//Rule of Five
	virtual ~Entity();
	Entity(const Entity& other);
	Entity& operator=(const Entity& other);
	Entity(Entity&& other) noexcept;
	Entity& operator=(Entity&& other) noexcept;

	void drawSelf() const;
};
