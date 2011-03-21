/*
 * MeshLoader.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

/*
 * MeshLoader.h
 *
 *  Created on: Feb 25, 2010
 *      Author: Mariano
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Mesh.h"
using namespace std;

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

class MeshLoader {
public:

	static Mesh * load(string filename) {

		Mesh * outMesh = new Mesh();

		// Load file
		ifstream file(filename.c_str());

		while (!file.eof()) {

			string line;

			getline(file, line);

			// Get vertices values
			if (line[0] == 'v') {
				double xyz[3];
				stringstream values(line.substr(line[1] == ' ' ? 1 : 2,
						line.size()));
				values >> xyz[0];
				values >> xyz[1];
				values >> xyz[2];

				if (line[1] == ' ')
					outMesh->addVertex(new Vertex((Vector3(xyz[0], xyz[1],
							xyz[2]))));
				else if (line[1] == 'n')
					outMesh->addVertexNormal(Vector3(xyz[0], xyz[1], xyz[2]));
				else if (line[1] == 't')

					outMesh->addTextureCoordinate(Vector3(xyz[0], xyz[1],
							xyz[2]));
			}

			// Get faces values
			if (line[0] == 'f') {

				vector<VertexWrapper> indices;
				stringstream values(line.substr(1, line.size()));

				//Get index of each vertex
				while (!(values.eof())) {
					stringstream indexStreams[3];

					values.get();

					int index = 0;
					while (values.peek() != ' ' && !values.eof()) {

						if (values.peek() == '/') {
							values.get();
							index++;
						}

						indexStreams[index].put(values.get());
					}

					while (values.peek() != ' ' && !values.eof())
						values.get();

					int tmpIndices[3];
					indexStreams[0] >> tmpIndices[0];

					if (index >= 1)
						indexStreams[1] >> tmpIndices[1];
					else
						tmpIndices[1] = 0;

					if (index >= 2)
						indexStreams[2] >> tmpIndices[2];
					else
						tmpIndices[2] = 0;

					// WARNING: order is of indices is 0,2,1! (v,vt,vn), wrapper is (v,vn,vt)
					indices.push_back(VertexWrapper(tmpIndices[0],
							tmpIndices[2], tmpIndices[1]));
				}

				Face * face = new Face();

				// Get all the loop vertices on a container
				// Note that OBJ index starts at 1, while C++ starts at 0
				for (unsigned i = 0; i < indices.size(); i++)
					face->addVertex(indices[i].getVertex() - 1,
							indices[i].getNormal() - 1, indices[i].getTexture()
									- 1);

				//	face->updateNormal();
				outMesh->addFace(face);
			}

		}

		file.close();

		// Center mesh on origin
		outMesh->centerPivot();
		outMesh->getTransform()->setPosition(outMesh->getPivot() * (-1));
		outMesh->applyTransform();
		outMesh->centerPivot();

		printf(
				"Vertex count: %d, Face count: %d, Normal count: %d, TX count: %d\n",
				outMesh->getVertices()->size(), outMesh->getFaces()->size(),
				outMesh->getNormals().size(),
				outMesh->getTextureCoordinates().size());
		return outMesh;
	}

};

#endif /* MESHLOADER_H_ */
