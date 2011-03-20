/*
 * Vertex.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "../../../Generic/Generic.h"

class Vertex {

	private:
		Vector3 position;
		Vector3 normal;
		Vector3 color;

	public:

		Vertex(const Vector3& position = Vector3(), const Vector3& normal =
				Vector3(), const Vector3& color = Vector3()) :
			position(position), normal(normal), color(color) {
		}

		void setPosition(const Vector3& p) {
			this->position = p;
		}

		Vector3 getPosition() {
			return position;
		}

		Vector3 getNormal() {
			return normal;
		}

		void resetNormal() {
			this->normal = Vector3();
		}

		void setNormal(const Vector3& n) {
			this->normal = n;
		}

};

#endif /* VERTEX_H_ */
