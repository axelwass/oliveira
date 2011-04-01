/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Game/Game.h"
#include <GL/glut.h>

void testNormal() {

	int size = 10;

	int * distr = new int[size];

	for (int i = 0; i < size; i++)
		distr[i] = 0;

	int k = 10000;
	for (int i = 0; i < k; i++) {

		float r = Stochastic::normalRandom(10);

		int index = size * r;
		index += size / 2;

		distr[index]++;
	}

	for (int i = 0; i < size; i++)
		printf("%d\n", distr[i]);

}

// LEER todo.txt
int main(int argc, char *argv[]) {
	srand(time(NULL));

	// initialize glut!
	glutInit(&argc, (char**) argv);

	GameEngine();
	return 0;
}
