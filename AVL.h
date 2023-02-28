#ifndef AVL_H
#define AVL_H
#include "Node.h"
#include "AVLInterface.h"

using namespace std;

class AVL : public AVLInterface
{
private:
    Node *rootNode = nullptr;
    void clear(Node *currentNode);

    bool add(Node *&tracker, int data);
    bool remove(int data, Node *&currentNode);
    int updateHeight(Node *givenPointer);

    Node *leftRotate(Node *&localRoot);
    Node *rightRotate(Node *&localRoot);
    Node *leftRightRotate(Node *&localRoot);
    Node *rightLeftRotate(Node *&localRoot);

    int differenceInChildHeight(Node *givenPointer);
    void balanceTree(Node *&localRoot);

public:
    AVL(){};
    ~AVL();

    // Please note that the class that implements this interface must be made
    // of objects which implement the NodeInterface

    /*
     * Returns the root node for this tree
     *
     * @return the root node for this tree.
     */
    Node *getRootNode() const override;

    /*
     * Attempts to add the given int to the BST tree
     *
     * @return true if added
     * @return false if unsuccessful (i.e. the int is already in tree)
     */
    bool add(int data) override;

    /*
     * Attempts to remove the given int from the BST tree
     *
     * @return true if successfully removed
     * @return false if remove is unsuccessful(i.e. the int is not in the tree)
     */
    bool remove(int data);

    /*
     * Removes all nodes from the tree, resulting in an empty tree.
     */
    void clear();
};
#endif