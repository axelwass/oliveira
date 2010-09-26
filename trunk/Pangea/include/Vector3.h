/*
 * Vector3.h
 *
 *  Created on: Jan 21, 2010
 *      Author: Mariano
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "precision.h"
#include <math.h>

class Vector3 {

private:

	/** Holds a 3D vector */
	real x, y, z;

public:

    real getX(){ return x; }
    real getY(){ return y; }
    real getZ(){ return z; }

	Vector3() :
		x(0), y(0), z(0) {
	}

	Vector3(const real x, const real y, const real z) :
		x(x), y(y), z(z) {
	}

	/** Inverts this vector's components */
	void invert();

	/** Gets the magnitude of this vector */
	real magnitude() const;

	/** Gets the squared magnitude of this vector */
	real squareMagnitude() const;

	/** Turns a non-zero vector into a vector of unit length */
	void normalize();

	/** Clears the components of the vector */
	void clear();

	/**
	 * OPERATORS
	 */

	// Assign a vector
	void operator=(const Vector3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	// Equals
	bool operator==(const Vector3& v) {
		return (x == v.x) && (y == v.y) && (z == v.z);
	}

	/** Multiplies this vector by the given scalar.*/
	void operator*=(const real value);

	/** Adds the given vector to this.*/
	void operator+=(const Vector3& v);

	/**Substracts the given vector from this.*/
	void operator-=(const Vector3& v);

	/** Returns a copy of this vector scaled to the given value.*/
	Vector3 operator*(const real value);

	/** Returns the value of the given vector added to this*/
	Vector3 operator+(const Vector3& v) const;

	/** Returns the value of the given vector substracted from this */
	Vector3 operator-(const Vector3& v) const;

	/** Adds the given vector to this, scaled by the given amount */
	void addScaledVector(const Vector3& vector, real scale);

	/** Calculates and returns a component-wise product of this
	 * vector with the given vector */
	Vector3 componentProduct(const Vector3& vector) const;

	/** Performs a component-wise product with the given vector
	 * and sets this vector to its result */
	void componentProductUpdate(const Vector3& vector);

	/** Calculates and returns the scalar product of this vector
	 * with the given vector. */
	real scalarProduct(const Vector3& vector) const;

	/** Calculates and returns the scalar product of this vector
	 * with the given vector */
	real operator*(const Vector3& vector) const;

	/**
	 * Calculates and returns the vector product of this vector
	 * with the given vector.
	 */
	Vector3 vectorProduct(const Vector3& vectpr) const;

	/**
	 * Updates this vector to be the vector product of its current
	 * value and the given vector.
	 */
	void operator%=(const Vector3& vector);

	/**
	 * Calculates and returns the vector product of this vector
	 * with the given vector.
	 */
	Vector3 operator%(const Vector3& vector) const;
};

#endif /* VECTOR3_H_ */
