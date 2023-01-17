#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
    private:
        Node * right = nullptr;
        Node * left = nullptr;
        Node * parent = nullptr;
        string data = "";
        int count = 1;
        friend class BSTree;
    public:
        Node(const string &);
};

#endif