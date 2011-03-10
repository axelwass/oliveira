/*
 * ImageTexture.h
 *
 *  Created on: Mar 10, 2011
 *      Author: mmerchan
 */

#include "Texture.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

class ImageTexture: public Texture {

	public:

		//Constructor
		ImageTexture(string name) :
			Texture(name) {
		}

		void LoadTexture() {
			SDL_Surface* surface = IMG_Load(this->name.c_str());
			LoadGLTexture();
		}
};

#endif /* IMAGETEXTURE_H_ */
