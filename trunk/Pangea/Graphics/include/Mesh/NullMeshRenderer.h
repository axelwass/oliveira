/*
 * NullMeshRenderer.h
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */

#ifndef NULLMESHRENDERER_H_
#define NULLMESHRENDERER_H_

/**
 * Does nothing.
 */

class NullMeshRenderer: public MeshRenderer {
public:
	NullMeshRenderer(AbstractMesh * m) :
		MeshRenderer(m) {
	}

	void render() {
	}
};

#endif /* NULLMESHRENDERER_H_ */
