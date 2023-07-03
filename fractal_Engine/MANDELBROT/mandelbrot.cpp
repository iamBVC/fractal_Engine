#include "mandelbrot.h"
#include "../UTILS/utils.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

namespace Mandelbrot
{

	void Evaluate(uint64_t iterations, double xCenter, double yCenter, double zoom, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer)
	{

		double Cx, Cy;
		double Zx, Zy;
		double Zx2, Zy2;
		double PixelWidth = (zoom * 2.0) / bufferWidth;
		double PixelHeight = (zoom * 2.0) / bufferHeight;


		for (uint32_t iY = y1; iY < y2; iY++) {
			Cy = (yCenter - zoom) + (iY * PixelHeight);
			if (fabs(Cy) < PixelHeight / 2.0) {
				Cy = 0.0; /* Main antenna */
			}

			for (uint32_t iX = x1; iX < x2; iX++) {

				Cx = (xCenter - zoom) + iX * PixelWidth;

				Zx = 0;
				Zy = 0;
				Zx2 = 0;
				Zy2 = 0;

				uint64_t Iteration = 0;
				while (((Zx2 + Zy2) <= 4.0) && (Iteration < iterations)) {
					Zy = (2.0 * Zx * Zy) + Cy;
					Zx = Zx2 - Zy2 + Cx;
					Zx2 = Zx * Zx;
					Zy2 = Zy * Zy;
					Iteration++;
				};

				float hue = 360.0f * (double)Iteration / (double)iterations;
				float brightness = (Iteration < iterations) ? (100.0f * (double)Iteration / (double)iterations) : 0.0f;
				float saturation = (Iteration < iterations) ? 100.0f : 0.0f;

				auto color = Utils::HSVtoRGB(hue, saturation, brightness);
				buffer[(bufferWidth * iY) + iX] = color;

			}
		}
	}



	void multithreadEvaluate(uint64_t iterations, double xCenter, double yCenter, double zoom, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t bufferWidth, int32_t bufferHeight, uint32_t* buffer)
	{
		vector<thread> threads;

		const auto numThreads = std::thread::hardware_concurrency();
		int32_t deltax = (x2 - x1) / numThreads;

		for (uint32_t i = 0; i < numThreads; i++)
		{
			int32_t newx1 = x1 + (deltax * i);
			int32_t newx2 = newx1 + deltax;
			threads.push_back(thread(Evaluate, iterations, xCenter, yCenter, zoom, newx1, y1, newx2, y2, bufferWidth, bufferHeight, buffer));
		}

		auto originalthread = threads.begin();
		while (originalthread != threads.end())
		{
			originalthread->join();
			originalthread++;
		}
	}



}