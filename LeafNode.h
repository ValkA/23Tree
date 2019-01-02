//
// Created by ValkA on 01-Jan-19.
//

#ifndef BALANCEDTREE_LEAFNODE_H
#define BALANCEDTREE_LEAFNODE_H

#include "Node.h"
#include "Value.h"

class LeafNode : public Node {
public:
    LeafNode(const Key* key, Node* parent, const Value* value);
    ~LeafNode();
    unsigned int degree();
    Value* value;
};


#endif //BALANCEDTREE_LEAFNODE_H
