#include "headers/terrain/Terrain.h"
#include "headers/Player.h"
#include "headers/enemies/Enemy.h"
#include "headers/Gatekeeper.h"
#include "headers/movements/ChaseMovement.h"
#include "headers/movements/GuardingMovement.h"
#include "headers/movements/RandomMovement.h"
#include "headers/enemies/Spider.h"
#include "headers/enemies/Snake.h"
#include "headers/textures/Animator.h"

Terrain::Terrain(AnimatorManager& animatorManager) : animatorManager(animatorManager) {
	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);

	// ########################  Main Room [1][1] ###############################
	Player* player = new Player(1, 5, 5, Vec2d((int)(_cols * 0.5), (int)(_rows * 0.5)), animatorManager.getAnimator("player"));
	Enemy* enemy1 = new Enemy(2, 5, 5, Vec2d(60.0, 20.0));
	Enemy* enemy2 = new Enemy(3, 5, 5, Vec2d(40.0, 30.0));
	Enemy* enemy3 = new Enemy(4, 5, 5, Vec2d(45.0, 15.0));
	Enemy* enemy4 = new Enemy(2, 5, 5, Vec2d(100.0, 20.0));
	Enemy* enemy5 = new Enemy(3, 5, 5, Vec2d(120.0, 30.0));
	Enemy* enemy6 = new Enemy(4, 5, 5, Vec2d(145.0, 15.0));
	Snake* slySnake = new Snake(101, 8, 1, Vec2d(30.0, 25.0));

	// Chase Movement Speed and Attack Radius can be modified via constructor!
	/*
		speed = how often is move method called without actually moving
		aggressionRadius = size of Radius
	*/
	int speed = 4;
	int aggressionRadius = 20;

	//enemy1->movement = new ChaseMovement(player, enemy1);
	enemy1->movement = new GuardingMovement(Vec2d(10, 5), Vec2d(123, 11));
	enemy2->movement = new ChaseMovement(player, enemy2, speed, aggressionRadius);
	enemy3->movement = new GuardingMovement(Vec2d(15, 30), Vec2d(50, 30.0));
	enemy4->movement = new GuardingMovement(Vec2d(5, 5), Vec2d(5, 30));
	enemy5->movement = new ChaseMovement(player, enemy5, speed, aggressionRadius);
	enemy6->movement = new ChaseMovement(player, enemy6, speed, aggressionRadius);
	slySnake->movement = new GuardingMovement(Vec2d(30.0, 25.0), Vec2d(60.0, 25.0));

	std::vector<Entity*> entities = { enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, player, slySnake };
	room[1][1] = Room(_cols, _rows);
	room[1][1].entity_manager = new EntityManager(entities);
	room[1][1].room_id = 11;
	room[1][1].spawnRelics();

	// ########################  Room [1][0] ###############################
	Spider* venomSpider = new Spider(99, 7, 5, Vec2d(20.0, 15.0));
	venomSpider->movement = new GuardingMovement(Vec2d(20.0, 15.0), Vec2d(45.0, 15.0));

	std::vector<Entity*> upRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0)),
		venomSpider
	};
	upRoomEntities[0]->movement = new RandomMovement();
	upRoomEntities[1]->movement = new RandomMovement();
	upRoomEntities[2]->movement = new RandomMovement();
	room[1][0] = Room(_cols, _rows);
	room[1][0].entity_manager = new EntityManager(upRoomEntities);
	room[1][0].room_id = 10;
	room[1][0].spawnRelics();

	// ########################  Room [1][2] ###############################
	std::vector<Entity*> downRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	downRoomEntities[1]->movement = new RandomMovement();
	room[1][2] = Room(_cols, _rows);
	room[1][2].entity_manager = new EntityManager(downRoomEntities);
	room[1][2].room_id = 12;
	room[1][2].spawnRelics();

	// ########################  Room [0][1] ###############################
	std::vector<Entity*> leftRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	leftRoomEntities[2]->movement = new RandomMovement();
	room[0][1] = Room(_cols, _rows);
	room[0][1].entity_manager = new EntityManager(leftRoomEntities);
	room[0][1].room_id = 1;
	room[0][1].spawnRelics();

	// ########################  Room [2][1] ###############################
	std::vector<Entity*> rightRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	rightRoomEntities[0]->movement = new RandomMovement();
	rightRoomEntities[1]->movement = new ChaseMovement(player, rightRoomEntities[1], speed, aggressionRadius);
	room[2][1] = Room(_cols, _rows);
	room[2][1].entity_manager = new EntityManager(rightRoomEntities);
	room[2][1].room_id = 21;
	room[2][1].spawnRelics();

	// ########################  Room [0][0] ###############################
	std::vector<Entity*> roomEntities_0_0 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 37.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_0_0[0]->movement = new RandomMovement();
	roomEntities_0_0[1]->movement = new ChaseMovement(player, roomEntities_0_0[1], speed, aggressionRadius);
	room[0][0] = Room(_cols, _rows);
	room[0][0].entity_manager = new EntityManager(roomEntities_0_0);
	room[0][0].room_id = 0;
	room[0][0].spawnRelics();

	// ########################  Room [0][2] ###############################
	std::vector<Entity*> roomEntities_0_2 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 37.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_0_2[1]->movement = new RandomMovement();
	roomEntities_0_2[2]->movement = new ChaseMovement(player, roomEntities_0_2[2], speed, aggressionRadius);
	room[0][2] = Room(_cols, _rows);
	room[0][2].entity_manager = new EntityManager(roomEntities_0_2);
	room[0][2].room_id = 2;
	room[0][2].spawnRelics();

	// ########################  Room [2][0] ###############################
	std::vector<Entity*> roomEntities_2_0 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 37.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_2_0[0]->movement = new RandomMovement();
	roomEntities_2_0[1]->movement = new ChaseMovement(player, roomEntities_2_0[1], speed, aggressionRadius);
	room[2][0] = Room(_cols, _rows);
	room[2][0].entity_manager = new EntityManager(roomEntities_2_0);
	room[2][0].room_id = 20;
	room[2][0].spawnRelics();

	// ########################  Room [2][2] ###############################
	std::vector<Entity*> roomEntities_2_2 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 37.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_2_2[0]->movement = new RandomMovement();
	roomEntities_2_2[1]->movement = new ChaseMovement(player, roomEntities_2_2[1], speed, aggressionRadius);
	room[2][2] = Room(_cols, _rows);
	room[2][2].entity_manager = new EntityManager(roomEntities_2_2);
	room[2][2].room_id = 22;
	room[2][2].spawnRelics();

	gateKeeper = nullptr;
	positionGatekeeper();
}

Terrain::~Terrain() {}

void Terrain::positionGatekeeper() {
	MersenneTwister rng;
	int x = rng.getRandomNumber(0, 2);
	int y = rng.getRandomNumber(0, 2);

	int _rows = 0, _cols = 0;
	getmaxyx(stdscr, _rows, _cols);
	int rastgeleX = rng.getRandomNumber(5, _cols - 5);
	int rastgeleY = rng.getRandomNumber(5, _rows - 5);

	gateKeeper = new GateKeeper(7, 5, 5, Vec2d(rastgeleX, rastgeleY));
	gatekeeperRoomX = x;
	gatekeeperRoomY = y;

	room[x][y].entity_manager->entities.push_back(gateKeeper);
}

void Terrain::removeGatekeeper() {
	if (gateKeeper == nullptr) return;

	auto& entityList = room[gatekeeperRoomX][gatekeeperRoomY].entity_manager->entities;

	for (int i = 0; i < entityList.size(); i++) {
		if (entityList[i] == gateKeeper) {
			entityList.erase(entityList.begin() + i);
			break;
		}
	}

	delete gateKeeper;
	gateKeeper = nullptr;
}