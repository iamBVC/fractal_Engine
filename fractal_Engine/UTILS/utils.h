/*
 * utils.h
 *
 *  Created on: Feb 25, 2022
 *      Author: Brian
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <stdint.h>

#define arraysize(x)	(size_t)(sizeof((x))/sizeof((x)[0]))



namespace Utils
{
	uint32_t min_u(uint32_t a, uint32_t b);
	float min_f(float a, float b);
	int32_t min_s(int32_t a, int32_t b);
	uint32_t max_u(uint32_t a, uint32_t b);
	float max_f(float a, float b);
	int32_t max_s(int32_t a, int32_t b);
	void swap_uint16_t(uint16_t* a, uint16_t* b);
	char* byte_to_binary(uint8_t byte);
	uint32_t rgb332_to_rgb888(uint8_t color);
	void fill_rgb888_from_rgb332(uint8_t** buf, uint8_t color);
	uint32_t HSVtoRGB(float H, float S, float V);
}


#endif /* UTILS_UTILS_H_ */
