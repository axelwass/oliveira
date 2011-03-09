/*
 * Shape.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"
#include "IntersectionData.h"
#include <vector>
#include <stdio.h>
#include <tr1/memory>
using namespace std;

#ifndef SHAPE_H_
#define SHAPE_H_

class Shape;

typedef tr1::shared_ptr<Shape> ShapePtr;

class Shape {

	protected:

		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		typedef enum {
			CUBE, PLANE, SPHERE, NULLSHAPE
		} shapeType;

	public:

		Shape() {
			this->scale = Vector3(1, 1, 1);
		}

		virtual ~Shape() {
		}

		// Test intersection between this shape and other
		// and return the shape of its intersection (point, line, circle, etc)
		virtual IntersectionData intersection(const Shape * s) = 0;

		virtual shapeType getType() const = 0;

		Vector3 getPosition() const {
			return position;
		}

		Vector3 getRotation() {
			return rotation;
		}

		Vector3 getScale() {
			return scale;
		}

		virtual void setPosition(const Vector3& pos) {
			this->position = pos;
		}

		virtual void setRotation(const Vector3& rot) {
			this->rotation = rot;
		}

		virtual void setScale(const Vector3& scale) {
			this->scale = scale;
		}

		void translate(const Vector3& t) {
			this->setPosition(this->position + t);
		}

		void rotate(const Vector3& r) {
			this->setRotation(this->rotation + r);
		}
};

#endif /* SHAPE_H_ */
