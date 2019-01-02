//
// Created by ValkA on 01-Jan-19.
//

#ifndef BALANCEDTREE_NODE_H
#define BALANCEDTREE_NODE_H

#include "Key.h"
#include <cstddef>

class Node {
public:
    Node(const Key* key, Node* parent);
    virtual unsigned int degree() = 0;
    virtual ~Node();
    Node* rightSibling;
    Node* parent;
    Key* key;
    unsigned int size;
};


#endif //BALANCEDTREE_NODE_H
