#ifndef METRICS_H
#define METRICS_H

#include <Windows.h>
#include <iostream>
#include "external_libraries/PDCurses/curses.h"
#include <time.h>
#include <cstdint>

typedef struct metrics {
	float TimeCounter, LastFrameTimeCounter, deltaTime, prevTime, FPS;
	int Frame, displayWindow;
	struct timeval tv, tv0;
	WINDOW *win;
} metrics;

void displayMetrics(metrics &mtr);
void hideMetrics(metrics& mtr);
void usleep(const int usec);
void gettimeofday(struct timeval &tp, struct timezone *tzp);
void initTimeCounter(metrics &mtr);
void updateTimeCounter(metrics &mtr);
void calculateFPS(metrics &mtr);

#endif // !METRICS_H
