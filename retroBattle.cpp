#include <Windows.h>
#include "external_libraries/PDCurses/curses.h"

int main() {

	HWND hwnd = GetConsoleWindow();
	HWND owner = GetWindow(hwnd, GW_OWNER);
	SendMessage(owner, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	Sleep(10);

	initscr();

	if (has_colors()) {
		start_color();
	}

	int _rows = 0, _cols = 0;
	getmaxyx(stdscr, _rows, _cols);

	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	while (1) {

		move(40, _cols - 12);  // Rows and Columns in terminal are starting from position Zero.

		attron(COLOR_PAIR(1));
		printw("Hello World!");
		attroff(COLOR_PAIR(1));

		refresh();

		int c = getc(stdin);

		mvprintw(0, 0, "Terminal rows: %d\n", _rows);
		mvprintw(1, 0, "Terminal cols: %d\n", _cols);

		move(_rows / 2, _cols / 2); // Print to the center of the Screen.
		printw("entered: %c", c);
	}

	endwin();

	return 0;
}