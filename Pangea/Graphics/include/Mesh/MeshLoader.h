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

			vector<Vertex *> tmpVertices;

			// LOAD OBJECT
			ifstream file(filename.c_str());

			while (!file.eof()) {

				string line;

				getline(file, line);

				// Get vertices values
				if (line[0] == 'v' && line[1] == ' ') {

					int flag = 1;
					if (line[2] == ' ')
						flag = 2;

					double xyz[3];
					stringstream values(line.substr(flag, line.size()));

					values >> xyz[0];
					values >> xyz[1];
					values >> xyz[2];

					// Add vertex to mesh
					tmpVertices.push_back(new Vertex((Vector3(xyz[0], xyz[1],
							xyz[2]))));

				}

				// Get faces values
				if (line[0] == 'f') {

					vector<int> indices;
					stringstream values(line.substr(1, line.size()));

					int tmp;

					//Get index of each vertex
					while (!(values.eof())) {
						stringstream index;
						values.get();

						while (values.peek() != '/' && values.peek() != ' '
								&& !values.eof())
							index.put(values.get());

						while (values.peek() != ' ' && !values.eof())
							values.get();

						index >> tmp;
						indices.push_back(tmp);
					}

					Face * face = new Face();

					// Get all the loop vertices on a container
					// Note that OBJ index starts at 1, while C++ starts at 0
					for (unsigned i = 0; i < indices.size(); i++)
						face->addVertex(tmpVertices[indices[i] - 1]);

					face->updateNormal();
					outMesh->addFace(face);
				}

				// Get rid of comment lines
				if ((line[0] == '#') || line[0] == ' ');

			}

			file.close();

			//outMesh.centerPivot();
			//outMesh.translate(outMesh.getPivot() * -1);
			//outMesh.softenNormals();

			printf("Vertex count: %d, Face count: %d\n", tmpVertices.size(), outMesh->getFaces()->size());
			return outMesh;
		}

};

#endif /* MESHLOADER_H_ */
