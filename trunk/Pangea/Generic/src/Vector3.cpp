/*
 * Vector3.cpp
 *
 *  Created on: Jan 21, 2010
 *      Author: Mariano
 */

#include "../include/Vector3.h"

/**
 *  Inverts this vector's components
 */
void Vector3::invert() {
	x = -x;
	y = -y;
	z = -z;
}

/**
 *  Clears the components of the vector
 */
void Vector3::clear() {
	x = 0;
	y = 0;
	z = 0;
}

/**
 *  Gets the magnitude of this vector
 */
real Vector3::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

/**
 *  Gets the squared magnitude of this vector
 */
real Vector3::squareMagnitude() const {
	return x * x + y * y + z * z;
}

/**
 *  Multiplies this vector by the given scalar.
 */
void Vector3::operator*=(const real value) {
	x *= value;
	y *= value;
	z *= value;
}

/**
 *  Returns a copy of this vector scaled to the given value.
 */
Vector3 Vector3::operator*(const real value) const{
	return Vector3(x * value, y * value, z * value);
}

/**
 *  Turns a non-zero vector into a vector of unit length
 */
void Vector3::normalize() {
	real l = magnitude();
	if (l > 0) {
		(*this) *= ((real) 1) / l;
	}
}
/**
 *  Adds the given vector to this.
 */
void Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

/**
 * Returns the value of the given vector added to this
 */
Vector3 Vector3::operator+(const Vector3& v) const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

/**
 * Substracts the given vector from this.
 */
void Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

/**
 * Returns the value of the given vector substracted from this
 */
Vector3 Vector3::operator-(const Vector3&v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

/**
 *  Adds the given vector to this, scaled by the given amount
 */
void Vector3::addScaledVector(const Vector3& vector, real scale) {
	x += vector.x * scale;
	y += vector.y * scale;
	z += vector.z * scale;
}

/**
 * Calculates and returns a component-wise product of this
 * vector with the given vector
 */
Vector3 Vector3::componentProduct(const Vector3& vector) const {
	return Vector3(x * vector.x, y * vector.y, z * vector.y);
}

/**
 * Performs a component-wise product with the given vector
 * and sets this vector to its result
 */
void Vector3::componentProductUpdate(const Vector3& vector) {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

/**
 * Calculates and returns the scalar product of this vector
 * with the given vector.
 */
real Vector3::scalarProduct(const Vector3& vector) const {
	return x * vector.x + y * vector.y + z * vector.z;
}

/**
 * Calculates and returns the scalar product of this vector
 * with the given vector.
 */
real Vector3::operator*(const Vector3& vector) const {
	return x * vector.x + y * vector.y + z * vector.z;
}

/**
 * Calculates and returns the vector product of this vector
 * with the given vector.
 */
Vector3 Vector3::vectorProduct(const Vector3& vector) const {
	return Vector3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x
			* vector.y - y * vector.x);
}

/**
 * Updates this vector to be the vector product of its current
 * value and the given vector.
 */
void Vector3::operator%=(const Vector3& vector) {
	*this = vectorProduct(vector);
}

/**
 * Calculates and returns the vector product of this vector
 * with the given vector.
 */
Vector3 Vector3::operator%(const Vector3& vector) const {
	return Vector3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x
			* vector.y - y * vector.x);
}

