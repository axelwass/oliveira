/*
 * ProceduralTexture.h
 *
 *  Created on: Mar 30, 2011
 *      Author: mmerchan
 */

#ifndef PROCEDURALTEXTURE_H_
#define PROCEDURALTEXTURE_H_

class ProceduralTexture: public Texture {

protected:

	//TODO: Clase PixelController, que maneje sdl, gl, raw, lo que sea y me de putpixel
	void putpixel(int x, int y, Uint32 pixel) {
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to set */
		Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

		switch (bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *) p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *) p = pixel;
			break;
		}
	}

	float getLocalPoint(int p, float destRange, int srcRange) {
		return destRange * (-1.0 + (2.0 * p / (float) srcRange));
	}

	Vector3 center;
	float rangeX, rangeY;

public:

	ProceduralTexture(int width, int height, const Vector3& center = Vector3(),
			float rangeX = 1, float rangeY = 1) :
		Texture("") {

		this->width = width;
		this->height = height;
		this->center = center;

		this->rangeX = rangeX;
		this->rangeY = rangeY;
	}

	virtual ~ProceduralTexture() {
	}

	virtual void LoadTexture() = 0;
};

#endif /* PROCEDURALTEXTURE_H_ */
