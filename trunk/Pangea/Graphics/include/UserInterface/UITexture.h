/*
 * UITexture.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "UIComponent.h"
#include "../Texture/TextTexture.h"

#ifndef UITEXTURE_H_
#define UITEXTURE_H_

class UITexture: public UIComponent {

	protected:

		Texture * texture;
		int w, h;

	public:

		UITexture() {
			texture = NULL;
		}

		UITexture(Texture * t) {
			setTexture(t);
		}

		virtual void setTexture(Texture * t) {
			if (t != NULL) {
				this->texture = t;
				this->texture->LoadTexture();
			}
		}

		void render() {

			if (texture == NULL)
				return;

			int x, y;
			x = position.getX();
			y = position.getY();
			h = texture->getHeight();
			w = texture->getWidth();

			texture->BindTexture();

			// Draw rectangle
			glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(x, y, 0);

			glTexCoord2f(1, 0);
			glVertex3f(x + w, y, 0);

			glTexCoord2f(1, 1);
			glVertex3f(x + w, y + h, 0);

			glTexCoord2f(0, 1);
			glVertex3f(x, y + h, 0);

			glEnd();

			texture->UnbindTexture();

		}
};

#endif /* UITEXTURE_H_ */
