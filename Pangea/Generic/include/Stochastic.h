/*
 * Stochastic.h
 *
 *  Created on: Mar 31, 2011
 *      Author: mmerchan
 */

#ifndef STOCHASTIC_H_
#define STOCHASTIC_H_

#include "precision.h"

class Stochastic {
public:

	// [0,1]
	static real random() {
		return ((real) rand()) / RAND_MAX;
	}

	// [-0.5,0.5]
	static real normalRandom(int k) {
		real out = 0;
		for (int i = 0; i < k; i++)
			out += random() - 0.5;
		return out * 2.0 / k;
	}
};

#endif /* STOCHASTIC_H_ */
