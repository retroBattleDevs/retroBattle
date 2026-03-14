#pragma once
#include "Vec2d.h"

class Entity {

private:
	Vec2d position;
	Vec2d min;
	Vec2d max;
	int id;

public:
	Entity();
	//Rule of Five
	~Entity();
	Entity(const Entity& other);
	Entity& operator=(const Entity& other);
	Entity(Entity&& other) noexcept;
	Entity& operator=(Entity&& other) noexcept;

	virtual void drawSelf() const;

};