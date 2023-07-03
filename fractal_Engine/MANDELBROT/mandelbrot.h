#pragma once

#include <stdint.h>

namespace Mandelbrot
{

	void Evaluate(uint64_t iterations, double xCenter, double yCenter, double zoom, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer);
	void multithreadEvaluate(uint64_t iterations, double xCenter, double yCenter, double zoom, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer);
}