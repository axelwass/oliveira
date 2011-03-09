/*
 * DerivativeData.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#ifndef INTEGRATIONDATA_H_
#define INTEGRATIONDATA_H_

class DerivativeData {

	public:
		Vector3 dx;
		Vector3 dv;

		DerivativeData(const Vector3& dv = Vector3(),
				const Vector3& dx = Vector3()) {
			this->dv = dv;
			this->dx = dx;
		}

		/** Returns a copy of this derivative scaled to the given value.*/
		DerivativeData operator*(const real value) {
			DerivativeData out;
			out.dx = this->dx * value;
			out.dv = this->dv * value;
			return out;
		}

		/** Returns the value of the given derivative added to this*/
		DerivativeData operator+(const DerivativeData& other) {
			DerivativeData out;
			out.dx = this->dx + other.dx;
			out.dv = this->dv + other.dv;
			return out;
		}

		/** Returns the value of the given derivative substracted from this */
		DerivativeData operator-(const DerivativeData& other) {
			DerivativeData out;
			out.dx = this->dx - other.dx;
			out.dv = this->dv - other.dv;
			return out;
		}
};

#endif /* INTEGRATIONDATA_H_ */
