#include <iostream>
#include <Windows.h>
#include "external_libraries/PDCurses/curses.h"
#include <time.h>
#include <cstdint>

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
void keyDispatcher(const char c, int &y, int &x) {
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

	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);
	int centerY = _rows / 2,
		centerX = _cols / 2;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	int x = 10, y = 10;

	while (1) {

		// Drawing of the Entities goes here.
		drawBox(y, x);
		mvprintw(0, 0, "y: %d    x: %d", y, x);

		int c = getch(stdin);
		keyDispatcher(c, y, x);

		// Collision detection and response goes here.

		// Update Entities with new positions and update animations to be drawn at the next iteration goes here.
		wclear(stdscr);
	}

	endwin();

	return 0;
}