#ifndef DRAW_FUNCS_H
#define DRAW_FUNCS_H

#include <iostream>
#include "external_libraries/PDCurses/curses.h"

void clearScreen();
void drawDoricColumn(void);
void drawLogo(const int x, const int y);

#endif // !DRAW_FUNCS_H