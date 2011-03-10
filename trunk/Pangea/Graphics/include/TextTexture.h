/*
 * TextTexture.h
 *
 *  Created on: Mar 10, 2011
 *      Author: mmerchan
 */

#include <SDL/SDL_ttf.h>
#include "Texture.h"

#include <math.h>

#ifndef TEXTTEXTURE_H_
#define TEXTTEXTURE_H_

class TextTexture: public Texture {

	private:

		TTF_Font * font;
		Color color;
		int size;

		int nextpoweroftwo(int x) {
			double logbase2 = log(x) / log(2);
			return round(pow(2, ceil(logbase2)));
		}

	public:

		//Constructor
		TextTexture(string name, int size, Color color) :
			Texture(name) {
			this->size = size;
			this->color = color;
			this->font = NULL;
		}

		void LoadTexture() {

			font = TTF_OpenFont("verdana.ttf", size);

			TTF_SetFontStyle(font, TTF_STYLE_BOLD);

			//White text. To change it, use Color.Set_GLColor
			SDL_Color tmp = { 255, 255, 255 };
			SDL_Surface * initial;

			initial = TTF_RenderText_Solid(font, name.c_str(), tmp);

			/* Convert the rendered text to a known format */
			width = nextpoweroftwo(initial->w);
			height = nextpoweroftwo(initial->h);

			surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000,
					0x0000ff00, 0x000000ff, 0xff000000);

			SDL_BlitSurface(initial, 0, surface, 0);

			LoadGLTexture();
			TTF_CloseFont(font);
			SDL_FreeSurface(initial);
		}
};

#endif /* TEXTTEXTURE_H_ */
