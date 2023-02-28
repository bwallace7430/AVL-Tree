#include "Node.h"
#include "AVL.h"
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

// Please note that the class that implements this interface must be made
// of objects which implement the NodeInterface

AVL::~AVL()
{
    clear(rootNode);
}
/*
 * Returns the root node for this tree
 *
 * @return the root node for this tree.
 */
Node *AVL::getRootNode() const { return rootNode; }

void printTree(Node *);

/*
 * Attempts to add the given int to the BST tree
 *
 * @return true if added
 * @return false if unsuccessful (i.e. the int is already in tree)
 */
bool AVL::add(int data)
{
    return add(rootNode, data);
}

bool AVL::add(Node *&tracker, int data)
{
    cout << "Entering add function." << endl;

    if (tracker == nullptr) // check if you have reached the add position for new Node
    {
        cout << "creating new Node for: " << data << endl;
        tracker = new Node(data); // creating new Node w/given data at the tracker position
        return true;              // exit add function
    }

    if (data == tracker->getData()) // check if data being added is already in the tree
    {
        cout << "tracker data is: " << tracker->getData() << endl;
        cout << "data is: " << data << endl;
        cout << "data is already in tree. returning false." << endl;
        return false; // exit add function w/o adding node
    }

    bool added = false; // fast way to identify if a node is added

    if (data < tracker->getData()) // check which way we need to traverse
    {
        added = add(tracker->getLeftChild(), data); // traverse left
    }
    else
    {
        added = add(tracker->getRightChild(), data); // traverse right
    }

    if (added)
    {
        cout << "after adding data, tracker data is: " << tracker->getData() << endl;
        printTree(rootNode);   // print tree to see what we're working with
        balanceTree(tracker);  // checks if adding tracker has created an imbalance and rebalances
        updateHeight(tracker); // updates height (OF WHOLE TREE? JUST OF ONE?)
    }

    return added;
};

void printTree(Node *);

/*
 * Attempts to remove the given int from the BST tree
 *
 * @return true if successfully removed
 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
 */
bool AVL::remove(int data)
{
    if (rootNode != nullptr)
    {
        cout << "your rootNode is: " << rootNode->getData() << endl;
    }
    printTree(rootNode);
    cout << "in regular remove function for: " << data << endl;
    if (data == rootNode->getData())
    {
        if (rootNode->getLeftChild() == nullptr && rootNode->getRightChild() == nullptr) // node being removed has no children
        {
            delete rootNode;    // remove node
            rootNode = nullptr; // set as nullptr
            return true;        // node was removed
        }
        else if (rootNode->getLeftChild() == nullptr) // node being removed has right child
        {
            Node *temporary = rootNode;           // temporary now points to node being removed
            rootNode = rootNode->getRightChild(); // currents node's parent will now point to currentNode's right child
            delete temporary;                     // removes target node, sets temporary to nullptr

            balanceTree(rootNode);  // check for imbalances on the new child of parentNode
            updateHeight(rootNode); // update height of current node
            return true;            // node was removed
        }
        else if (rootNode->getRightChild() == nullptr) // node being removed has left child
        {
            Node *temporary = rootNode;          // temporary now points to node being removed
            rootNode = rootNode->getLeftChild(); // currentNode's parent will now point to currentNode's left child
            delete temporary;                    // removes target node, sets temporary to nullptr

            balanceTree(rootNode);
            updateHeight(rootNode);
            return true;
        }
        else // node being removed has two children
        {
            cout << "so you got this far" << endl;
            Node *temporary = rootNode->getLeftChild();
            Node *parent = nullptr;
            while (temporary->getRightChild() != nullptr)
            {
                parent = temporary;
                temporary = temporary->getRightChild();
            }

            rootNode->setData(temporary->getData());
            if (parent != nullptr)
            {
                parent->getRightChild() = temporary->getLeftChild();
            }
            else
            {
                rootNode->getLeftChild() = temporary->getLeftChild();
            }
            delete temporary;

            if (rootNode->getLeftChild() == parent)
            {
                balanceTree(parent);
                rootNode->getLeftChild() = parent;
            }
            else
            {
                balanceTree(parent); // come here
            }

            rootNode->getLeftChild() = parent;

            updateHeight(rootNode);

            balanceTree(rootNode);

            return true;
        }
    }
    printTree(rootNode);           // just to check what we're working with
    return remove(data, rootNode); // calls recursive remove function
}

bool AVL::remove(int data, Node *&parentNode)
{
    cout << "in recursive remove function for: " << data << endl;
    /*ORIGINAL CODE*/                 // Node *&currentNode = rootNode;    // TODO: fix this problem area. needs to be a pass by reference, can't be because we change what it is (WHY DO I HAVE THIS?)
    if (data > parentNode->getData()) // check to traverse right
    {
        cout << data << " is greater than " << parentNode->getData() << endl;
        cout << "traversing right" << endl;
        /*ORIGINAL CODE*/ // currentNode = parentNode->getRightChild(); // traverse right

        /*ORIGINAL CODE*/ // if (currentNode != nullptr) // just to check where we are in the tree

        /*NEW CODE STARTS HERE*/
        if (parentNode->getRightChild() != nullptr) // just to check where we are in the tree
        {
            cout << parentNode->getRightChild()->getData() << endl;
        }
        if (parentNode->getRightChild() == nullptr) // if where we traversed DNE, data is not in tree
        {
            cout << "data was not found. returning false." << endl;
            return false; // exit w/o removing a Node
        }
        else if (data == parentNode->getRightChild()->getData()) // we found node to remove
        {
            cout << "data was found." << endl;
            cout << "data wanted: " << data << endl;
            cout << "data found: " << parentNode->getRightChild()->getData() << endl;

            if (parentNode->getRightChild()->getLeftChild() == nullptr && parentNode->getRightChild()->getRightChild() == nullptr) // node being removed has no children
            {
                delete parentNode->getRightChild();    // remove node
                parentNode->getRightChild() = nullptr; // set as nullptr

                balanceTree(parentNode);  // check for imbalances and rebalance parentNode
                updateHeight(parentNode); // update heights
                return true;              // node was removed
            }
            else if (parentNode->getRightChild()->getLeftChild() == nullptr) // node being removed has right child
            {
                Node *temporary = parentNode->getRightChild();                              // temporary now points to node being removed
                parentNode->getRightChild() = parentNode->getRightChild()->getRightChild(); // currents node's parent will now point to parentNode->getRightChild()'s right child
                delete temporary;                                                           // removes target node, sets temporary to nullptr

                balanceTree(parentNode->getRightChild());  // check for imbalances on the new child of parentNode
                updateHeight(parentNode->getRightChild()); // update height of current node
                updateHeight(parentNode);                  // update height of parent node
                return true;                               // node was removed
            }
            else if (parentNode->getRightChild()->getRightChild() == nullptr) // node being removed has left child
            {
                Node *temporary = parentNode->getRightChild(); // temporary now points to node being removed
                cout << "before: " << parentNode->getRightChild()->getData() << endl;
                parentNode->getRightChild() = parentNode->getRightChild()->getLeftChild(); // parentNode->getRightChild()'s parent will now point to parentNode->getRightChild()'s left child
                cout << "after: " << parentNode->getRightChild()->getData() << endl;
                delete temporary; // removes target node, sets temporary to nullptr

                cout << "temporary has been deleted." << endl;
                printTree(rootNode); // just to check and see that it was deleted properly

                balanceTree(parentNode->getRightChild()); // find imbalances from node being removed
                cout << "done" << endl;
                updateHeight(parentNode->getRightChild()); // update height
                cout << "whee" << endl;
                cout << parentNode->getData() << endl;
                updateHeight(parentNode); // update height

                return true;
            }
            else // node has two children
            {
                Node *temporary = parentNode->getRightChild()->getLeftChild(); // temporary will be the node that we want to set as the new root
                Node *parent = nullptr;                                        // parent will keep track of temporary's parent
                while (temporary->getRightChild() != nullptr)                  // if we haven't reached the rightmost node in the left tree of the node being removed (parentNode->getRightChild())
                {
                    parent = temporary;                     // parent traverses to temporary
                    temporary = temporary->getRightChild(); // temporary traverses right
                }

                parentNode->getRightChild()->setData(temporary->getData()); // the data in temporary becomes the new local root
                if (parent != nullptr)                                      // if the tree is small, there may not be a parent. gotta check.
                {
                    parent->getRightChild() = temporary->getLeftChild(); // temporary was the last right child. it has no right children. if it had left children, they are now right children.
                }
                else // there is no parent. this tree is muy smol.
                {
                    parentNode->getRightChild()->getLeftChild() = temporary->getLeftChild(); // temporary was the last right child. it has no right children. this makes sense but idk how to explain. i worked it out, i promise.
                }
                delete temporary; // get rid of temporary

                balanceTree(parentNode->getRightChild()); // rebalance the local root

                updateHeight(parentNode->getRightChild()); // update heights
                updateHeight(parent);
                updateHeight(parentNode);
                return true; // return after removing
            }
        }
        else
        {
            remove(data, parentNode->getRightChild());
        } /*NEW CODE ENDS HERE*/
    }
    else if (data < parentNode->getData()) // check to traverse left
    {
        cout << data << "is less than " << parentNode->getData() << endl;
        cout << "traversing left" << endl;
        /*ORIGINAL CODE*/                          // currentNode = parentNode->getLeftChild(); // traverse left
        if (parentNode->getLeftChild() != nullptr) // just to check where we are in the tree
        {
            cout << parentNode->getLeftChild()->getData() << endl;
        }
        if (parentNode->getLeftChild() == nullptr) // if where we traversed DNE, data is not in tree
        {
            cout << "data was not found. returning false." << endl;
            return false; // exit w/o removing a Node
        }
        else if (data == parentNode->getLeftChild()->getData()) // we found node to remove
        {
            cout << "data was found." << endl;
            cout << "data wanted: " << data << endl;
            cout << "data found: " << parentNode->getLeftChild()->getData() << endl;

            if (parentNode->getLeftChild()->getLeftChild() == nullptr && parentNode->getLeftChild()->getRightChild() == nullptr) // node being removed has no children
            {
                delete parentNode->getLeftChild();    // remove node
                parentNode->getLeftChild() = nullptr; // set as nullptr

                balanceTree(parentNode);  // check for imbalances and rebalance parentNode
                updateHeight(parentNode); // update heights
                return true;              // node was removed
            }
            else if (parentNode->getLeftChild()->getLeftChild() == nullptr) // node being removed has right child
            {
                Node *temporary = parentNode->getLeftChild();                             // temporary now points to node being removed
                parentNode->getLeftChild() = parentNode->getLeftChild()->getRightChild(); // currents node's parent will now point to parentNode->getLeftChild()'s right child
                delete temporary;                                                         // removes target node, sets temporary to nullptr

                balanceTree(parentNode->getLeftChild());  // check for imbalances on the new child of parentNode
                updateHeight(parentNode->getLeftChild()); // update height of current node
                updateHeight(parentNode);                 // update height of parent node
                return true;                              // node was removed
            }
            else if (parentNode->getLeftChild()->getRightChild() == nullptr) // node being removed has right child
            {
                Node *temporary = parentNode->getLeftChild(); // temporary now points to node being removed
                cout << "before: " << parentNode->getLeftChild()->getData() << endl;
                parentNode->getLeftChild() = parentNode->getLeftChild()->getLeftChild(); // parentNode->getLeftChild()'s parent will now point to parentNode->getLeftChild()'s right child
                cout << "after: " << parentNode->getLeftChild()->getData() << endl;
                delete temporary; // removes target node, sets temporary to nullptr

                cout << "temporary has been deleted." << endl;
                printTree(rootNode); // just to check and see that it was deleted properly

                balanceTree(parentNode->getLeftChild()); // find imbalances from node being removed
                cout << "done" << endl;
                updateHeight(parentNode->getLeftChild()); // update height
                cout << "whee" << endl;
                cout << parentNode->getData() << endl;
                updateHeight(parentNode); // update height

                return true;
            }
            else // node has two children
            {
                Node *temporary = parentNode->getLeftChild()->getLeftChild(); // temporary will be the node that we want to set as the new root
                Node *parent = nullptr;                                       // parent will keep track of temporary's parent
                while (temporary->getRightChild() != nullptr)                 // if we haven't reached the rightmost node in the left tree of the node being removed (parentNode->getLeftChild())
                {
                    parent = temporary;                     // parent traverses to temporary
                    temporary = temporary->getRightChild(); // temporary traverses right
                }

                parentNode->getLeftChild()->setData(temporary->getData()); // the data in temporary becomes the new local root
                if (parent != nullptr)                                     // if the tree is small, there may not be a parent. gotta check.
                {
                    parent->getRightChild() = temporary->getLeftChild(); // temporary was the last right child. it has no right children. if it had right children, they are now right children.
                }
                else // there is no parent. this tree is muy smol.
                {
                    parentNode->getLeftChild()->getLeftChild() = temporary->getLeftChild(); // temporary was the last right child. it has no right children. this makes sense but idk how to explain. i worked it out, i promise.
                }
                delete temporary; // get rid of temporary

                balanceTree(parentNode->getLeftChild()); // rebalance the local root

                updateHeight(parentNode->getLeftChild()); // update heights
                updateHeight(parent);
                updateHeight(parentNode);
                return true; // return after removing
            }
        }
        else
        {
            remove(data, parentNode->getLeftChild());
        }
    }
}

/*
 * Removes all nodes from the tree, resulting in an empty tree.
 */
void AVL::clear()
{
    clear(rootNode);
    rootNode = nullptr;
}

void AVL::clear(Node *currentNode)
{
    if (currentNode == nullptr)
    {
        return;
    }
    if (currentNode->getLeftChild() != nullptr)
    {
        clear(currentNode->getLeftChild());
    }
    else if (currentNode->getRightChild() != nullptr)
    {
        clear(currentNode->getRightChild());
    }
    delete currentNode;
}

int AVL::updateHeight(Node *givenPointer)
{
    cout << "in update height function" << endl;
    if (givenPointer == nullptr)
    {
        return -1;
    }

    int leftChildHeight = safeGetHeight(givenPointer->getLeftChild());
    int rightChildHeight = safeGetHeight(givenPointer->getRightChild());
    int maxChildHeight = max(leftChildHeight, rightChildHeight);
    givenPointer->setHeight(maxChildHeight + 1);

    cout << "height of data point " << givenPointer->getData() << " is: " << givenPointer->getHeight() << endl;
    return givenPointer->getHeight();
}

Node *AVL::rightRotate(Node *&localRoot)
{
    cout << "in right rotate function" << endl;
    Node *nodeBeingMoved = localRoot;

    localRoot = localRoot->getLeftChild();
    nodeBeingMoved->getLeftChild() = localRoot->getRightChild();
    localRoot->getRightChild() = nodeBeingMoved;

    if (localRoot->getLeftChild() != nullptr && localRoot->getRightChild() != nullptr)
    {
        cout << localRoot->getData() << " " << localRoot->getLeftChild()->getData() << " " << localRoot->getRightChild()->getData();
    }

    printTree(rootNode);
    updateHeight(nodeBeingMoved);
    updateHeight(localRoot);
}

Node *AVL::leftRotate(Node *&localRoot)
{
    cout << "in left rotate function" << endl;
    Node *nodeBeingMoved = localRoot;

    localRoot = localRoot->getRightChild();
    nodeBeingMoved->getRightChild() = localRoot->getLeftChild();
    localRoot->getLeftChild() = nodeBeingMoved;

    updateHeight(nodeBeingMoved);
    updateHeight(localRoot);
    printTree(rootNode);
}

Node *AVL::leftRightRotate(Node *&localRoot)
{
    cout << "in left right rotate function. tree is: " << endl;
    printTree(rootNode);
    leftRotate(localRoot->getLeftChild());
    cout << "finished leftRotate. tree is: " << endl;
    printTree(rootNode);
    rightRotate(localRoot);
}

Node *AVL::rightLeftRotate(Node *&localRoot)
{
    cout << "in right left rotate function. tree is: " << endl;
    printTree(rootNode);
    rightRotate(localRoot->getRightChild());
    cout << "finished rightRotate. tree is: " << endl;
    printTree(rootNode);
    leftRotate(localRoot);
}

void AVL::balanceTree(Node *&localRoot)
{
    cout << "balancing: " << localRoot->getData() << endl;
    if (differenceInChildHeight(localRoot) < -1)
    {
        cout << "imbalance found" << endl;
        if (differenceInChildHeight(localRoot->getLeftChild()) <= 0)
        {
            cout << "left left imbalance" << endl;
            rightRotate(localRoot);
        }
        else
        {
            cout << "left right imbalance" << endl;
            leftRightRotate(localRoot);
        }
    }

    else if (differenceInChildHeight(localRoot) > 1)
    {
        cout << "imbalance found" << endl;
        if (differenceInChildHeight(localRoot->getRightChild()) >= 0)
        {
            cout << "right right imbalance" << endl;
            leftRotate(localRoot);
        }
        else
        {
            cout << "right left imbalance" << endl;
            rightLeftRotate(localRoot);
        }
    }
}

void printTree(Node *rootNode)
{
    queue<NodeInterface *> readQ; // used to read in the levels of the tree, contains Node*
    stringstream nodeReader_ss;   // used to store the values of the nodes and the level-order sequence
    int depth = 0;                // the depth of a node on the tree

    readQ.push(rootNode); // push the root node of the tree into the queue

    while (!readQ.empty())
    {                         // as long as the queue has a remaining node:
        int i = readQ.size(); // store the number of nodes on this level of the tree
        nodeReader_ss << depth << ":  ";
        for (; i > 0; i--)
        {                                                // for each node on this level,
            NodeInterface *nextNode = readQ.front();     // store the next node in the queue
            nodeReader_ss << nextNode->getData() << " "; // store the data from the node into the ss
            if (nextNode->getLeftChild() != NULL)
            { // if there is a left child, push the left child into the queue
                readQ.push(nextNode->getLeftChild());
            }
            if (nextNode->getRightChild() != NULL)
            { // if there is a right child, push the left child into the queue
                readQ.push(nextNode->getRightChild());
            }
            readQ.pop(); // pop the node off of the queue, leaving its children in the queue
        }

        nodeReader_ss << "\n"; // push an endl into the ss to distinguish levels
        depth++;
    }

    cout << nodeReader_ss.str();
}

int AVL::differenceInChildHeight(Node *givenPointer)
{
    if (givenPointer == nullptr)
    {
        return 0;
    }
    int rightHeight = safeGetHeight(givenPointer->getRightChild());
    cout << "rightChildHeight is: " << rightHeight << endl;
    int leftHeight = safeGetHeight(givenPointer->getLeftChild());
    cout << "leftChildHeight is: " << leftHeight << endl;

    printTree(rootNode);
    return (rightHeight - leftHeight);
}