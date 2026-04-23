#include "retroBattle.h"

void keyDispatcher(metrics& mtr, const char c, EntityManager *mgr) {

	Entity *player = mgr->getPlayer();
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
			}
			else {
				mtr.displayWindow = 0;
				delwin(mtr.win);
				mtr.win = nullptr;
			}
		case 'b':
			mgr->showBoundingBox = (mgr->showBoundingBox == true) ? false : true;
    }
	player->setPosition(position);
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

	int x = 10, y = 10;

	float time_diff = 0;
	// Entity  
	Entity* player = new Player(1, Vec2d(3.0, 3.0), Vec2d(5.0, 5.0), Vec2d(30.0, 30.0));
	
	Entity* enemy1 = new Enemy(2, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(20.0, 20.0));
	Entity* enemy2 = new Enemy(3, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(20.0, 30.0));
	Entity* enemy3 = new Enemy(4, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(45.0, 15.0));
	//Entity enemy3(4, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(45.0, 15.0));
	//Entity enemy4(5, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(50.0, 20.0));

	std::vector<Entity*> entities = { player, enemy1 };
	EntityManager entityManager(entities);
	entityManager.add(enemy2);
	entityManager.add(enemy3);

	while (1) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		entityManager.renderAll();

		displayMetrics(mtr);

		// Collision detection and response goes here
		/*
		if (collisionDetectionBoundinBox(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Collision!!");
		}
		*/

		if (circleCollisionDetection(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Circle Collision!!");
		}

		// battle class test
		//test turn order with different speeds
		//BattleManager test;
		//Entity *enemy = entityManager.getEnemies()[0];
		//test.startBattle(entityManager.getPlayer(), enemy, 1);
		
		// Update Entities with new positions and update animations to be drawn at the next iteration goes here.
		mvprintw(0, 0, "y: %f    x: %f", entityManager.getPlayer()->getPosition().x, entityManager.getPlayer()->getPosition().y);

		mvprintw(1, 0, "Direction X: %.2f    Direction Y: %.2f",
			entityManager.getPlayer()->getDirection().x,
			entityManager.getPlayer()->getDirection().y);
		
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
	
	return 0;
}
