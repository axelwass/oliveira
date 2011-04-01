/*
 * MandelbrotTexture.h
 *
 *  Created on: Mar 30, 2011
 *      Author: mmerchan
 */

#include "JuliaTexture.h"

#ifndef MANDELBROTTEXTURE_H_
#define MANDELBROTTEXTURE_H_

class MandelbrotTexture: public JuliaTexture {
public:
	MandelbrotTexture(int width, int height, const Vector3& center = Vector3(),
			double rangeX = 1, double rangeY = 1, int iter = 10) :
		JuliaTexture(width, height, 0, 0, center, rangeX, rangeY, iter) {
	}

	void LoadTexture() {
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
				0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		Uint32 tmpColor;
		double Cx, Cy;
		double value;
		// For each pixel, do an iteration
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++) {

				Cx = center.getX() + getLocalPoint(x, rangeX, width);
				Cy = center.getY() + getLocalPoint(y, rangeY, height);

				complex<double> c(Cx, Cy);
				complex<double> z(0, 0);

				int i;
				for (i = 0; i < maxIterations && abs(z) < 2.0; i++)
					z = z * z + c;//+ (double)(rand()%2); // FOR EPIC LULZ

				value = (i + 1 - log(log(abs(z))) / log(2.0))
						/ (double) maxIterations;

				//	if (i == maxIterations)
				//			tmpColor = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
				//	else
				tmpColor = SDL_MapRGBA(surface->format, color.getR() * value,
						value * color.getG(), color.getB() * value, 255);

				putpixel(x, y, tmpColor);
			}
		LoadGLTexture();
	}
};

#endif /* MANDELBROTTEXTURE_H_ */
