/*
 * FractalTexture.h
 *
 *  Created on: Mar 30, 2011
 *      Author: mmerchan
 */

#include <SDL/SDL.h>
#include "ProceduralTexture.h"
#include "../../Color.h"
#include <complex>
#include "../../../../Generic/Generic.h"

#ifndef FRACTALTEXTURE_H_
#define FRACTALTEXTURE_H_

class JuliaTexture: public ProceduralTexture,
		public MouseListener,
		public KeyListener {

protected:
	bool drag1, drag2;
	int maxIterations;

	double cx, cy;
	Color color;

public:

	JuliaTexture(int width, int height, double cx, double cy,
			const Vector3& center = Vector3(), double rangeX = 1,
			double rangeY = 1, int iter = 10) :
		ProceduralTexture(width, height, center, rangeX, rangeY) {
		drag1 = false;
		drag2 = false;
		this->maxIterations = iter;
		this->cx = cx;
		this->cy = cy;

		setColor(Color(255, 255, 255));
	}

	void setColor(Color c) {
		this->color = c;
	}

	virtual void LoadTexture() {
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
				0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		Uint32 tmpColor;
		double value;

		// For each pixel, do an iteration
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++) {

				double Cx = center.getX() + getLocalPoint(x, rangeX, width);
				double Cy = center.getY() + getLocalPoint(y, rangeY, height);

				complex<double> c(cx, cy);
				complex<double> z(Cx, Cy);

				int i;
				for (i = 0; i < maxIterations; i++) {
					z = z * z + c;
					if (abs(z) > 2)
						break;
				}

				value = (i + 1 - log(log(abs(z))) / log(2.0))
						/ (double) maxIterations;

				tmpColor = SDL_MapRGBA(surface->format, color.getR() * value,
						value * color.getG(), color.getB() * value, 255);

				putpixel(x, y, tmpColor);
			}
		LoadGLTexture();
	}

	// TODO DE ACA EN ADELANTE, LO TIENE QUE MANEJAR LA UI, NO YO
	void onMouseMotion(MouseEvent event) {
		if (drag1) {
			float x = getLocalPoint(event.getRelativeX() + width / 2, rangeX,
					width);
			float y = getLocalPoint(event.getRelativeY() + height / 2, rangeY,
					height);

			cx += x;
			cy += y;
		} else if (drag2) {
			float x = getLocalPoint(event.getRelativeX() + width / 2, rangeX,
					width);
			float y = getLocalPoint(event.getRelativeY() + height / 2, rangeY,
					height);

			center += Vector3(x, y, 0) * -1;
		}
	}

	void onMouseWheelDown(MouseEvent event) {
		rangeX *= 1 / 0.75;
		rangeY *= 1 / 0.75;
		unload();
		LoadTexture();
	}

	void onMouseWheelUp(MouseEvent event) {
		rangeX *= 0.75;
		rangeY *= 0.75;
		unload();
		LoadTexture();
	}

	void onMouseRightClickDown(MouseEvent event) {
		drag1 = true;
	}

	void onMouseRightClickUp(MouseEvent event) {
		drag1 = false;
		unload();
		LoadTexture();
	}

	void onMouseLeftClickDown(MouseEvent event) {
		drag2 = true;
	}

	void onMouseLeftClickUp(MouseEvent event) {
		drag2 = false;
		unload();
		LoadTexture();
	}

	void onMouseLeftClick(MouseEvent event) {
	}

	void onKeyDown(int key) {
		if (key == 't') {
			maxIterations += 5;
			unload();
			LoadTexture();
		} else if (key == 'g') {
			maxIterations -= maxIterations > 5 ? 5 : 0;
			unload();
			LoadTexture();
		}
	}

	void onKeyUp(int key) {
	}
};

#endif /* FRACTALTEXTURE_H_ */
