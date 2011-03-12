/*
 * UIOverlay.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */
#include <list>
#include "../Render/RenderLayer2D.h"
#include "UIComponent.h"
using namespace std;

#ifndef UIOVERLAY_H_
#define UIOVERLAY_H_

class UIOverlay: public RenderLayer2D {
	private:

		typedef RenderLayer2D super;

		list<UIComponent *> components;

	public:
		UIOverlay() {

		}

		void addUIComponent(UIComponent * c) {
			this->components.push_back(c);
		}

		void render() {
			super::render(); // Render camera
			list<UIComponent *>::iterator c;

			for (c = components.begin(); c != components.end(); c++)
				(*c)->render();

		}
};

#endif /* UIOVERLAY_H_ */
