#include <iostream>
#include "Node.h"

using namespace std;

/*
 * Returns the data that is stored in this node
 *
 * @return the data that is stored in this node.
 */
int Node::getData() const { return data; }
void Node::setData(int newData)
{
    data = newData;
}

/*
 * Returns the left child of this node or null if it doesn't have one.
 *
 * @return the left child of this node or null if it doesn't have one.
 */
Node *Node::getLeftChild() const { return leftChild; }
Node *&Node::getLeftChild() { return leftChild; }

/*
 * Returns the right child of this node or null if it doesn't have one.
 *
 * @return the right child of this node or null if it doesn't have one.
 */
Node *Node::getRightChild() const { return rightChild; }
Node *&Node::getRightChild() { return rightChild; }

/*
 * Returns the height of this node. The height is the number of nodes
 * along the longest path from this node to a leaf.  While a conventional
 * interface only gives information on the functionality of a class and does
 * not comment on how a class should be implemented, this function has been
 * provided to point you in the right direction for your solution.  For an
 * example on height, see page 448 of the text book.
 *
 * @return the height of this tree with this node as the local root.
 */
int Node::getHeight() { return height; }
void Node::setHeight(int value) { height = value; }

int safeGetHeight(Node *givenPointer)
{
    if (givenPointer == nullptr)
    {
        return -1;
    }

    return givenPointer->getHeight();
}