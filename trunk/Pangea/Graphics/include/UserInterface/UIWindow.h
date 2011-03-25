/*
 * UIWindow.h
 *
 *  Created on: Mar 24, 2011
 *      Author: mariano
 */

#ifndef UIWINDOW_H_
#define UIWINDOW_H_

class UIWindow: public UIComponent {
private:

	int width, height;
	Color bgColor, borderColor;

	list<UIComponent *> components;

	typedef UIComponent super;

public:

	UIWindow(Vector3 position, int w, int h, Color bg) :
		width(w), height(h), bgColor(bg) {
		this->setPosition(position);
		this->borderColor = bgColor * 1.5;
	}

	void translate(const Vector3& p) {
		super::translate(p);
		list<UIComponent *>::iterator c;
		for (c = components.begin(); c != components.end(); c++)
			(*c)->translate(p);
	}

	void addUIComponent(UIComponent * c) {
		c->translate(this->position);
		this->components.push_back(c);
	}

	void render() {

		int x, y;
		x = position.getX();
		y = position.getY();

		bgColor.set_GLColor();

		// Draw rectangle
		glBegin( GL_QUADS);

		glVertex3f(x, y, 0);
		glVertex3f(x + width, y, 0);
		glVertex3f(x + width, y + height, 0);
		glVertex3f(x, y + height, 0);

		glEnd();

		borderColor.set_GLColor();

		// Draw rectangle
		glBegin( GL_LINE_LOOP);

		glVertex3f(x, y, 0);
		glVertex3f(x + width, y, 0);
		glVertex3f(x + width, y + height, 0);
		glVertex3f(x, y + height, 0);

		glEnd();

		list<UIComponent *>::iterator c;
		for (c = components.begin(); c != components.end(); c++)
			(*c)->render();
	}
};

#endif /* UIWINDOW_H_ */
