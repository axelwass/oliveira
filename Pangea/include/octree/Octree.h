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

// OPTIMIZACION!
// TODO: Usar punteros mas seguros (boost::sharedptr) para evitar problemas!
// TODO: Destruccion de nodos bien hecha
// TODO: Pasar todos los metodos al octree, hacer al nodo liviano!
template<class T>
class Octree {

	protected:

		class Node {

			private:

				// To clarify code
				typedef typename list<Node *>::iterator NodeIterator;
				typedef typename list<Positionable<T> *>::iterator
						ElementIterator;

				Node * parent;
				Vector3 center;
				double size;

				// 8 in this case
				list<Node *> children;

				// Elements if this is leaf
				list<Positionable<T> *> elements;

				// Inner node is private
				Node(Node * parent, const Vector3 center) {
					this->parent = parent;
					this->center = center;
					this->size = this->parent->size / 2.0;
				}

			public:

				// TODO: Al eliminar un nodo, borrar tambien el subarbol abajo
				~Node() {
					printf("Mori\n");
				}

				// Root node is public
				Node(const Vector3 center, double size) {
					this->parent = NULL;
					this->center = center;
					this->size = size;
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

				void setCenter(const Vector3& center) {
					this->center = center;
				}

				double getSize() const {
					return size;
				}

				void setSize(double size) {
					this->size = size;
				}

				bool isLeaf() {
					return children.empty();
				}

				void setLeafElements(list<Positionable<T> *> * elements) {
					this->elements = list<Positionable<T> *> (*elements);
				}

				// If this node is not leaf, list is empty
				list<Positionable<T> *> * getLeafElements() {
					return &elements;
				}

				// Get all elements under this node
				list<Positionable<T> *> getSubtreeElements() {

					// If leaf, return copy of elements
					if (this->isLeaf())
						return list<Positionable<T> *> (elements);

					// If not, get children elements and return them all
					else {
						// Accumulator  list
						list<Positionable<T> *> out;

						NodeIterator itr;

						for (itr = children.begin(); itr != children.end(); itr++) {
							list<Positionable<T> *> childList =
									(*itr)->getSubtreeElements();

							ElementIterator elem;
							for (elem = childList.begin(); elem
									!= childList.end(); elem++)
								out.push_back(*elem);

						}

						return out;
					}
				}

				// Returns true if the point falls inside the node's boundaries (cubic),
				// regardless of the point's position in the tree.
				bool containsPoint(Vector3 p) {

					real border = this->size / 2.0;

					real distX = fabs(p.getX() - this->center.getX());
					real distY = fabs(p.getY() - this->center.getY());
					real distZ = fabs(p.getZ() - this->center.getZ());

					if (distX - border < EPSILON && distY - border < EPSILON
							&& distZ - border < EPSILON)
						return true;
					else
						return false;

				}

				bool addElement(Positionable<T> * elem, int threshold) {
					if (!containsPoint(elem->getPosition()))
						return false;

					// If node is leaf, just add and check threshold
					if (this->isLeaf()) {
						elements.push_back(elem);

						if (elements.size() > (unsigned) threshold) {
							//	printf("Partition!\n");
							partition(threshold);
						}
						return true;
					} else {
						// If node is not leaf, add it to one of its children
						NodeIterator itr;
						for (itr = children.begin(); itr != children.end(); itr++)
							// If it had success, return
							if ((*itr)->addElement(elem, threshold))
								return true;

						return false;
					}
				}

				void partition(int threshold) {

					// x,y,z
					int movArray[8][3] = { { 1, 1, -1 }, { 1, -1, -1 }, { -1,
							1, -1 }, { -1, -1, -1 }, { 1, 1, 1 }, { 1, -1, 1 },
							{ -1, 1, 1 }, { -1, -1, 1 } };

					// Half of half node
					double halfSize = this->size / 4.0;

					Node * child;

					for (int i = 0; i < 8; i++) {

						// Use a movement array to get a direction vector
						Vector3 dir(movArray[i][0], movArray[i][1],
								movArray[i][2]);

						dir *= halfSize;

						Vector3 childCenter = this->center + dir;

						// Create child
						child = new Node(this, childCenter);

						// And add elements if possible
						ElementIterator itr;
						for (itr = elements.begin(); itr != elements.end(); itr++)
							if (child->addElement(*itr, threshold)) {
								itr = elements.erase(itr);
								itr--;
							}

						this->children.push_back(child);
					}

					if (!elements.empty()) {
						printf(
								"NO PASE TODOS!!! ES EL FIN DEL FUCKING MUNDOOO ( NODO DESACTUALIZADO ) %d\n",
								elements.size());

						if (containsPoint(elements.front()->getPosition()))
							printf("CARAJO, HAY ALGO FUNDAMENTALMENTE MAL \n");
					}
				}
		};

		// OCTREE WRAPPER STARTS HERE

		// To clarify code, on Octree
		typedef typename list<Node *>::iterator NodeIterator;
		typedef typename list<Positionable<T> *>::iterator ElementIterator;

		Node * root; // root node
		bool sizeAdaptive; // resizable cube
		int threshold;

		// For access of lost elements in update (out of root range elements)
		list<Positionable<T> *> lostElements;

		// For access of elements that need to be updated
		// A hashmap would be excelent here, element <-> parent, element as key
		list<Positionable<T> *> outdatedElements;

		// For rapid access to elements
		list<Positionable<T> *> octreeElements;

		void renderNode(Node * node) {

			glTranslatef(node->getCenter().getX(), node->getCenter().getY(),
					node->getCenter().getZ());

			if (node->isLeaf() && getElementCount(node) > 0)
				glColor4f(1.0, 0, 0, 0.1);
			else
				glColor4f(1.0, 1.0, 1.0, 0.05);
			if (node->isLeaf())
				glutWireCube(node->getSize());

			glTranslatef(-node->getCenter().getX(), -node->getCenter().getY(),
					-node->getCenter().getZ());

			glColor3f(1.0, .5, .5);
			if (node->isLeaf()) {
				ElementIterator vitr;
				for (vitr = node->getLeafElements()->begin(); vitr
						!= node->getLeafElements()->end(); vitr++) {

					Vector3 p = (*vitr)->getPosition();
					glTranslatef(p.getX(), p.getY(), p.getZ());
					glutWireSphere(4, 5, 5);
					glTranslatef(-p.getX(), -p.getY(), -p.getZ());

				}

			} else {

				NodeIterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					renderNode(*itr);

			}
			glColor3f(1.0, 1.0, 1.0);
		}

		int getElementCount(Node * node) {

			if (node->isLeaf()) {
				return node->getLeafElements()->size();
			} else {

				int out = 0;

				NodeIterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					out += getElementCount(*itr);

				return out;
			}
		}

		int childCount(Node * node) {

			if (node->isLeaf()) {
				return 0;
			} else {
				int out = 0;

				NodeIterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					out += childCount(*itr) + 1;

				return out;
			}
		}

		// Check if child nodes are useless
		void checkThreshold(Node * node) {

			// If it is under threshold, remove children
			if (getElementCount(node) <= threshold) {

				// Get all elements
				list<Positionable<T> *> elements = node->getSubtreeElements();

				// And give all elements to node
				node->setLeafElements(&elements);

				// Erase children nodes. (so it is now a leaf)
				node->getChildren()->clear();

			} else {
				// Or go down one level
				NodeIterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					checkThreshold(*itr);
			}
		}

		/*
		 * THIS FUNCTION MUST USE A HASHMAP. UNTIL THEN, its losing
		 * a big chance of optimization
		 * Note: it must be recursive despite not using a map, because
		 * it checks if element fell outside root recursively.
		 */
		bool repositionElement(Node * node, Positionable<T> * elem) {

			if (node == NULL || elem == NULL)
				return false;

			Node * parent = node->getParent();

			// If element falls outside root, store it to add it later.
			if (parent == NULL) {
				// Add this element to out of range list
				lostElements.push_back(elem);
				return true;
			}

			// Try to add it to its parent
			if (parent->containsPoint(elem->getPosition())) {
				// Add this element to outdated list
				outdatedElements.push_back(elem);
				return true;
			} else
				// Go up one step, retry
				return repositionElement(parent, elem);
		}

		// This method updates the subtree below the given node
		void updateNode(Node * node) {
			if (node == NULL)
				return;

			// If node contains elements
			if (node->isLeaf()) {

				// Update each element
				ElementIterator elem;
				for (elem = node->getLeafElements()->begin(); elem
						!= node->getLeafElements()->end(); elem++) {
					// Update only if element moved away from node's range
					if (!node->containsPoint((*elem)->getPosition()))
						// If it was moved, erase element from node
						if (repositionElement(node, *elem)) {
							elem = node->getLeafElements()->erase(elem);
							elem--;
						}

				}
			} else {
				// Or go down one level
				NodeIterator itr;
				for (itr = node->getChildren()->begin(); itr
						!= node->getChildren()->end(); itr++)
					updateNode(*itr);
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
					NodeIterator itr;
					for (itr = node->getChildren()->begin(); itr
							!= node->getChildren()->end(); itr++) {

						list<Node *> tmp = getIntersectionLeaves(*itr, s);

						// Add those nodes to this list
						NodeIterator tmpItr;
						for (tmpItr = tmp.begin(); tmpItr != tmp.end(); tmpItr++)
							out.push_back(*tmpItr);
					}
				}
			}
			return out;
		}

		// Translates subtree
		void translateNode(Node * node, Vector3 t) {
			if (node == NULL)
				return;

			// Move node
			node->setCenter(node->getCenter() + t);

			// If it has children, move them too
			NodeIterator itr;
			for (itr = node->getChildren()->begin(); itr
					!= node->getChildren()->end(); itr++)
				translateNode(*itr, t);
		}

		// Centers root node
		void centerOctree() {
			Vector3 center;
			ElementIterator elem;
			for (elem = octreeElements.begin(); elem != octreeElements.end(); elem++)
				center += (*elem)->getPosition();

			center *= (1.0 / octreeElements.size());
			Vector3 distToRoot = center - root->getCenter();
			translateNode(root, distToRoot);
		}

		void restoreOutdatedElements() {
			ElementIterator elem;
			for (elem = outdatedElements.begin(); elem
					!= outdatedElements.end(); elem++)
				if (this->root->addElement(*elem, threshold)) {
					elem = outdatedElements.erase(elem);
					elem--;
				}
		}

		// Checks if previous out-of-range nodes are inside root range
		void recoverLostNodes() {
			//printf("%d\n", lostElements.size());
			ElementIterator elem;
			for (elem = lostElements.begin(); elem != lostElements.end(); elem++)
				// Add element to root and erase it from lostElements if successful
				if (root->addElement(*elem, threshold)) {
					elem = lostElements.erase(elem);
					elem--;
				}
		}

		// Resize subtree!
		// Note: MUST resize whole octree, CANNOT be used on independent nodes or it will return earlier
		void resizeNode(Node * node, double size) {
			if (node == NULL)
				return;

			// If node is not root and its parent has adequate size
			if (node->getParent() != NULL && ((node->getParent()->getSize()
					/ 2.0) - size > EPSILON))
				return;

			// Resize node over its own position
			node->setSize(size);

			// If it has children, resize them too
			NodeIterator itr;
			for (itr = node->getChildren()->begin(); itr
					!= node->getChildren()->end(); itr++) {

				// But! calculate their new positions first
				real childHalfSize = size / 4.0;

				// Calculate vector towards parent so it scales it on that direction
				Vector3 distToParent = (*itr)->getCenter() - node->getCenter();

				// Get displacement magnitude and vector needed. sqrt(3) is because of cube hypotenuse
				real displ = distToParent.magnitude() - (childHalfSize
						* sqrt(3));

				Vector3 displVector = distToParent;
				displVector.normalize();
				displVector *= displ;

				// Set new center, actual center plus displacement
				Vector3 childCenter = (*itr)->getCenter() + displVector;
				(*itr)->setCenter(childCenter);

				// And resize child with half of this size
				resizeNode((*itr), size / 2.0);
			}
		}

	public:

		Octree(Vector3 center, int threshold, double size, bool sizeAdaptive =
				false) {
			root = new Node(center, size);

			this->threshold = threshold;
			this->sizeAdaptive = sizeAdaptive;
		}

		~Octree() {
			printf("Octree destruido\n");

			delete root;
		}

		void put(Positionable<T> * e) {
			root->addElement(e, threshold);
			octreeElements.push_back(e);
		}

		// JUST DEBUGGING
		void render(Shape * s, bool visible) {

			// Base rendering
			if (s == NULL || visible) {
				this->renderNode(root);
			} else {

				list<Node *> nodes = getIntersectionLeaves(root, s);

				// Print those nodes!
				NodeIterator itr;
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

		int treeSize() const {
			return root->getSize();
		}

		int getElementCount() const {
			return getElementCount(root);
		}

		int nodeCount() const {
			return childCount(root);
		}

		list<Positionable<T> > getIntersectionElements(Shape *s) {
			list<Node *> nodes = getIntersectionLeaves(root, s);

			list<Positionable<T> > out;

			NodeIterator itr;
			ElementIterator elemItr;

			for (itr = nodes.begin(); itr != nodes.end(); itr++)
				for (elemItr = (*itr).begin(); elemItr != (*itr).end(); elemItr++) {
					out.push_back(*elemItr);
				}

			return out;
		}

		bool isSizeAdaptive() const {
			return sizeAdaptive;
		}

		// It will resize and update every node to the new dimensions
		void resize(double size) {
			// If it is size adaptive, it will be resized afterwards, disabling this method effect
			if (sizeAdaptive)
				return;

			resizeNode(this->root, size);

			updateNode(this->root);
			restoreOutdatedElements();
			recoverLostNodes(); // in case it expands

			checkThreshold(this->root);
		}

		// This method will take the farthest out of range element and
		// resize octree so it will contain it
		void adaptSize(real maxDisplacement) {

			// If no need to resize, return
			if (lostElements.empty())
				return;

			Vector3 maximumDistance(0, 0, 0);

			// Plain maximum element search
			ElementIterator elem;
			for (elem = lostElements.begin(); elem != lostElements.end(); elem++) {
				Vector3 dist = (*elem)->getPosition() - this->root->getCenter();

				if (dist.magnitude() > maximumDistance.magnitude())
					maximumDistance = dist;
			}

			if (maximumDistance.magnitude() < this->root->getSize() / 2.0)
				printf("FAIL!\n");

			printf("Max: %f\n", maximumDistance.magnitude());

			// For now, just update size as if it was a sphere
			resizeNode(this->root, maximumDistance.magnitude()
					+ maxDisplacement);
		}

		/*
		 * If octree is dynamic, some elements
		 * must have moved from their original position. This
		 * means there are nodes containing elements that do not belong there.
		 * So we first resize all nodes if octree is adaptive,
		 * and then re position every element in each node.
		 * Resizing must be done first to prevent double updating.
		 * Besides, resizing just considers out of range elements, for optimization.
		 */
		void update() {

			// First, resize all nodes
			//	if (sizeAdaptive)
			//	adaptSize(1);


			// Order of function calls is CRITICAL.

			// Delete first
			updateNode(this->root);

			// Add later
			restoreOutdatedElements();
			recoverLostNodes();

			// Then re check all thresholds
			checkThreshold(this->root);
		}

};

#endif /* OCTREE_H_ */
