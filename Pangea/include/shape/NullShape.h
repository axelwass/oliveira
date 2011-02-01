/*
 * NullShape.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#ifndef NULLSHAPE_H_
#define NULLSHAPE_H_

// SINGLETON CLASS
class NullShape: public Shape {
	private:
		static NullShape * instance;

		NullShape() {
		}

	public:
		static NullShape * getInstance() {
			if (NullShape::instance == NULL)
				NullShape::instance = new NullShape();
			return NullShape::instance;
		}

		shapeType getType() const {
			return NULLSHAPE;
		}

		Shape * intersection(const Shape * s) {
			return NULL;
		}
};

NullShape * NullShape::instance = NULL;

#endif /* NULLSHAPE_H_ */
