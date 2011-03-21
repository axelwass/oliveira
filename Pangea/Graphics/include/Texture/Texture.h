/*
 * Texture.h
 *
 *  Created on: Mar 10, 2011
 *      Author: mmerchan
 */

#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture {

protected:

	GLuint texture; // This is a handle to our texture object
	int width, height;
	SDL_Surface * surface;
	string name;
	bool loaded;

	// Convert SDL_Surface to Texture
	void LoadGLTexture() {

		if (surface != NULL) {
			//		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

			SDL_PixelFormat *format = surface->format;

			this->width = surface->w;
			this->height = surface->h;

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_LINEAR);

			glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

			if (format->Amask)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
						GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

			glBindTexture(GL_TEXTURE_2D, NULL);

			loaded = true;
			SDL_FreeSurface(surface);
			surface = NULL;
		}

	}

public:

	virtual ~Texture() {
		glDeleteTextures(1, &texture);
	}

	//Constructor
	Texture(string name) {
		this->name = name;
		this->surface = NULL;
		this->loaded = false;
	}

	//Accessing
	void BindTexture() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void UnbindTexture() {
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	int getWidth() {
		return this->width;
	}

	int getHeight() {
		return this->height;
	}

	virtual void LoadTexture() = 0;
};

#endif /* TEXTURE_H_ */
