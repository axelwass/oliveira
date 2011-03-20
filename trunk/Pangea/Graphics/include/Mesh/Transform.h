/*
 * Transform.h
 *
 *  Created on: Mar 19, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

class Transform {

	private:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

	public:
		Transform(const Vector3& p = Vector3(), const Vector3& r = Vector3(),
				const Vector3& s = Vector3(1, 1, 1));

		void setPosition(const Vector3& position);
		void setRotation(const Vector3& rotation);
		void setScale(const Vector3& scale);

		Vector3 getPosition() const;
		Vector3 getRotation() const;
		Vector3 getScale() const;

};

#endif /* TRANSFORM_H_ */
