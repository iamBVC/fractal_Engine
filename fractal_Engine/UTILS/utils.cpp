/*
 * utils.c
 *
 *  Created on: Feb 25, 2022
 *      Author: Brian
 */


#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

namespace Utils
{
	//minimum value between two uint32_t
	uint32_t min_u(uint32_t a, uint32_t b) {
		if (a < b) {
			return a;
		}
		else {
			return b;
		}
	}

	//minimum value between two float
	float min_f(float a, float b) {
		if (a < b) {
			return a;
		}
		else {
			return b;
		}
	}

	//minimum value between two int32_t
	int32_t min_s(int32_t a, int32_t b) {
		if (a < b) {
			return a;
		}
		else {
			return b;
		}
	}


	//maximum value between two uint32_t
	uint32_t max_u(uint32_t a, uint32_t b) {
		if (a > b) {
			return a;
		}
		else {
			return b;
		}
	}

	//maximum value between two float
	float max_f(float a, float b) {
		if (a > b) {
			return a;
		}
		else {
			return b;
		}
	}

	//maximum value between two int32_t
	int32_t max_s(int32_t a, int32_t b) {
		if (a > b) {
			return a;
		}
		else {
			return b;
		}
	}


	void swap_uint16_t(uint16_t* a, uint16_t* b) {
		uint16_t* temp = b;
		b = a;
		a = temp;
	}


	char* byte_to_binary(uint8_t byte) {
		static char text[8];
		for (uint8_t i = 0; i < 8; i++)
			text[7 - i] = (byte & (1 << i) ? '1' : '0');
		return text;
	}




	uint32_t rgb332_to_rgb888(uint8_t color) {
		uint32_t rgb888 = ((uint32_t)(color & 0b11100000) << 16) | ((uint32_t)(color & 0b00011100) << 11) | ((uint32_t)(color & 0b00000011) << 6);
		return rgb888;
	}

	void fill_rgb888_from_rgb332(uint8_t** buf, uint8_t color) {
		uint8_t* tmpbuf = (uint8_t*)malloc(sizeof(&buf));
		for (uint16_t i = 0; i < sizeof(&buf); i += 3) {
			tmpbuf[i + 0] = (color & 0b11100000) << 0;
			tmpbuf[i + 1] = (color & 0b00011100) << 3;
			tmpbuf[i + 2] = (color & 0b00000011) << 6;
		}
		free(*buf);
		*buf = tmpbuf;
	}



	uint32_t HSVtoRGB(float H, float S, float V) {
		float s = S / 100.0f;
		float v = V / 100.0f;
		float C = s * v;
		float X = C * (1.0f - roundf(fmodf(H / 60.0f, 2.0f) - 1.0f));
		float m = v - C;

		float r_value = 0.0f;
		float g_value = 0.0f;
		float b_value = 0.0f;

		if (H >= 0 && H < 60) {
			r_value = C;
			g_value = X;
			b_value = 0.0;
		}
		else if (H >= 60 && H < 120) {
			r_value = X;
			g_value = C;
			b_value = 0.0;
		}
		else if (H >= 120 && H < 180) {
			r_value = 0.0;
			g_value = C;
			b_value = X;
		}
		else if (H >= 180 && H < 240) {
			r_value = 0.0;
			g_value = X;
			b_value = C;
		}
		else if (H >= 240 && H < 300) {
			r_value = X;
			g_value = 0.0;
			b_value = C;
		}
		else {
			r_value = C;
			g_value = 0.0;
			b_value = X;
		}

		uint32_t out = 0;
		out += ((uint8_t)((r_value + m) * 255.0)) << 16;
		out += ((uint8_t)((g_value + m) * 255.0)) << 8;
		out += ((uint8_t)((b_value + m) * 255.0)) << 0;
		return out;
	}




}