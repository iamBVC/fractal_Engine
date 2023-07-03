#define _AMD64_
#include <sysinfoapi.h>
#include <windows.h>
#include "LCD/WinConsole.h"
#include "MANDELBROT/mandelbrot.h"
#include <math.h>

#define MIN_DRAW_TIME	50
#define MAX_DRAW_TIME	250

int main()
{
	//init output device
	lcd_t console = {};
	console.params.height = 9 * 60;
	console.params.width = 16 * 60;
	WinConsole::Init(&console);
	LCD::init(&console);


	double xCenter = -0.5;
	double yCenter = 0;

	double zoom = 1.0;

	uint32_t oldtime = GetTickCount();
	uint64_t IterationMax = 100;

	while (1) {

		bool inputPressed = false;
		if (GetKeyState(VK_ADD) & 0x8000)
		{
			zoom *= 0.9;
			inputPressed = true;
		}
		if (GetKeyState(VK_SUBTRACT) & 0x8000)
		{
			zoom /= 0.9;
			inputPressed = true;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			yCenter += zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			yCenter -= zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			xCenter += zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			xCenter -= zoom / 20;
			inputPressed = true;
		}


		Mandelbrot::multithreadEvaluate(IterationMax, xCenter, yCenter, zoom, 0, 0, console.params.width, console.params.height, console.params.width, console.params.height, console.buffer);

		uint32_t time = GetTickCount();
		uint32_t diff = time - oldtime;
		if (diff < MIN_DRAW_TIME) Sleep(MIN_DRAW_TIME - diff);
		LCD::print(&console);
		oldtime = GetTickCount();


		if (!inputPressed) {
			if ((diff < MAX_DRAW_TIME / 0.9) && (diff > MAX_DRAW_TIME * 0.9)) continue;
			IterationMax /= (4.0 / 5.0) + (diff / (MAX_DRAW_TIME * 5.0));
		}
		else {
			if ((diff < MIN_DRAW_TIME / 0.9) && (diff > MIN_DRAW_TIME * 0.9)) continue;
			IterationMax /= (4.0 / 5.0) + (diff / (MIN_DRAW_TIME * 5.0));
		}

		



	}

	return 0;
}
