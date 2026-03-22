#pragma once
#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "headers/Entity.h"
#include <iostream>


class TestEntity : public Entity{
private:

public:
	TestEntity(int h, int hp, int a, int d);
	TestEntity(const TestEntity& other);
	TestEntity(const Entity& other);
	
	void drawSelf() const override;
};
#endif