/*
 * UITextLabel.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "UIComponent.h"
#include "../Texture/TextTexture.h"
#include <string>
using namespace std;

#ifndef UITEXTLABEL_H_
#define UITEXTLABEL_H_

class UITextLabel: public UIComponent {

	protected:

		string text;
		TextTexture * texture;
		Color color;
		int size;
		int w, h;

	public:

		UITextLabel(string text, int size, const Color& color, const Vector3& p) {
			this->text = text;
			this->position = p;
			this->color = color;
			this->size = size;

			this->setString(text);
		}

		void setString(string text) {
			texture = new TextTexture(text, size, color);
			texture->LoadTexture();
			w = texture->getWidth();
			h = texture->getHeight();
		}

		void render() {

			int x, y;
			x = position.getX();
			y = position.getY();

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

#endif /* UITEXTLABEL_H_ */
