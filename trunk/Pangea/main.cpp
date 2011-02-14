/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "include/Vector3.h"

#include <GL/glut.h>

#include "include/shape/Shape.h"
#include "include/shape/FinitePlane.h"
#include "include/shape/Sphere.h"
#include "include/shape/Cube.h"

#include "include/force/ConstantForce.h"
#include "include/force/SpringForce.h"
#include "include/force/GravitationalForce.h"
#include "include/force/FlashGravityForce.h"

#include "include/particle/ParticleData.h"
#include "include/particle/Particle.h"
#include "include/particle/ParticleRope.h"
#include "include/particle/ParticleBridge.h"

#include "include/emitter/Emitter.h"
#include "include/emitter/DirectionalEmitter.h"
#include "include/world/ParticleWorld.h"
#include "include/ode/RK4.h"
#include "include/precision.h"
#include "include/Matrix.h"
#include "MainWindow.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <sys/time.h>

#include "include/octree/Octree.h"

#include <tr1/memory>

using namespace std;

// LEER todo.txt


// Testeo de interseccion plano - esfera interactivo

/*
 * Esto lo hago asi porque no tenemos un frontend armado todavia
 * tal vez pierda tiempo haciendolo asi, pero pierdo mas tiempo
 * armando lo de arriba sino
 */
void testPlaneSphereCollision(MainWindow * window) {

	FinitePlane plane(20, 100);
	Sphere sphere(20);
	bool collide;

	Cube c(50);

	//plane.translate(Vector3(0,200,-100));

	Uint8 * keystate;

	//plane.setRotation(Vector3(0, 3.1415 / 2, 0));

	//	printf("%s(%p)\n", s2 ? "Colisiona" : "No colisiona", s2);

	real rv = 0;

	while (window->Refresh(0)) {

		// Move sphere
		keystate = SDL_GetKeyState(NULL);
		real vel = 1;
		if (keystate[SDLK_w])
			sphere.translate(Vector3(0, vel, 0));
		if (keystate[SDLK_s])
			sphere.translate(Vector3(0, -vel, 0));
		if (keystate[SDLK_d])
			sphere.translate(Vector3(0, 0, -vel));
		if (keystate[SDLK_a])
			sphere.translate(Vector3(0, 0, vel));
		if (keystate[SDLK_q]) {
			plane.setRotation(Vector3(rv, 0, 0));
			rv += 0.1;
		}

		// Check collision
		collide = plane.intersection(&sphere).hasIntersected();

		// Color feedback for collision
		if (collide)
			glColor3f(1, 0, 0);
		else
			glColor3f(1, 1, 1);

		// Draw sphere
		Vector3 p = sphere.getPosition();
		glTranslatef(p.getX(), p.getY(), p.getZ());
		//glutWireSphere(2, 5, 5);
		glutWireSphere(sphere.getRadius(), 20, 20);
		glTranslatef(-p.getX(), -p.getY(), -p.getZ());

		// Draw plane (que paja!)
		Vector3 pp = plane.getPosition();
		glTranslatef(pp.getX(), pp.getY(), pp.getZ());
		glutWireSphere(2, 5, 5); // Centro
		glTranslatef(-pp.getX(), -pp.getY(), -pp.getZ());

		Vector3 u, v;
		real w, h;

		u = plane.getU();
		v = plane.getV();

		// Just halves
		w = plane.getWidth() / 2;
		h = plane.getHeight() / 2;

		Vector3 p1 = pp + (u * w + v * h);
		Vector3 p2 = pp + (u * w - v * h);
		Vector3 p3 = pp - (u * w + v * h);
		Vector3 p4 = pp - (u * w - v * h);

		glBegin(GL_LINE_LOOP);

		glVertex3f(p1.getX(), p1.getY(), p1.getZ());
		glVertex3f(p2.getX(), p2.getY(), p2.getZ());
		glVertex3f(p3.getX(), p3.getY(), p3.getZ());
		glVertex3f(p4.getX(), p4.getY(), p4.getZ());

		glEnd();

	}

}

void testMatrixClass() {

	Matrix a(5, 20);

	a.set(3, 10, 5);
	printf("%g, %g\n", a.get(3, 10), a[3][10]);

	a[3][10] = 3;
	printf("%g, %g\n", a.get(3, 10), a[3][10]);

	Matrix b(3, 2), c(2, 3);

	b[0][0] = 3;
	b[0][1] = 2;
	b[1][0] = 1;
	b[1][1] = 0;
	b[2][0] = 1;
	b[2][1] = 2;

	c[0][0] = 3;
	c[0][1] = 2;
	c[0][2] = 1;
	c[1][0] = 0;
	c[1][1] = 1;
	c[1][2] = 2;

	b.print();
	printf("\n");
	c.print();
	printf("\n");

	//	(b * c).print();

	Matrix tmp(3, 3);
	Vector3 v(-2, -1, 0);

	tmp[0][0] = 1;
	tmp[0][1] = 2;
	tmp[0][2] = 3;

	tmp[1][0] = 4;
	tmp[1][1] = 5;
	tmp[1][2] = 6;

	tmp[2][0] = 7;
	tmp[2][1] = 8;
	tmp[2][2] = 9;

	Vector3 result = tmp * v;

	printf("\n%.2f,%.2f,%.2f\n", result.get(0), result.get(1), result.get(2));

	Matrix::getIdentity(5).print();

}

void testCubeSphereCollision(MainWindow * window) {

	Cube cube(50);
	Sphere sphere(20);
	bool collide;

	cube.setPosition(Vector3(0, 0, 10));

	Uint8 * keystate;

	real rv = 0;

	while (window->Refresh(0)) {

		// Move sphere
		keystate = SDL_GetKeyState(NULL);
		real vel = 1;
		if (keystate[SDLK_s])
			sphere.translate(Vector3(vel, 0, 0));
		if (keystate[SDLK_w])
			sphere.translate(Vector3(-vel, 0, 0));
		if (keystate[SDLK_d])
			sphere.translate(Vector3(0, 0, -vel));
		if (keystate[SDLK_a])
			sphere.translate(Vector3(0, 0, vel));
		if (keystate[SDLK_q]) {
			cube.setRotation(Vector3(0, rv, 0));
			rv += 0.1;
		}

		// Check collision
		collide = cube.intersection(&sphere).hasIntersected();

		// Color feedback for collision
		if (collide)
			glColor3f(1, 0, 0);
		else
			glColor3f(1, 1, 1);

		// Draw sphere
		Vector3 p = sphere.getPosition();
		glTranslatef(p.getX(), p.getY(), p.getZ());
		//glutWireSphere(2, 5, 5);
		glutWireSphere(sphere.getRadius(), 20, 20);
		glTranslatef(-p.getX(), -p.getY(), -p.getZ());

		// Draw Cube (esta es mas facil jaja)
		Vector3 pp = cube.getPosition();
		Vector3 rotation = cube.getRotation();
		real degrees = rotation.magnitude() * 180 / 3.1415;
		glTranslatef(pp.getX(), pp.getY(), pp.getZ());
		glRotatef(degrees, rotation.getX(), rotation.getY(), rotation.getZ());
		glutWireSphere(2, 5, 5); // Centro
		glutWireCube(cube.getLength()); // Centro
		glTranslatef(-pp.getX(), -pp.getY(), -pp.getZ());
	}
}

void testOctreeDynamic(MainWindow * window) {

	ParticleWorld world(.15);

	Octree<Particle> octree(Vector3(0, 0, 0), 1, 500, true);

	ParticleRope rope(&world, Vector3(10, 10, 250), Vector3(10, 10, -250), .1,
			15);

	world.updateForces();

	list<Particle *> particles = rope.getRope();

	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++)
		octree.put(*p);

	timeval elapsed;
	long miliseconds;
	int qty = 0, avg = 0;

	//octree.resize(500);

	while (window->Refresh(0)) {

		gettimeofday(&elapsed, NULL);
		miliseconds = elapsed.tv_sec * 1000 + elapsed.tv_usec / 1000.0;

		world.runPhysics();

		octree.update();
		//octree.render(NULL, true);

		world.render();

		gettimeofday(&elapsed, NULL);
		miliseconds = elapsed.tv_sec * 1000 + elapsed.tv_usec / 1000
				- miliseconds;
		avg += miliseconds;
		qty++;

		//	printf("%ld, avg: %f\n", miliseconds, avg/(double)qty);

	}

	// avg: 12.417417 CON OCTREE DINAMICO ACTIVADO Y RENDERIZANDO JAJAJA FAIL
	// igual todo bien, nunca va a hacer falta mostrar el octree.

	// avg: 0.860000  CON OCTREE DINAMICO ACTIVADO PERO SIN RENDERIZAR
	// avg: 0.719403 SIN OCTREE DINAMICO (PERO CREADO). GENIAL! , EL APORTE DEL OCTREE ES BAJO! =D

	// avg: 0.449023 sin octree renderizado + centrado
	// avg: 1.143808
	// avg: 1.167192

	// avg: 20.908555 renderizado + centrado
	// avg: 22.356190

	// avg: 19.341158 renderizado + sin centrar

	// avg: 0.442927 sin octree rederizado + sin centrar
	// avg: 1.062865

	// avg: 9.336614 renderizado con size adapt
	// avg: 9.638686

	// avg: 0.395604 sin renderizad con size adapt
	// avg: 0.365103

	// avg: 0.333333 sin renderizar sin size adapt
	// avg: 0.389172

	// avg: 7.136000 renderizado sin size adapt
	// avg: 7.295318

	printf("avg: %f\n", avg / (double) qty);
}

void testOctreeIntersection(MainWindow * window) {

	ParticleWorld world(.05);

	Octree<Particle> octree(Vector3(0, 0, 0), 1, 200);

	Sphere sphere(50);

	Uint8 * keystate;

	//world.addField(new ConstantForce(.5, Vector3(0, 1, 0)));

	list<Particle *> particles;

	int mx, my;

	while (window->Refresh(0)) {

		// Move sphere
		keystate = SDL_GetKeyState(NULL);
		real vel = 5;
		if (keystate[SDLK_w])
			sphere.translate(Vector3(0, vel, 0));
		if (keystate[SDLK_s])
			sphere.translate(Vector3(0, -vel, 0));
		if (keystate[SDLK_d])
			sphere.translate(Vector3(0, 0, -vel));
		if (keystate[SDLK_a])
			sphere.translate(Vector3(0, 0, vel));

		Uint8 ms = SDL_GetMouseState(&mx, &my);
		if (ms & SDL_BUTTON(SDL_BUTTON_LEFT)) {

			Particle * p = world.addParticle(1, Vector3((rand() % 200) - 110,
					(rand() % 200) - 110, (rand() % 200) - 110));

			octree.put(p);
			particles.push_back(p);
		}

		Vector3 p = sphere.getPosition();
		glTranslatef(p.getX(), p.getY(), p.getZ());
		glutWireSphere(sphere.getRadius(), 20, 20);
		glTranslatef(-p.getX(), -p.getY(), -p.getZ());

		// PROBAR TRUE O FALSE, MUESTRA LO DEMAS O NO
		//octree.render(NULL, true);

		//printf("Elements: %d Nodes:%d \n", octree.size(), octree.nodeCount());

		world.runPhysics();
	}
}

class testNode: public tr1::enable_shared_from_this<testNode> {

	public:
		tr1::shared_ptr<testNode> getThisPtr() {
			tr1::shared_ptr<testNode> out = shared_from_this();
			cout << "Al existir ambos, el count es: " << out.use_count()
					<< endl;
			return out;
		}

};

void testSafePointers() {

	int * ip1 = new int(1);

	// ESTO TIENE QUE PINCHAR:
	// porque apuntan al mismo lugar sin conocerse entre si
	// por lo que cuando termina, un shared se destruye
	// y el otro tiene basura, y SEGFAULT!!
	tr1::shared_ptr<int> i1(ip1);
	cout << i1.use_count() << endl;
	//tr1::shared_ptr<int> i2(ip1);

	//cout << i2.use_count() << endl;
	cout << i1.use_count() << endl;

	tr1::shared_ptr<testNode> node1(new testNode());

	cout << node1.get() << " Y this: " << node1->getThisPtr().get() << endl;
	if (node1.get() == node1->getThisPtr().get())
		cout << "Son iguales !! yay" << endl;

}

void testParticleCollision(MainWindow * window) {

	ParticleWorld world(.25);

	srand(time(NULL));
	int qty = 100;
	real outerRadius = 300;
	real innerRadius = 245;
	Vector3 center = Vector3(0, 0, 0);

	for (int i = 0; i < qty; i++) {
		real r = innerRadius + (fabs(outerRadius - innerRadius) * (rand()
				/ (double) RAND_MAX));
		real theta = 2 * 3.1415 * (rand() / (double) RAND_MAX);
		real phi = 3.1415 * (rand() / (double) RAND_MAX);

		Vector3 position(r * cos(theta), r * sin(theta), 0);
		position += center;

		world.addParticle(1, position);

	}

	world.addParticle(1.0 / 5, Vector3());

	world.addPerParticleInteraction(new GravitationalForce());
	world.updateForces();

	int time = SDL_GetTicks();
	int nextTime;
	int qtyFrames = 0;
	real avg = 0;

	while (window->Refresh(0)) {

		world.runPhysics();
		world.render();

		nextTime = SDL_GetTicks() - time;
		time = time + nextTime;

		// Pareciera que las colisiones solo afectan en 5-7 fps
		//printf("FPS: %.2f\n", 1000.0 / nextTime);

		avg += 1000.0 / nextTime;
		qtyFrames++;

	}

	printf("Average framerate: %f\n", avg / qtyFrames);

	// El octree hace efecto solo en las colisiones, OJO

	// Average framerate: 25.377089 con gravedad + colisiones con octree, 50 particulas
	// Average framerate: 15.646843 con gravedad + colisiones SIN octree, 50 particulas

	// Average framerate: 5.709004 con gravedad + colisiones SIN octree, 100 particulas
	// Average framerate: 12.892283 con gravedad + colisiones con octree, 100 particulas

	// Buena onda, el octree es mucho mejor =D
}

int main(int argc, char *argv[]) {

	MainWindow window(1200, 600);
	glutInit(&argc, (char**) argv);
	srand(time(NULL));

	//testMatrixClass();
	//return 0;

	//testSafePointers();
	//return 0;

	testParticleCollision(&window);
	return 0;
	/*
	 testOctreeDynamic(&window);
	 return 0;

	 /*
	 testOctreeIntersection(&window);
	 return 0;

	 testCubeSphereCollision(&window);
	 return 0;

	 testPlaneSphereCollision(&window);
	 return 0;

	 ParticleWorld world(.08);

	 DirectionalEmitter e1 = DirectionalEmitter(&world, Vector3(-100, 0, 0),
	 Vector3(0, -1, 0), .4, 0, 10, 1);

	 world.addEmitter(&e1);

	 world.addField(new ConstantForce(.5, Vector3(0, 1, 0)));

	 /*
	 ParticleBridge bridge(&world, Vector3(-500, 0, 0), Vector3(-100, 0, 0),
	 100, .015, 50);

	 ParticleBridge bridge2(&world, Vector3(-500, -300, 0),
	 Vector3(500, -300, 0), 50, .15, 120);

	 /*
	 Particle * ropeBase = (rope.getRope().front());
	 ParticleData data = ropeBase->getData();

	 //	Particle * p =	world.addParticle(1, Vector3(0, 50, 0), Vector3(10,-40,0));

	 //world.addParticleInteraction(p, NULL, new ConstantForce(10, Vector3(0,1,0)));


	 /*world.addParticle(1 / (double) 80000, Vector3(150, 0, 0),
	 Vector3(150, 0, 0));
	 /*
	 for (int i = 0; i < 100; i++) {
	 world.addParticle(1 / 5.0, Vector3(-50 + rand() % 100, -50 + rand()
	 % 100, 0), Vector3(-5 + rand() % 10, -5 + rand() % 10, 0));
	 }

	 /*
	 for (int r = 1; r < 4; r++)
	 for (double angle = 0; angle < 2 * 3.14; angle += 0.1)
	 world.addParticle(1 / 2.0, Vector3(-150 + cos(angle) * 50 * r, sin(
	 angle) * r * 50, 0));
	 *
	 //world.addWorldInteraction(new ConstantForce(9.81, Vector3(0,-1,0)));

	 //		world.addPerParticleInteraction(new GravitationalForce());

	 //	world.addSpring(Vector3(-100,0,0),Vector3(100,0,0),
	 //		1, 5, 100);

	 //world.addSpringCircle(Vector3(0, 0, 0), 300, 1 / 50.0, 100, 50);

	 //world.addPerParticleInteraction(new FlashGravityForce());

	 world.updateForces();

	 world.printParticles();

	 Octree<Particle> octree(Vector3(0, 0, 0), 7, 500);

	 world.addField(new ConstantForce(.5, Vector3(0, 1, 0)));

	 list<Particle *> particles;

	 double angle = 0;
	 int mx, my;

	 while (window.Refresh(0)) {

	 Uint8 ms = SDL_GetMouseState(&mx, &my);
	 if (ms & SDL_BUTTON(SDL_BUTTON_LEFT)) {

	 Particle * p = world.addParticle(1, Vector3((rand() % 200) - 110,
	 (rand() % 200) - 110, (rand() % 200) - 110));

	 octree.put(p);
	 particles.push_back(p);
	 }

	 glRotatef(angle++, 0, 1, 0);
	 glutWireCube(510);
	 //		octree.render();

	 //printf("Elements: %d Nodes:%d \n", octree.size(), octree.nodeCount());

	 /*
	 data.setPosition(Vector3(data.getPosition().getX(),
	 sin(world.getTime()*4)*150, data.getPosition().getZ()));
	 ropeBase->setData(data);
	 *
	 //world.render();
	 world.runPhysics();

	 }*/

	return 1;
}
