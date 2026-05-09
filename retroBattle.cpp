#include "retroBattle.h"

void keyDispatcher(metrics& mtr, const char c, EntityManager *mgr) {

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
			mgr->RUNNING = 0;
			break;
		case 'i':
			if (!player->showStats) {
				player->showStats = 1;
				player->displayStats();
			} else {
				player->hideStats();
			}
			break;
    }
	if (mgr->canWalkTo(player, position)) {
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

	int x = 10, y = 10;

	float time_diff = 0;

	Entity* player = new Player(1, 5, 5, Vec2d(30.0, 30.0));
	Entity* enemy1 = new Enemy(2, 5, 5, Vec2d(60.0, 20.0));
	Entity* enemy2 = new Enemy(3, 5, 5, Vec2d(20.0, 30.0));
	Entity* enemy3 = new Enemy(4, 5, 5, Vec2d(45.0, 15.0));
	Entity* enemy4 = new Enemy(2, 5, 5, Vec2d(100.0, 20.0));
	Entity* enemy5 = new Enemy(3, 5, 5, Vec2d(120.0, 30.0));
	Entity* enemy6 = new Enemy(4, 5, 5, Vec2d(145.0, 15.0));

	//GateKeeper
	MersenneTwister tempRng;
	int randX = tempRng.getRandomNumber(5, _cols - 5);
	int randY = tempRng.getRandomNumber(5, _rows - 5);
	Entity* gateKeeper = new GateKeeper(7, 5, 5, Vec2d(randX, randY));


	std::vector<Entity*> entities = { player, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, gateKeeper };
	EntityManager entityManager(entities);
	/*
	entityManager.add(enemy2);
	entityManager.add(enemy3);
	*/

	BattleManager battleManager;

	Room startRoom = Room(_cols, _rows);

	while (entityManager.RUNNING) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		startRoom.drawSelf();
		entityManager.renderAll();

		displayMetrics(mtr);
		static_cast<Player*>(player)->displayStats();

		// Collision detection and response goes here
		/*
		if (collisionDetectionBoundinBox(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Collision!!");
		}
		*/

		//GateKeeper collision
		if (circleCollisionDetection(entityManager.getPlayer(), { gateKeeper }) != nullptr) {
			int midY = _rows / 2;
			int midX = _cols / 2;

			mvprintw(midY, midX - 4, "YOU WON!");
			mvprintw(midY + 1, midX - 15, "Press any key to restart...");
			refresh();
			
			nodelay(stdscr, false);
			getch();
			nodelay(stdscr, true);

			entityManager.getPlayer()->setPosition(Vec2d(30.0, 30.0));
			gateKeeper->setPosition(Vec2d(tempRng.getRandomNumber(5, _cols - 5), tempRng.getRandomNumber(5, _rows - 5)));
			continue;
		}

		//check for collision
		Entity* collider = circleCollisionDetection(entityManager.getPlayer(), entityManager.getEnemies());
		if (collider != nullptr) {
			mvprintw(0, 40, "Circle Collision!!");

			//start battle and save result
			int battleResult = battleManager.startBattle(entityManager.getPlayer(), collider, 1);

			//battle won
			if (battleResult == 1) {
				entityManager.removeEntity(collider);
			}
			//battle lost
			else{
				//someting happens
			}			
		}	
		
		//mvprintw(0, 0, "_rows: %d    _cols: %d", _rows, _cols);
		refresh();

		int c = getch(stdin);
		keyDispatcher(mtr, c, &entityManager);

		// Sleep so much as we need to keep us at 60 fps. 
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		// clear screen
		wclear(stdscr);
	}

	endwin();
	clearScreen();
	
	return 0;
}
