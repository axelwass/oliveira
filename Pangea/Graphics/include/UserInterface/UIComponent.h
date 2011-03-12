/*
 * UIComponent.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"

#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

class UIComponent {
	protected:
		Vector3 position;

	public:
		UIComponent() {
		}

		void setPosition(const Vector3& p) {
			this->position = p;
		}

		void translate(const Vector3& p) {
			this->position += p;
		}

		virtual void render() = 0;
};

#endif /* UICOMPONENT_H_ */
