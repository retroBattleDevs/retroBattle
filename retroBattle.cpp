#include "retroBattle.h"

void drawBox(int &y, int &x) {
	attron(COLOR_PAIR(1));
	mvprintw(y - 2, x - 2, "#####");
	mvprintw(y - 1, x - 2, "#   #");
	mvprintw(y, x - 2, "#   #");
	mvprintw(y + 1, x - 2, "#   #");
	mvprintw(y + 2, x - 2, "#####");
	attroff(COLOR_PAIR(1));
	mvprintw(y, x, "#");
}
void keyDispatcher(metrics &mtr, const char c, int &y, int &x) {
	switch (c) {
		case 'a':
			x--;
			break;
		case 'd':
			x++;
			break;
		case 'w':
			y--;
			break;
		case 's':
			y++;
			break;
		case 'm':
			if (!mtr.displayWindow) {
				mtr.displayWindow = 1;
			} else {
				mtr.displayWindow = 0;
				delwin(mtr.win);
				mtr.win = nullptr;
			}
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

	initPDCurses();

	metrics mtr = { 0 };
	initTimeCounter(mtr);

	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);


	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	int x = 10, y = 10;

	float time_diff = 0;
	while (1) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		drawBox(y, x);
		mvprintw(0, 0, "y: %d    x: %d", y, x);

		displayMetrics(mtr);

		int c = getch(stdin);
		keyDispatcher(mtr, c, y, x);

		// Collision detection and response goes here.

		// Update Entities with new positions and update animations to be drawn at the next iteration goes here.

		/* Sleep so much as we need to keep us at 60 fps. */
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		// clear screen
		wclear(stdscr);
	}

	endwin();

	return 0;
}