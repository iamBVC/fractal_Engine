/*
 * lcd->c
 *
 *  Created on: Mar 1, 2022
 *      Author: Brian
 */

#include "lcd_wrapper.h"
#include "../UTILS/utils.h"
#include "stdlib.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "string.h"



namespace LCD {

	bool init(lcd_t* lcd) {
		lcd->buffer = (uint32_t*)malloc(lcd->params.width * lcd->params.height * sizeof(uint32_t));
		if (lcd->buffer)
			return true;
		else
			return false;
	}

	void write(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data) {
		lcd->ops.WRITE_fn(lcd, 0, 0, lcd->params.width - 1, lcd->params.height - 1, lcd->buffer);
	}

	void print(lcd_t* lcd) {
		lcd->ops.PRINT_fn(lcd);
	}

	void clear(lcd_t* lcd) {
		memset(lcd->buffer, 0, lcd->params.height * lcd->params.width * sizeof(uint32_t));
		lcd->ops.CLEAR_fn(lcd);
	}

	void clear_buffer(lcd_t* lcd) {
		memset(lcd->buffer, 0, lcd->params.width * lcd->params.height * sizeof(uint32_t));
	}

	void draw_pixel(lcd_t* lcd, int32_t x, int32_t y, uint32_t color) {
		if (x >= lcd->params.width || y >= lcd->params.height || x < 0 || y < 0) {
			return;
		}

		lcd->buffer[(y * lcd->params.width) + x] = color;
	}


	void fill_rect(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) {

		if (x1 > x2) {
			uint16_t temp = x2;
			x2 = x1;
			x1 = temp;
		}
		if (y1 > y2) {
			uint16_t temp = y2;
			y2 = y1;
			y1 = temp;
		}

		if (x1 >= lcd->params.width) return;
		if (x2 >= lcd->params.width) x2 = lcd->params.width - 1;
		if (y1 >= lcd->params.height) return;
		if (y2 >= lcd->params.height) y2 = lcd->params.height - 1;
		if (x1 < 0) x1 = 0;
		if (y1 < 0) y1 = 0;
		if (x2 < 0) return;
		if (y2 < 0) return;

		for (int32_t y = y1; y <= y2; y++) {
			for (int32_t x = x1; x <= x2; x++) {
				draw_pixel(lcd, x, y, color);
			}
		}
	}





	void draw_line(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) {

		float dx = (float)x2 - (float)x1;
		float dy = (float)y2 - (float)y1;
		float inc;

		if (fabsf(dx) >= fabsf(dy)) {

			float diff = fabsf(dy / (float)lcd->params.height);
			if (diff > 1.0f) {
				dx /= diff;
				dy /= diff;
			}

			dy /= dx;
			inc = dx / fabsf(dx);
			for (float i = 0; i <= fabsf(dx); i++) {
				draw_pixel(lcd, x1 + (int32_t)(inc * i), y1 + (int32_t)(dy * i * inc), color);
			}
		}
		else {

			float diff = fabsf(dx / (float)lcd->params.width);
			if (diff > 1.0f) {
				dx /= diff;
				dy /= diff;
			}

			dx /= dy;
			inc = dy / fabsf(dy);
			for (float i = 0; i <= fabsf(dy); i++) {
				draw_pixel(lcd, x1 + (int32_t)(dx * i * inc), y1 + (int32_t)(inc * i), color);
			}
		}
	}

	void draw_rect(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) {
		draw_line(lcd, x1, y1, x2, y1, color);
		draw_line(lcd, x2, y1, x2, y2, color);
		draw_line(lcd, x1, y2, x2, y2, color);
		draw_line(lcd, x1, y1, x1, y2, color);
	}

	void draw_circle(lcd_t* lcd, int32_t x, int32_t y, uint32_t radius, uint32_t color) {
		float inc;
		if (radius == 0)
			inc = 360.0;
		else
			inc = 30.0f / (float)radius;
		for (float phi = 0.0; phi < 360.0; phi += inc) {
			int32_t dx = (int32_t)(radius * cos(phi * M_PI / 180.0));
			int32_t dy = (int32_t)(radius * sin(phi * M_PI / 180.0));
			draw_pixel(lcd, x + dx, y + dy, color);
		}
	}

	void draw_triangle(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {
		draw_line(lcd, x1, y1, x2, y2, color);
		draw_line(lcd, x2, y2, x3, y3, color);
		draw_line(lcd, x3, y3, x1, y1, color);
	}



	void fill_circle(lcd_t* lcd, int32_t x, int32_t y, uint32_t radius, uint32_t color) {
		for (uint32_t r = 0; r < radius; r++)
			draw_circle(lcd, x, y, r, color);
	}

	void fill_triangle(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {

		int32_t maxX = Utils::max_s(x1, Utils::max_s(x2, x3));
		int32_t minX = Utils::min_s(x1, Utils::min_s(x2, x3));
		int32_t maxY = Utils::max_s(y1, Utils::max_s(y2, y3));
		int32_t minY = Utils::min_s(y1, Utils::min_s(y2, y3));

		if ((minX < 0 && maxX < 0) || (minY < 0 && maxY < 0)) {
			return;
		}
		if ((minX >= lcd->params.width && maxX >= lcd->params.width) || (minY >= lcd->params.height && maxY >= lcd->params.height)) {
			return;
		}

		int32_t vs1x = x2 - x1;
		int32_t vs1y = y2 - y1;
		int32_t vs2x = x3 - x1;
		int32_t vs2y = y3 - y1;

		for (int32_t x = minX; x <= maxX; x++) {
			for (int32_t y = minY; y <= maxY; y++) {

				int32_t vx = x - x1;
				int32_t vy = y - y1;

				float s = (float)((vx * vs2y) - (vy * vs2x)) / (float)((vs1x * vs2y) - (vs1y * vs2x));
				float t = (float)((vs1x * vy) - (vs1y * vx)) / (float)((vs1x * vs2y) - (vs1y * vs2x));

				if ((s >= 0.0f) && (t >= 0.0f) && (s + t <= 1.0f)) {
					draw_pixel(lcd, x, y, color);
				}
			}
		}
	}

	void draw_text(lcd_t* lcd, int32_t x, int32_t y, const GFXfont font, char* text, uint32_t color) {
		for (uint16_t i = 0; i < strlen(text); i++) {

			text[i] -= font.first;
			GFXglyph* glyph = &(font.glyph[(unsigned char)text[i]]);
			uint8_t* bitmap = font.bitmap;

			uint16_t bo = glyph->bitmapOffset;
			uint8_t  w = glyph->width,
				h = glyph->height;
			int8_t   xo = glyph->xOffset,
				yo = glyph->yOffset;
			uint8_t  xx, yy, bits = 0, bit = 0;

			for (yy = h; yy > 0; yy--) {
				for (xx = 0; xx < w; xx++) {
					if (!(bit++ & 0x07)) {
						bits = bitmap[bo++];
					}
					if (bits & 0x80) {
						draw_pixel(lcd, x + xo + xx, y + yo + yy, color);
					}
					bits <<= 1;
				}
			}
			x += w;
		}
	}

	void draw_image(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data) {

		if (x1 > x2) {
			int32_t temp = x2;
			x2 = x1;
			x1 = temp;
		}
		if (y1 > y2) {
			int32_t temp = y2;
			y2 = y1;
			y1 = temp;
		}

		if (x1 >= lcd->params.width) return;
		if (x2 >= lcd->params.width) x2 = lcd->params.width - 1;
		if (y1 >= lcd->params.height) return;
		if (y2 >= lcd->params.height) y2 = lcd->params.height - 1;

		int32_t pixelCnt = 0;
		for (int32_t y = y1; y <= y2; y++) {
			for (int32_t x = x1; x <= x2; x++) {
				draw_pixel(lcd, x, y, data[pixelCnt]);
				pixelCnt++;
			}
		}
	}




}