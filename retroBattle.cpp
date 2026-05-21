#include "retroBattle.h"

int RUNNING = 1;

void keyDispatcher(metrics& mtr, const char c, Terrain *terrain, EntityManager *mgr) {

	Player *player = static_cast<Player*>(mgr->getPlayer());
	Vec2d position = player->getPosition();

	switch (c) {
		case 'a':
			position.x--;
			break;
		case 'd':
			position.x++;
			break;
		case 'w':
			position.y--;
			break;
		case 's':
			position.y++;
			break;
		case 'm':
			if (!mtr.displayWindow) {
				mtr.displayWindow = 1;
				displayMetrics(mtr);
			} else {
				hideMetrics(mtr);
			}
			break;
		case 'b':
			mgr->showBoundingBox = (mgr->showBoundingBox == true) ? false : true;
			break;
		case 'x':
			if (displayDialog()) {
				clearScreen();
				exit(0);
			}
			return;
		case 'i':
			if (!player->showStats) {
				player->showStats = 1;
				player->displayStats();
			} else {
				player->hideStats();
			}
			break;
    }

	player->roomCheck(terrain, position);

	if (terrain->room[player->terrain_room_x][player->terrain_room_x].entity_manager->canWalkTo(player, position)) {
		player->setPosition(position);
	}
}
void initWindowsAPI(void) {
	HWND hwnd = GetConsoleWindow();
	HWND owner = GetWindow(hwnd, GW_OWNER);
	SendMessage(owner, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	Sleep(10);
}
void initPDCurses(void) {
	initscr();
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	if (has_colors()) {
		start_color();
	}
}
int main() {
	using namespace std;
	
	initWindowsAPI();
	drawLogo(50, 20);
	initPDCurses();

	metrics mtr = { 0 };
	initTimeCounter(mtr);

	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);

	//color pairs
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_CYAN);
	init_pair(6, COLOR_BLACK, COLOR_RED);

	init_color(BROWN_COLOR, 867, 718, 527);
	init_color(LIGHT_GREEN_COLOR, 714, 917, 203);
	init_pair(7, BROWN_COLOR, COLOR_BLACK);
	init_pair(8, LIGHT_GREEN_COLOR, COLOR_BLACK);

	int x = 10, y = 10;

	float time_diff = 0;

	//GateKeeper
	MersenneTwister tempRng;
	int randX = tempRng.getRandomNumber(5, _cols - 5);
	int randY = tempRng.getRandomNumber(5, _rows - 5);
	GateKeeper* gateKeeper = new GateKeeper(7, 5, 5, Vec2d(randX, randY));

	Player* player = new Player(1, 5, 5, Vec2d(30.0, 30.0));
	Enemy* enemy1 = new Enemy(2, 5, 5, Vec2d(60.0, 20.0));
	Enemy* enemy2 = new Enemy(3, 5, 5, Vec2d(20.0, 30.0));
	Enemy* enemy3 = new Enemy(4, 5, 5, Vec2d(45.0, 15.0));
	Enemy* enemy4 = new Enemy(2, 5, 5, Vec2d(100.0, 20.0));
	Enemy* enemy5 = new Enemy(3, 5, 5, Vec2d(120.0, 30.0));
	Enemy* enemy6 = new Enemy(4, 5, 5, Vec2d(145.0, 15.0));
	enemy1->movement = new ChaseMovement(player, enemy1);
	enemy2->movement = new ChaseMovement(player, enemy2);
	enemy3->movement = new ChaseMovement(player, enemy3);
	enemy4->movement = new ChaseMovement(player, enemy4);
	enemy5->movement = new ChaseMovement(player, enemy5);
	enemy6->movement = new ChaseMovement(player, enemy6);
	std::vector<Entity*> entities = { player, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, gateKeeper};
	BattleManager battleManager;

	Room startRoom = Room(_cols, _rows);
	startRoom.entity_manager = new EntityManager(entities);

	// up room #####################################################
	std::vector<Entity*> upRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	Room upRoom = Room(_cols, _rows);
	upRoom.entity_manager = new EntityManager(upRoomEntities);

	// down room ###################################################
	std::vector<Entity*> downRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	Room downRoom = Room(_cols, _rows);
	downRoom.entity_manager = new EntityManager(downRoomEntities);

	// left room ###################################################
	std::vector<Entity*> leftRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	Room leftRoom = Room(_cols, _rows);
	leftRoom.entity_manager = new EntityManager(leftRoomEntities);

	// right room ##################################################
	std::vector<Entity*> rightRoomEntities = {
		new Enemy(2, 5, 5, Vec2d(60.0, 20.0)),
		new Enemy(2, 5, 5, Vec2d(100.0, 30.0)),
		new Enemy(2, 5, 5, Vec2d(10.0, 15.0))
	};
	Room rightRoom = Room(_cols, _rows);
	rightRoom.entity_manager = new EntityManager(rightRoomEntities);


	Terrain terrain;
	terrain.room[1][1] = startRoom;
	terrain.room[1][0] = upRoom;
	terrain.room[1][2] = downRoom;
	terrain.room[0][1] = leftRoom;
	terrain.room[2][1] = rightRoom;

	while (true) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		terrain.room[player->terrain_room_x][player->terrain_room_y].drawSelf();
		terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->renderAll();

		displayMetrics(mtr);
		player->displayStats();

		// Collision detection and response goes here
		/*
		if (collisionDetectionBoundinBox(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Collision!!");
		}
		*/

		//GateKeeper collision
		if (circleCollisionDetection(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), { gateKeeper }).size() > 0) {
			int midY = _rows / 2;
			int midX = _cols / 2;

			mvprintw(midY, midX - 4, "YOU WON!");
			mvprintw(midY + 1, midX - 15, "Press any key to restart...");
			refresh();
			
			nodelay(stdscr, false);
			getch();
			nodelay(stdscr, true);

			terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer()->setPosition(Vec2d(30.0, 30.0));
			gateKeeper->setPosition(Vec2d(tempRng.getRandomNumber(5, _cols - 5), tempRng.getRandomNumber(5, _rows - 5)));
			continue;
		}
		
		// BattleManager Collision resolution.
		auto collider = circleCollisionDetection(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getEnemies());
		if (collider.size() > 0) {
			mvprintw(0, 40, "Circle Collision!!");

			//start battle and save result
			int battleResult = battleManager.startBattle(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), collider.front(), 1);

			//battle won
			if (battleResult == 1) {
				terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->removeEntity(collider.front());
			}
			//battle lost
			else{
				//end the program
				return 0;
			}			
		}
		
		refresh();

		int c = getch(stdin);
		keyDispatcher(mtr, c, &terrain, terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager);

		// Sleep so much as we need to keep us at 60 fps. 
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		// clear screen
		wclear(stdscr);
	}

	endwin();
	
	return 0;
}
