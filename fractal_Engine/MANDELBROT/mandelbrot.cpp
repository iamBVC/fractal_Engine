#include "mandelbrot.h"
#include "../UTILS/utils.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

namespace Mandelbrot
{

	void Evaluate(mandelbrot_params_t* params, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer)
	{

		double Cx, Cy;
		double Zx, Zy;
		double Zx2, Zy2;
		double PixelWidth = (params->zoom * 2.0) / bufferWidth;
		double PixelHeight = (params->zoom * 2.0) / bufferHeight;


		for (uint32_t iY = y1; iY < y2; iY++) {
			Cy = (params->yCenter - params->zoom) + (iY * PixelHeight);
			if (fabs(Cy) < PixelHeight / 2.0) {
				Cy = 0.0; /* Main antenna */
			}

			for (uint32_t iX = x1; iX < x2; iX++) {

				Cx = (params->xCenter - params->zoom) + iX * PixelWidth;

				Zx = 0;
				Zy = 0;
				Zx2 = 0;
				Zy2 = 0;

				uint64_t Iteration = 0;
				while (((Zx2 + Zy2) <= 4.0) && (Iteration < params->iterations)) {
					Zy = (2.0 * Zx * Zy) + Cy;
					Zx = Zx2 - Zy2 + Cx;
					Zx2 = Zx * Zx;
					Zy2 = Zy * Zy;
					Iteration++;
				};

				float hue = 360.0f * (double)Iteration / (double)params->iterations;
				float brightness = (Iteration < params->iterations) ? (100.0f * (double)Iteration / (double)params->iterations) : 0.0f;
				float saturation = (Iteration < params->iterations) ? 100.0f : 0.0f;

				auto color = Utils::HSVtoRGB(hue, saturation, brightness);
				buffer[(bufferWidth * iY) + iX] = color;

			}
		}
	}



	void multithreadEvaluate(mandelbrot_params_t* params, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer)
	{
		vector<thread> threads;

		//const auto numThreads = std::thread::hardware_concurrency() * 128;
		const auto numThreads = (x2 - x1);
		//uint32_t deltax = (x2 - x1) / numThreads;
		uint32_t deltax = 1;

		for (uint32_t i = 0; i < numThreads; i++)
		{
			int32_t newx1 = x1 + (deltax * i);
			int32_t newx2 = newx1 + deltax;
			threads.push_back(thread(Evaluate, params, newx1, y1, newx2, y2, bufferWidth, bufferHeight, buffer));
		}

		auto originalthread = threads.begin();
		while (originalthread != threads.end())
		{
			originalthread->join();
			originalthread++;
		}
	}



}