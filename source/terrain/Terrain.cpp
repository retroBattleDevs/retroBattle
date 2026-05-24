#include "headers/terrain/Terrain.h"
#include "headers/Player.h"
#include "headers/enemies/Enemy.h"
#include "headers/Gatekeeper.h"
#include "headers/movements/ChaseMovement.h"
#include "headers/movements/GuardingMovement.h"
#include "headers/movements/RandomMovement.h"
#include "headers/enemies/Spider.h"
#include "headers/enemies/Snake.h"

Terrain::Terrain() {
	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);

	// ########################  Main Room [1][1] ###############################
	MersenneTwister tempRng;
	int randX = tempRng.getRandomNumber(5, _cols - 5);
	int randY = tempRng.getRandomNumber(5, _rows - 5);
	GateKeeper *gatekeeper = new GateKeeper(7, 5, 5, Vec2d(randX, randY));

	Player* player = new Player(1, 5, 5, Vec2d(145.0, 30.0));
	Enemy* enemy1 = new Enemy(2, 5, 5, Vec2d(60.0, 20.0));
	Enemy* enemy2 = new Enemy(3, 5, 5, Vec2d(40.0, 30.0));
	Enemy* enemy3 = new Enemy(4, 5, 5, Vec2d(45.0, 15.0));
	Enemy* enemy4 = new Enemy(2, 5, 5, Vec2d(100.0, 20.0));
	Enemy* enemy5 = new Enemy(3, 5, 5, Vec2d(120.0, 30.0));
	Enemy* enemy6 = new Enemy(4, 5, 5, Vec2d(145.0, 15.0));
	Snake* slySnake = new Snake(101, 8, 1, Vec2d(30.0, 25.0));

	//enemy1->movement = new ChaseMovement(player, enemy1);
	enemy1->movement = new GuardingMovement(Vec2d(10, 5), Vec2d(123, 11));
	enemy2->movement = new ChaseMovement(player, enemy2);
	enemy3->movement = new GuardingMovement(Vec2d(15, 30), Vec2d(50, 30.0));
	enemy4->movement = new GuardingMovement(Vec2d(5, 5), Vec2d(5, 30));
	enemy5->movement = new ChaseMovement(player, enemy5);
	enemy6->movement = new ChaseMovement(player, enemy6);
	slySnake->movement = new GuardingMovement(Vec2d(30.0, 25.0), Vec2d(60.0, 25.0));

	std::vector<Entity*> entities = { enemy1, enemy2, enemy3, enemy4,/* enemy5, enemy6, */ gatekeeper, player, slySnake };
	room[1][1] = Room(_cols, _rows);
	room[1][1].entity_manager = new EntityManager(entities);

	// ########################  Room [1][0] ###############################
	Spider* venomSpider = new Spider(99, 7, 5, Vec2d(20.0, 15.0));
	venomSpider->movement = new GuardingMovement(Vec2d(20.0, 15.0), Vec2d(25.0, 15.0));

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

	// ########################  Room [1][2] ###############################
	std::vector<Entity*> downRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	downRoomEntities[1]->movement = new RandomMovement();
	room[1][2] = Room(_cols, _rows);
	room[1][2].entity_manager = new EntityManager(downRoomEntities);

	// ########################  Room [0][1] ###############################
	std::vector<Entity*> leftRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	leftRoomEntities[2]->movement = new RandomMovement();
	room[0][1] = Room(_cols, _rows);
	room[0][1].entity_manager = new EntityManager(leftRoomEntities);

	// ########################  Room [2][1] ###############################
	std::vector<Entity*> rightRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	rightRoomEntities[0]->movement = new RandomMovement();
	rightRoomEntities[1]->movement = new ChaseMovement(player, rightRoomEntities[1]);
	room[2][1] = Room(_cols, _rows);
	room[2][1].entity_manager = new EntityManager(rightRoomEntities);

	// ########################  Room [0][0] ###############################
	std::vector<Entity*> roomEntities_0_0 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 38.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_0_0[0]->movement = new RandomMovement();
	roomEntities_0_0[1]->movement = new ChaseMovement(player, roomEntities_0_0[1]);
	room[0][0] = Room(_cols, _rows);
	room[0][0].entity_manager = new EntityManager(roomEntities_0_0);

	// ########################  Room [0][2] ###############################
	std::vector<Entity*> roomEntities_0_2 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 38.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_0_2[1]->movement = new RandomMovement();
	roomEntities_0_2[2]->movement = new ChaseMovement(player, roomEntities_0_2[1]);
	room[0][2] = Room(_cols, _rows);
	room[0][2].entity_manager = new EntityManager(roomEntities_0_2);

	// ########################  Room [2][0] ###############################
	std::vector<Entity*> roomEntities_2_0 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 38.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_2_0[0]->movement = new RandomMovement();
	roomEntities_2_0[1]->movement = new ChaseMovement(player, roomEntities_2_0[1]);
	room[2][0] = Room(_cols, _rows);
	room[2][0].entity_manager = new EntityManager(roomEntities_2_0);

	// ########################  Room [2][2] ###############################
	std::vector<Entity*> roomEntities_2_2 = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(120.0, 38.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	roomEntities_2_2[0]->movement = new RandomMovement();
	roomEntities_2_2[1]->movement = new ChaseMovement(player, roomEntities_2_2[1]);
	room[2][2] = Room(_cols, _rows);
	room[2][2].entity_manager = new EntityManager(roomEntities_2_2);
}

Terrain::~Terrain() {}