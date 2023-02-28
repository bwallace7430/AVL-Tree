#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface
{
private:
    int data;
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
    int height = 0;

public:
    Node(int value) : data(value) {}
    ~Node() {}

    /*
     * Returns the data that is stored in this node
     *
     * @return the data that is stored in this node.
     */
    int getData() const override;
    void setData(int newData);

    /*
     * Returns the left child of this node or null if it doesn't have one.
     *
     * @return the left child of this node or null if it doesn't have one.
     */
    Node *getLeftChild() const override;
    Node *&getLeftChild();

    /*
     * Returns the right child of this node or null if it doesn't have one.
     *
     * @return the right child of this node or null if it doesn't have one.
     */
    Node *getRightChild() const override;
    Node *&getRightChild();

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
    int getHeight() override;
    void setHeight(int value);
};

int safeGetHeight(Node *givenPointer);
#endif