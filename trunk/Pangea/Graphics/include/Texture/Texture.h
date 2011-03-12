/*
 * Texture.h
 *
 *  Created on: Mar 10, 2011
 *      Author: mmerchan
 */

#include <string>
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
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				SDL_PixelFormat *format = surface->format;

				this->width = surface->w;
				this->height = surface->h;

				if (format->Amask) {
					gluBuild2DMipmaps(GL_TEXTURE_2D, 4, this->width,
							this->height, GL_RGBA, GL_UNSIGNED_BYTE,
							surface->pixels);
				} else {
					gluBuild2DMipmaps(GL_TEXTURE_2D, 3, this->width,
							this->height, GL_RGB, GL_UNSIGNED_BYTE,
							surface->pixels);
				}
				loaded = true;
				SDL_FreeSurface(surface);
				surface = NULL;
			}
			glBindTexture(GL_TEXTURE_2D, NULL);
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
