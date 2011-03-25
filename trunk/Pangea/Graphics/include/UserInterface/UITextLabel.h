/*
 * UITextLabel.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "UITexture.h"
#include "../Texture/TextTexture.h"
#include <string>
using namespace std;

#ifndef UITEXTLABEL_H_
#define UITEXTLABEL_H_

class UITextLabel: public UITexture {

protected:

	string text;
	Color color;
	int size;

public:

	UITextLabel(string text, int size, const Color& color, const Vector3& p) {
		this->text = text;
		this->position = p;
		this->color = color;
		this->size = size;

		this->setString(text);
	}

	virtual void setTexture(TexturePtr t) {
	}

	void setString(string text) {
		this->text = text;

		this->texture = TexturePtr(new TextTexture(text, size, color));
		this->texture->LoadTexture();

		this->w = texture->getWidth();
		this->h = texture->getHeight();
	}

};

#endif /* UITEXTLABEL_H_ */
