//
// Created by ValkA on 01-Jan-19.
//

#include "LeafNode.h"

LeafNode::LeafNode(const Key *key, Node *parent, const Value *value) :
    Node(key, parent),
    value(NULL) {
    if(value!=NULL) this->value = value->clone();
    size = 1;
}

LeafNode::~LeafNode() {
    delete value;
}

unsigned int LeafNode::degree() {
    return 0;
};

