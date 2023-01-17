#ifndef BSTREE_H
#define BSTREE_H

#include "Node.h"

class BSTree {
    private:
        Node * root;
    public:
       BSTree(); 
       void insert(const string &);
       bool search(const string &) const;
       string largest() const;
       string smallest() const;
       int height(const string &) const;
       void remove(const string &);

       void preOrder();
       void inOrder();
       void postOrder(); 
    private:
        int height(Node *) const;
        void preOrder(Node *);
        void inOrder(Node *);
        void postOrder(Node *);
        void deleteN(Node *n);

};

#endif