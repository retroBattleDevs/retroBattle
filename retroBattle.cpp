#include "retroBattle.h"

void keyDispatcher(metrics& mtr, const char c, Entity *player) {
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

	initPDCurses();

	metrics mtr = { 0 };
	initTimeCounter(mtr);

	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);


	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	int x = 10, y = 10;

	float time_diff = 0;
	// Entity
	Entity player(1, Vec2d(3.0, 3.0), Vec2d(5.0, 5.0), Vec2d(30.0, 30.0));
	
	Entity enemy(2, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(20.0, 20.0));
	Entity enemy2(3, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(20.0, 30.0));
	Entity enemy3(4, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(45.0, 15.0));
	Entity enemy4(5, Vec2d(10.0, 10.0), Vec2d(20.0, 20.0), Vec2d(50.0, 20.0));
	Entity enemies[4] = { enemy, enemy2, enemy3, enemy4 };

	while (1) {

		

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		player.drawTesting();
		enemy.drawTesting();
		enemy2.drawTesting();
		enemy3.drawTesting();
		enemy4.drawTesting();

		displayMetrics(mtr);

		// Collision detection and response goes here.
		bool collision = collisionDetectionBoundinBoxArray(&player, enemies);
		if (collision) {
			mvprintw(0,40, "Collision!!");
			//refresh();
		}

		if (collisionDetectionCircles(&player, &enemy) == true) {
			mvprintw(0, 40, "Circle Collision!!");
			//refresh();
		}

		// battle class test using temp entity child class
		BattleManager test;
		//test.startBattle(&player, &enemy, 2);
		

		// Update Entities with new positions and update animations to be drawn at the next iteration goes here.
		mvprintw(0, 0, "y: %f    x: %f", player.getPosition().x, player.getPosition().y);
		refresh();
		int c = getch(stdin);
		keyDispatcher(mtr, c, &player);

		// Sleep so much as we need to keep us at 60 fps. 
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		// clear screen
		wclear(stdscr);
	}

	endwin();
	
	return 0;
}