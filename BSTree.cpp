/* Felix Diaz - BST implementation 
	Option 1: Insert string into the tree
	Option 2: Remove string from the tree
	Option 3: Print tree in preorder, inorder, and postorder notation
				*duplicate strings are represented as a numerical value
	Option 4: Searches for instance of string within tree
	Option 5: Searches for the smallest string within the tree
	Option 6: Searches for the largest string within the tree
	Option 7: Returns the height of a given node within the tree
*/

#include <iostream>

#include "BSTree.h"

using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

void BSTree::insert(const string &nData) {
    Node * insnode = new Node(nData);

    //if the tree is empty, make this the first node in the tree
    if(root == nullptr) {
        root = insnode;
        insnode->parent = nullptr;
    } else { 
        Node * current = root;

        while(current) {
            if(nData < current->data) {
                if(current->left == nullptr) {
                    current->left = insnode;
                    insnode->parent = current;
                    current = nullptr;
                } else {
                    current = current->left;
                }
            } else if(nData > current->data) {
                if(current->right == nullptr) {
                    current->right = insnode;
                    insnode->parent = current;
                    current = nullptr;
                } else {
                    current = current->right;
                }
            } else {
                current->count++;
                current = nullptr;
            }
        }        
    }
}

bool BSTree::search(const string &toFind) const {
    //searches for a string in the BST, if found, return true
    bool nExists = false;

    //for traversal
    //Node * parent = nullptr;
    Node * current = root;

    //if the tree is empty, return false doe
    if(!current) {
        return nExists;
    } else {
        //otherwise, traverse through the tree as you would until you find it
        //if node is found, update bool to refelct that, break loop, return bool
        while(current) {
            if(toFind < current->data) {
                //parent = current;
                current = current->left;
            } else if(toFind > current->data) {
                //parent = current;
                current = current->right;
            } else {
                nExists = true;
                break;
            }
        }
        //false or not return the result here
        return nExists;
    }
}

string BSTree::largest() const {
    string currLargest = "";

    if(!root) {
        return currLargest;
    }

    Node * current = root;
    Node * parent = nullptr;

    while(current) {
        parent = current;
        current = current->right;
    }

    currLargest = parent->data;
    return currLargest;
}

string BSTree::smallest() const {
    string currLargest = "";

    if(!root) {
        return currLargest;
    }

    Node * current = root;
    Node * parent = nullptr;

    while(current) {
        parent = current;
        current = current->left;
    }

    currLargest = parent->data;
    return currLargest;    
}

int BSTree::height(const string &nData) const {
    bool strExists = false;
    Node * current = root;

    //actually find the node we need to compute the height of, simple traversal
    //bool to indicate whether or not the node exists in the tree
    while(current) {
        if(nData < current->data) {
            current = current->left;
        } else if(nData > current->data) {
            current = current->right;
        } else {
            strExists = true;
            break;
        }
    }

    //if the node does exists go ahead and recursively compute the height
    //if the node does not exist, return an error message indicating that
    if(strExists) {
        return height(current);
    } else {
        return -1;
    }
}

void BSTree::remove(const string &s) {
    bool found = search(s);

    if(found) {
        //cout << "found: " << s << endl;
        //Node * par = nullptr;
        Node * current = root;

        while(current->data != s) {
            if(s < current->data) {
                //par = current;
                current = current->left;
            } else {
                //par = current;
                current = current->right;
            }
        }

        if(current->count > 1) {
            current->count--;
            return;
        } else {
            //out << "deleting: " << current->data << endl;
            deleteN(current);
        }
    }
}

void BSTree::deleteN(Node *n) {
    if(n->right == nullptr && n->left == nullptr) {
        //if its a leaf node
        if(n->parent == nullptr) {
            //if its the root node, disconnect it
            root = nullptr;
            delete n;
        } else if(n->parent->left == n) {
            //if its a left child
            n->parent->left = nullptr;
            delete n;
        } else {
            //if its a right child
            n->parent->right = nullptr;
            delete n;
        }
    } else if(n->left != nullptr) {
        Node * suc = n->left;
        while(suc->right) {
            suc = suc->right;
        }        

        string sucDat = suc->data;
        int suCount = suc->count;

        deleteN(suc); 
        
        n->data = sucDat;
        n->count = suCount;
    } else {
        Node * suc = n->right;
        while(suc->left) {
            suc = suc->left;
        }        

        string sucDat = suc->data;
        int suCount = suc->count;

        deleteN(suc); 
        
        n->data = sucDat;
        n->count = suCount;
    }
}

//preorder notation
void BSTree::preOrder() {
    preOrder(root);
}

void BSTree::preOrder(Node *n) {
    if(n == nullptr) {
        return;
    }

    cout << n->data << "(";
    cout << n->count << "), ";
    preOrder(n->left);
    preOrder(n->right);
}

//inorder notation
void BSTree::inOrder() {
    inOrder(root);
}

void BSTree::inOrder(Node *n) {
    if(n == nullptr) {
        return;
    }
    inOrder(n->left);
    cout << n->data << "(";
    cout << n->count << "), ";
    inOrder(n->right);
}

//post order notation
void BSTree::postOrder() {
    postOrder(root);
}

void BSTree::postOrder(Node *n) {
    if(n == nullptr) {
        return;
    }
    postOrder(n->left);
    postOrder(n->right);
    cout << n->data << "(";
    cout << n->count << "), ";     
}

//helper functions
//helper function to revursively compute the height of a particular node in the tree
int BSTree::height(Node * n) const {
    if(n == nullptr) {
        return -1;
    }

    int leftHeight = height(n->left);
    int rightHeight = height(n->right);

    return max(leftHeight, rightHeight) + 1;
}