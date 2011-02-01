/*
 * Octree.h
 *
 *  Created on: Jan 25, 2011
 *      Author: mmerchan
 */

#include "../Vector3.h"
#include "../shape/Shape.h"
#include "../shape/Cube.h"
#include "../Positionable.h"
#include <stdio.h>
#include <list>
using namespace std;

#ifndef OCTREE_H_
#define OCTREE_H_

template<class T>
class Octree {

	protected:

		class Node {

			private:

				Node * parent;
				Vector3 center;
				double size;

				// 8 in this case
				list<Node *> children;

				// Elements if this is leaf
				list<Positionable<T> *> elements;

				unsigned int threshold;

			public:

				// Root node
				Node(const Vector3 center, int threshold, double size) {
					this->parent = NULL;
					this->center = center;
					this->threshold = threshold;
					this->size = size;
				}

				// Inner node
				Node(Node * parent, const Vector3 center, int threshold = 10) {
					this->parent = parent;
					this->center = center;
					this->threshold = threshold;
					this->size = this->parent->size / 2.0;
				}

				list<Positionable<T> *> * getElements() {
					return &elements;
				}

				list<Node *> * getChildren() {
					return &children;
				}

				Node * getParent() {
					return parent;
				}

				Vector3 getCenter() {
					return center;
				}

				double getSize() {
					return size;
				}

				bool isLeaf() {
					return children.empty();
				}

				int getElementCount(Node * node) {

					if (node->isLeaf()) {
						return node->getElements()->size();
					} else {

						int out = 0;

						typename list<Node *>::iterator itr;
						for (itr = node->getChildren()->begin(); itr
								!= node->getChildren()->end(); itr++)
							out += getElementCount(*itr);

						return out;
					}
				}

				void addElement(Positionable<T> * elem) {

					// If node is leaf, just add and check threshold
					if (this->isLeaf()) {
						elements.push_back(elem);
						if (elements.size() >= threshold) {
							//	printf("Partition!\n");
							partition();
						}
					} else {

						// If node is not leaf, add it to one of its children
						typename list<Node *>::iterator itr;

						for (itr = children.begin(); itr != children.end(); itr++) {
							if ((*itr)->containsPoint(elem->getPosition())) {
								(*itr)->addElement(elem);

								// To prevent duplicates (although it should not happen)
								return;
							}
						}
					}

				}

				// Returns true if the point falls inside the node's boundaries (cubic),
				// regardless of the point's position in the tree.
				bool containsPoint(Vector3 p) {

					double dist = this->size / 2.0;

					if ((p.getX() <= this->center.getX() + dist) && (p.getX()
							> this->center.getX() - dist) && (p.getY()
							<= this->center.getY() + dist) && (p.getY()
							> this->center.getY() - dist) && (p.getZ()
							<= this->center.getZ() + dist) && (p.getZ()
							> this->center.getZ() - dist))
						return true;
					else
						return false;

				}

				// Check if child nodes are useless
				void checkThreshold() {

					if ((unsigned) getElementCount(this) < threshold) {

						typename list<Node *>::iterator itr;
						typename list<Positionable<T> *>::iterator elemItr;

						// Get all children elements and add them to this node
						for (itr = children.begin(); itr != children.end(); itr++) {

							list<Positionable<T> *> * childElements =
									(*itr)->getElements();

							if (childElements != NULL)
								for (elemItr = childElements->begin(); elemItr
										!= childElements->end(); elemItr++)
									elements.push_back(*elemItr);
						}

						// Erase children nodes.
						children.clear();
					}
				}

				// Reference to element may not be in same position as element (this is useful to update positions)
				bool deleteReference(Positionable<T> * elem, Vector3 position) {
					// WARNING: POSITION NOT NECESSARY = ELEM.POSITION
					if (this->containsPoint(position)) {

						if (this->isLeaf()) {

							// Remove reference, check threshold
							elements.remove(elem);

							if (parent != NULL)
								parent->checkThreshold();
							return true;

						} else {

							// Check for children
							typename list<Node *>::iterator itr;
							for (itr = children.begin(); itr != children.end(); itr++)
								if ((*itr)->deleteReference(elem, position))
									return true;
						}
					}

					return false;
				}

				void partition() {

					// x,y,z
					int movArray[8][3] = { { 1, 1, -1 }, { 1, -1, -1 }, { -1,
							1, -1 }, { -1, -1, -1 }, { 1, 1, 1 }, { 1, -1, 1 },
							{ -1, 1, 1 }, { -1, -1, 1 } };

					// Half of half node
					double halfSize = this->size / 4.0;

					//	printf("Node center(%g,%g,%g)\n", center.getX(), center.getY(),
					//		center.getZ());

					Node * child;

					for (int i = 0; i < 8; i++) {

						// Use a movement array to get a direction vector
						Vector3 dir(movArray[i][0], movArray[i][1],
								movArray[i][2]);

						dir *= halfSize;

						Vector3 childCenter = this->center + dir;

						//printf("Child center(%g,%g,%g)\n", childCenter.getX(), childCenter.getY(), childCenter.getZ());

						// Create child
						child = new Node(this, childCenter, this->threshold);

						//	printf("Parent size: %g\n", size);
						//	printf("Child size: %g\n", child->size);

						typename list<Positionable<T> *>::iterator itr;

						// And add elements if possible
						for (itr = elements.begin(); itr != elements.end(); itr++) {
							if (child->containsPoint((*itr)->getPosition())) {
								//		printf("Contains point!\n");
								child->addElement(*itr);
							}
						}

						this->children.push_back(child);

					}

					// After all, clear this node's elements, we don't need them
					this->elements.clear();
				}

				Node * findContainerNode(const Vector3 position) {

					if (this->containsPoint(position)) {

						if (this->isLeaf()) {
							return this;
						} else {

							typename list<Node *>::iterator itr;
							for (itr = children.begin(); itr != children.end(); itr++) {
								Node * n = (*itr)->findContainerNode(position);

								//bool contains = (*itr)->containsPoint(position);

								//	printf("%p, %s\n", n, contains ? "true"
								//										: "false");

								if (n != NULL)
									return n;
							}
						}

						// THIS SHOULD NOT HAPPEN
						printf("Error que no entiendo!\n");
					}

					return NULL;
				}

		};

		Node * root;

		void renderNode(Node * node) {

			glTranslatef(node->getCenter().getX(), node->getCenter().getY(),
					node->getCenter().getZ());

			if (node->isLeaf() && node->getElementCount(node) > 0)
				glColor3f(1.0, 0, 0);
			else
				glColor3f(1.0, 1.0, 1.0);
			if (node->isLeaf())
				glutWireCube(node->getSize());
			glutWireSphere(5, 5, 5);

			glTranslatef(-node->getCenter().getX(), -node->getCenter().getY(),
					-node->getCenter().getZ());

			glColor3f(1.0, .5, .5);
			if (node->isLeaf()) {
				typename list<Positionable<T> *>::iterator vitr;
				for (vitr = node->getElements()->begin(); vitr
						!= node->getElements()->end(); vitr++) {

					Vector3 p = (*vitr)->getPosition();

					glTranslatef(p.getX(), p.getY(), p.getZ());
					glutWireSphere(2, 5, 5);
					glTranslatef(-p.getX(), -p.getY(), -p.getZ());

				}

			} else {

				typename list<Node *>::iterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					renderNode(*itr);

			}
			glColor3f(1.0, 1.0, 1.0);
		}

		int childCount(Node * node) {

			if (node->isLeaf()) {
				return 0;
			} else {
				int out = 0;

				typename list<Node *>::iterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					out += childCount(*itr) + 1;

				return out;
			}
		}

		// CONTAINER IS ASSUMED TO BE THE PREVIOUS STATE'S CONTAINER
		void updateElement(Node * container, Positionable<T> * elem,
				Vector3 prev) {

			// If element moved from this voxel
			if (!container->containsPoint(elem->getPosition())) {

				Node * parent = container->getParent();
				// To be safe
				if (parent == NULL)
					return;

				// Check for related voxels
				if (parent->containsPoint(elem->getPosition())) {

					// If it exists, then erase the elem in the container
					container->deleteReference(elem, prev);

					// And try to add it to its parent
					parent->addElement(elem);

				} else {

					// Go up one step, retry
					updateElement(parent, elem, prev);
				}
			}

		}

		list<Node *> getIntersectionLeaves(Node * node, Shape * s) {

			list<Node *> out;

			Cube cube(node->getSize());
			cube.setPosition(node->getCenter());

			if (cube.intersection(s) != NULL) {

				if (node->isLeaf()) {
					out.push_back(node);
					return out;
				} else {

					// Get children nodes that intersect
					typename list<Node *>::iterator itr;
					for (itr = node->getChildren()->begin(); itr
							!= node->getChildren()->end(); itr++) {

						list<Node *> tmp = getIntersectionLeaves(*itr, s);

						// Add those nodes to this list
						typename list<Node *>::iterator tmpItr;
						for (tmpItr = tmp.begin(); tmpItr != tmp.end(); tmpItr++)
							out.push_back(*tmpItr);

					}
				}
			} //else printf("No colisiona!\n");

			return out;
		}

	public:

		Octree(Vector3 center, int threshold, double size) {
			root = new Node(center, threshold, size);
		}

		void addElement(Positionable<T> * e) {
			root->addElement(e);
		}

		void render(Shape * s, bool visible) {

			if (visible)
				this->renderNode(root);

			// Base rendering
			if (s == NULL) {
				this->renderNode(root);
			} else {

				list<Node *> nodes = getIntersectionLeaves(root, s);

				// Print those nodes!
				typename list<Node *>::iterator itr;
				for (itr = nodes.begin(); itr != nodes.end(); itr++) {

					//renderNode(*itr);

					glTranslatef((*itr)->getCenter().getX(),
							(*itr)->getCenter().getY(),
							(*itr)->getCenter().getZ());

					glColor3f(.2, .2, 1);
					glutWireCube((*itr)->getSize());
					glColor3f(1.0, 1.0, 1.0);

					glTranslatef(-(*itr)->getCenter().getX(),
							-(*itr)->getCenter().getY(),
							-(*itr)->getCenter().getZ());
				}
			}
		}

		int size() {
			return getElementCount(root);
		}

		int nodeCount() {
			return childCount(root);
		}

		list<Positionable<T> > getIntersectionElements(Shape *s) {
			list<Node *> nodes = getIntersectionLeaves(root, s);
		}

		void updateElement(Positionable<T> * elem, Vector3 prevPosition) {

			if (!root->containsPoint(elem->getPosition())) {
				root->deleteReference(elem, prevPosition);
				return;
			}

			Node * container = root->findContainerNode(prevPosition);

			/*printf("(%g,%g,%g)\n", prevPosition.getX(), prevPosition.getY(),
			 prevPosition.getZ());
			 */
			//			printf("%p\n", container);

			if (container != NULL) {
				updateElement(container, elem, prevPosition);
			} else {
				//	getchar();
			}
		}
};

#endif /* OCTREE_H_ */
