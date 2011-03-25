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

	TexturePtr texture;
	int w, h;

public:

	UITexture() {
	}

	UITexture(TexturePtr t) {
		setTexture(t);
	}

	virtual void setTexture(TexturePtr t) {
		this->texture = t;
		if (t.get() != NULL)
			this->texture->LoadTexture();
	}

	void render() {
		// To prevent modifying texture
		glColor4f(1, 1, 1, 1);

		if (texture.get() == NULL)
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
