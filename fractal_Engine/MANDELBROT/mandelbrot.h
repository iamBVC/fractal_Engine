#pragma once

#include <stdint.h>



typedef struct {
	uint64_t iterations;
	double xCenter;
	double yCenter;
	double zoom;
}mandelbrot_params_t;


namespace Mandelbrot
{

	void Evaluate(mandelbrot_params_t* params, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer);
	void multithreadEvaluate(mandelbrot_params_t* params, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer);
}