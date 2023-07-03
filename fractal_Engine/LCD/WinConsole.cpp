/*
 * WinConsole.h
 *
 *  Created on: July 03, 2023
 *      Author: Brian
 */



#include "WinConsole.h"
#include <windows.h>
#include <wingdi.h>

namespace WinConsole
{

	void Write(void* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data)
	{

		BITMAPINFOHEADER bmih = { 0 };
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = x2 - x1 + 1;
		bmih.biHeight = y2 - y1 + 1;
		bmih.biPlanes = 1;
		bmih.biBitCount = 32;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = 10;
		bmih.biYPelsPerMeter = 10;

		BITMAPINFO dbmi = { 0 };
		dbmi.bmiHeader = bmih;

		SetDIBitsToDevice((HDC)((lcd_t*)(lcd))->HandlerPtr, x1, y1, x2-x1+1, y2-y1+1, 0, 0, 0, y2-y1+1, data, &dbmi, DIB_RGB_COLORS);

	}



	void Clear(void* lcd)
	{
		system("cls");
	}


	void Print(void* lcd)
	{
		Write(lcd, 0, 0, ((lcd_t*)(lcd))->params.width - 1, ((lcd_t*)(lcd))->params.height - 1, ((lcd_t*)(lcd))->buffer);
	}



	void Init(lcd_t* lcd)
	{
		HWND myconsole = GetConsoleWindow();
		lcd->HandlerPtr = GetDC(myconsole);
		lcd->ops.WRITE_fn = Write;
		lcd->ops.CLEAR_fn = Clear;
		lcd->ops.PRINT_fn = Print;
	}


}