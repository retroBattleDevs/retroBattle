#include "headers/testEntity.h"

TestEntity::TestEntity(int h,int hp,int a,int d){
	setHealth(h);
	setAttack(a);
	setDefence(d);
	setHitPoints(hp);
}

TestEntity::TestEntity(const TestEntity& other) : Entity(other) {
	
}

TestEntity::TestEntity(const Entity& other) : Entity(other) {
	
}

void TestEntity::drawSelf() const{

}
