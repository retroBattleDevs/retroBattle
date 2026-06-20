#include "headers/draw_funcs.h"

void clearScreen() {
	std::cout << "\x1b[H\x1b[J";
}

void drawDoricColumn(void) {
	char columns[30] = "\x1b[38;5;46m";
	char walls[30] = "\x1b[38;5;104m";
	char reset[30] = "\x1b[0m";
	std::cout << "\\\x1b[38;5;46m_______________\x1b[0m           \\        \\           \\           \\                                 /             /             /      /          \x1b[38;5;46m_______________\x1b[0m/" << std::endl;
	std::cout << "\x1b[38;5;46m|               |\x1b[0m\\__________\\        \\           \\           \\                               /             /             /      /_________/\x1b[38;5;46m|               |\x1b[0m" << std::endl;
	std::cout << "\x1b[38;5;46m|               |\x1b[0m            \\________\\           \\           \\                             /             /             /______/           \x1b[38;5;46m|               |\x1b[0m" << std::endl;
	std::cout << " \x1b[38;5;46m---------------\x1b[0m                       \\___________\\           \\                           /             /_____________/                    \x1b[38;5;46m---------------\x1b[0m " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                      \\___________\\                         /_____________/                                     \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                   \\_______________________/                                                    \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                       \x1b[38;5;46m|_____|\x1b[0m    \x1b[38;5;46m|_____|\x1b[0m                                                       \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                         \x1b[38;5;46m|||\x1b[0m        \x1b[38;5;46m|||\x1b[0m                                                         \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                                    ___\x1b[38;5;46m|_____|\x1b[0m    \x1b[38;5;46m|_____|\x1b[0m___                                                    \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                              ____/         /\x1b[48;5;196m      \x1b[0m\\         \\____                                              \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                         ____/             /\x1b[48;5;196m        \x1b[0m\\              \\____                                        \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                                    ____/                 /\x1b[48;5;196m          \x1b[0m\\                   \\____                                  \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                               ____/                     /\x1b[48;5;196m            \x1b[0m\\                        \\____                            \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                          ____/                         /\x1b[48;5;196m              \x1b[0m\\                             \\____                      \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                     ____/                             /\x1b[48;5;196m                \x1b[0m\\                                  \\____                \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m                ____/                                 /\x1b[48;5;196m                  \x1b[0m\\                                       \\____          \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m           ____/                                     /\x1b[48;5;196m                    \x1b[0m\\                                            \\____    \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m      ____/                                         /\x1b[48;5;196m                      \x1b[0m\\                                                 \\__\x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << "   \x1b[38;5;46m| | | | | |\x1b[0m ____/                                             /\x1b[48;5;196m                        \x1b[0m\\                                                   \x1b[38;5;46m| | | | | |\x1b[0m   " << std::endl;
	std::cout << " \x1b[38;5;46m_______________\x1b[0m                                                /\x1b[48;5;196m                          \x1b[0m\\                                                \x1b[38;5;46m_______________\x1b[0m " << std::endl;
	std::cout << "\x1b[38;5;46m|               |\x1b[0m                                              /\x1b[48;5;196m                            \x1b[0m\\                                              \x1b[38;5;46m|               |\x1b[0m" << std::endl;
	std::cout << "\x1b[38;5;46m|               |\x1b[0m                                             /\x1b[48;5;196m                              \x1b[0m\\                                             \x1b[38;5;46m|               |\x1b[0m" << std::endl;
	std::cout << " \x1b[38;5;46m---------------\x1b[0m                                             /\x1b[48;5;196m________________________________\x1b[0m\\                                             \x1b[38;5;46m---------------\x1b[0m " << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|\x1b[48;5;196m                                  \x1b[0m|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

	//std::cout << "\x1b[0;156HMax Width" << std::endl;
	//std::cout << "\x1b[39;0HMax Height" << std::endl;
}

void drawLogo(const int x, const int y) {
	clearScreen();
	drawDoricColumn();
	std::cout << "\x1b[" << y - 6 << ";" << x << "H" << "      ______________                    __________           ";
	std::cout << "\x1b[" << y - 5 << ";" << x << "H" << "     |              |                  |          |___       ";
	std::cout << "\x1b[" << y - 4 << ";" << x << "H" << "     |____      ____|                  |___    ___|   |      ";
	std::cout << "\x1b[" << y - 3 << ";" << x << "H" << " ______ __|_   |______    ______      _____|__|_|  ___|      ";
	std::cout << "\x1b[" << y - 2 << ";" << x << "H" << "|  _   |    |  |   _  |  |   _  |  __|        |  ||__        ";
	std::cout << "\x1b[" << y - 1 << ";" << x << "H" << "|  |_| | ___|  |  |_| |  |  |_| | /  \\__    __|  | __|      ";
	std::cout << "\x1b[" << y     << ";" << x << "H" << "|   ___||_|    |   ___|__|   ___;/ /\\ \\ |  |  |  ||___     ";
	std::cout << "\x1b[" << y + 1 << ";" << x << "H" << "|   \\ |  __|   |   \\|  _  | ´---.      \\|  |  |  |    |   ";
	std::cout << "\x1b[" << y + 2 << ";" << x << "H" << "| ^  \\| |_|_   | ^  \\ | | | .-.  | /\\   \\  |  |  |___ |  ";
	std::cout << "\x1b[" << y + 3 << ";" << x << "H" << "| |\\  \\     |  | |\\  \\|_| | |_|  |/  \\   \\ |  |      | ";
	std::cout << "\x1b[" << y + 4 << ";" << x << "H" << "|_| \\__\\____|__|_| \\__\\___|______|    \\___\\|__|______| ";
	std::cout << "\x1b[" << y + 5 << ";" << x << "H" << "                  \x1b[?25l\x1b[5m\x1b[32mPress Enter to continue\x1b[0m\x1b[25m";
	std::cout << "\x1b[" << y + 6 << ";" << x << "H" << "\x1b[8m";
	if (getchar()) return;
}

void drawCollisionAnimation(){
	int _rows = 0;
	int _cols = 0;
	getmaxyx(stdscr, _rows, _cols);
	attron(COLOR_PAIR(3));
	for(int i = 1; i < _rows - 2; i++){
		mvprintw(i, 1, std::string(_cols - 2, '#').c_str());
		refresh();
		Sleep(15);

	}
	attroff(COLOR_PAIR(3));
	//emty the input stream
	while(getch(stdin) != -1){}
}
