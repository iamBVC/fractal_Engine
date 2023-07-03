#define _AMD64_
#include <sysinfoapi.h>
#include <windows.h>
#include "LCD/WinConsole.h"
#include "MANDELBROT/mandelbrot.h"
#include <math.h>
#include <stdio.h>

#define MIN_DRAW_TIME	50
#define MAX_DRAW_TIME	250

int main()
{
	//init output device
	lcd_t console = {};
	console.params.height = 9 * 90;
	console.params.width = 16 * 90;
	WinConsole::Init(&console);
	LCD::init(&console);

	mandelbrot_params_t params = { 256, -0.5, 0, 1};

	uint32_t oldtime = GetTickCount();


	printf("\
arrows = move\n\
+- = change zoom\n\
D = toggle dynamic resolution\n\
H = increase quality\n\
N = decrease quality\n\
\n\nPress enter to start...");
	getchar();

	while (1) {


		bool inputPressed = false;
		if (GetKeyState(VK_ADD) & 0x8000)
		{
			params.zoom *= 0.9;
			inputPressed = true;
		}
		if (GetKeyState(VK_SUBTRACT) & 0x8000)
		{
			params.zoom /= 0.9;
			inputPressed = true;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			params.yCenter += params.zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			params.yCenter -= params.zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			params.xCenter += params.zoom / 20;
			inputPressed = true;
		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			params.xCenter -= params.zoom / 20;
			inputPressed = true;
		}


		
		Mandelbrot::multithreadEvaluate(&params, 0, 0, console.params.width, console.params.height, console.params.width, console.params.height, console.buffer);

		uint32_t time = GetTickCount();
		uint32_t diff = time - oldtime;
		if (diff < MIN_DRAW_TIME) Sleep(MIN_DRAW_TIME - diff);

		char buff[128];
		sprintf_s(buff, "X: %.10f   Y: %.10f   Z: %.10f", params.xCenter, params.yCenter, params.zoom);
		LCD::draw_text(&console, 20, 20, mono18x7, buff, WHITE);
		sprintf_s(buff, "I: %llu   T: %u ms", params.iterations, diff);
		LCD::draw_text(&console, 20, 50, mono18x7, buff, WHITE);

		LCD::print(&console);
		oldtime = GetTickCount();


		if (GetKeyState('H') & 0x8000)
		{
			params.iterations *= 1.2;
			continue;
		}

		if (GetKeyState('N') & 0x8000)
		{
			params.iterations *= 0.8;
			continue;
		}



		if (!GetKeyState('D'))
		{
			continue;
		}

		if (!inputPressed) {
			if ((diff < MAX_DRAW_TIME / 0.9) && (diff > MAX_DRAW_TIME * 0.9)) continue;
			params.iterations /= (3.0 / 4.0) + (diff / (MAX_DRAW_TIME * 4.0));
		}
		else {
			if ((diff < MIN_DRAW_TIME / 0.9) && (diff > MIN_DRAW_TIME * 0.9)) continue;
			params.iterations /= (3.0 / 4.0) + (diff / (MIN_DRAW_TIME * 4.0));
		}





	}

	return 0;
}
