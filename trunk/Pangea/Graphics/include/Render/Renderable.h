/*
 * Renderable.h
 *
 *  Created on: Mar 14, 2011
 *      Author: mmerchan
 */

#ifndef RENDERABLE_H_
#define RENDERABLE_H_

class Renderable {
	public:
		Renderable() {
		}
		virtual void render() = 0;
};

#endif /* RENDERABLE_H_ */
