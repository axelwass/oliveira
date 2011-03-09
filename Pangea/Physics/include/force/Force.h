/*
 * Force.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */
#include "../particle/ParticleData.h"
#include "../particle/DerivativeData.h"
#include "../../../Generic/Generic.h"
#include <iostream>
#include <list>
#include <tr1/memory>
using namespace std;

#ifndef FORCE_H_
#define FORCE_H_

class Force;

typedef tr1::shared_ptr<Force> ForcePtr;

class Force {

	private:
		virtual DerivativeData _evaluate(real t, ParticleData * data) = 0;
		virtual Force * _clone() = 0;
		list<Force *> forces;

	public:
		Force() {
		}
		virtual ~Force() {
			/*	cout << "Eliminando funcion..." << forces.size() <<endl;
			 list<Force *>::iterator itr;
			 for(itr=forces.begin();itr!=forces.end();itr++){
			 Force * del = (*itr);
			 delete del;
			 }*/
		}

		// Evaluation function
		DerivativeData evaluate(real t, ParticleData * data) {
			DerivativeData out = this->_evaluate(t, data);

			list<Force *>::iterator itr;
			for (itr = forces.begin(); itr != forces.end(); itr++) {
				out = out + (*itr)->_evaluate(t, data);
			}
			return out;
		}

		// Assign a vector
		void operator+=(Force * other) {
			Force * copy = other->_clone();
			forces.push_back(copy);
		}
};

#endif /* FORCE_H_ */
