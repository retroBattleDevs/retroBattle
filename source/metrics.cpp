#include "headers/metrics.h"

void displayMetrics(metrics &mtr) {
	if (mtr.displayWindow) {
		if (mtr.win == nullptr) {
			mtr.win = subwin(stdscr, 5, 30, 1, 1);
		}
		wclear(mtr.win);
		box(mtr.win, 0, 0);
		mvwprintw(mtr.win, 1, 1, "FPS      : %f", mtr.FPS);
		mvwprintw(mtr.win, 2, 1, "deltaTime: %f", mtr.deltaTime);
		mvwprintw(mtr.win, 3, 1, "Frame    : %d", mtr.Frame);
	}
}
void hideMetrics(metrics& mtr) {
	mtr.displayWindow = 0;
	delwin(mtr.win);
	mtr.win = nullptr;
}
const static uint64_t epoch = ((uint64_t)116444736000000000ULL);
void usleep(const int usec) {
	HANDLE timer = 0;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanoseconds interval. Negative value indicates relative time.

	timer = CreateWaitableTimerA(NULL, TRUE, NULL);
	if (!timer)
		return;
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
/* Initializes the given timeval struct, to the time of the day, at the moment, at which this function was called. */
void gettimeofday(struct timeval &tp, struct timezone *tzp) {
	FILETIME file_time;
	SYSTEMTIME system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp.tv_sec = (uint64_t)((ularge.QuadPart - epoch) / 10000000L);
	tp.tv_usec = (uint64_t)(system_time.wMilliseconds * 1000);
}
/* Initializes the global timeval struct, to the time of the day, at the moment, at which this function was called. */
void initTimeCounter(metrics &mtr) {
	gettimeofday(mtr.tv0, NULL);
}
/* Counts how much time has passed since the first time that we casted gettimeofday(). */
void updateTimeCounter(metrics &mtr) {
	mtr.LastFrameTimeCounter = mtr.TimeCounter;
	gettimeofday(mtr.tv, NULL);
	mtr.TimeCounter = (float)(mtr.tv.tv_sec - mtr.tv0.tv_sec) + 0.000001 * ((float)(mtr.tv.tv_usec - mtr.tv0.tv_usec));
	mtr.deltaTime = mtr.TimeCounter - mtr.LastFrameTimeCounter;
}
void calculateFPS(metrics &mtr) {
	mtr.Frame++;
	if ((mtr.Frame % 60) == 0)
		mtr.FPS = 1.f / mtr.deltaTime;
	mtr.prevTime = mtr.TimeCounter;
}