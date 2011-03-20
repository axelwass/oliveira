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

					if (line[1] == ' ') {
						int flag = 1;
						if (line[2] == ' ')
							flag = 2;

						double xyz[3];
						stringstream values(line.substr(flag, line.size()));

						values >> xyz[0];
						values >> xyz[1];
						values >> xyz[2];

						// Add vertex to mesh
						outMesh->addVertex(new Vertex((Vector3(xyz[0], xyz[1],
								xyz[2]))));
					}

					if (line[1] == 'n') {
						double xyz[3];
						stringstream values(line.substr(2, line.size()));

						values >> xyz[0];
						values >> xyz[1];
						values >> xyz[2];

						//		printf("%g,%g,%g\n", xyz[0], xyz[1], xyz[2]);

						outMesh->addVertexNormal(
								Vector3(xyz[0], xyz[1], xyz[2]));
					}

					if (line[1] == 't') {
						double xyz[3];
						stringstream values(line.substr(2, line.size()));

						values >> xyz[0];
						values >> xyz[1];
						values >> xyz[2];

						outMesh->addTextureCoordinate(Vector3(xyz[0], xyz[1],
								xyz[2]));
					}
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
						indexStreams[1] >> tmpIndices[1];
						indexStreams[2] >> tmpIndices[2];

						indices.push_back(VertexWrapper(tmpIndices[0],
								tmpIndices[1], tmpIndices[2]));
					}

					Face * face = new Face();

					// Get all the loop vertices on a container
					// Note that OBJ index starts at 1, while C++ starts at 0
					for (unsigned i = 0; i < indices.size(); i++) {
						face->addVertex(indices[i].getVertex() - 1,
								indices[i].getNormal() - 1,
								indices[i].getTexture() - 1);

						Vector3 normal = outMesh->getNormals()[indices[i].getNormal() - 1];
						printf("%g,%g,%g\n", normal.getX(), normal.getY(),
														normal.getZ());
					}

					printf("CORTE\n");

					vector<VertexWrapper>& faceVertices = face->getVertices();
					vector<VertexWrapper>::iterator n;
					for (n = faceVertices.begin(); n != faceVertices.end(); n++) {
						int index = (*n).getNormal();
						Vector3 normal = outMesh->getNormals()[index];
						printf("%g,%g,%g\n", normal.getX(), normal.getY(),
								normal.getZ());
					}

					printf("\n\n");

					// CARGA MAL LAS COSAS EN LAS FACES!!!

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

			/*

			 printf("Cargue\n");

			 vector<Vector3>& normals = outMesh->getNormals();
			 vector<Vector3>::iterator n;
			 for(n=normals.begin();n!=normals.end();n++){
			 printf("%g,%g,%g\n", (*n).getX(),(*n).getY(),(*n).getZ());
			 }*/

			printf(
					"Vertex count: %d, Face count: %d, Normal count: %d, TX count: %d\n",
					outMesh->getVertices()->size(),
					outMesh->getFaces()->size(), outMesh->getNormals().size(),
					outMesh->getTextureCoordinates().size());
			return outMesh;
		}

};

#endif /* MESHLOADER_H_ */
