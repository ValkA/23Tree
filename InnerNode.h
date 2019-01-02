//
// Created by ValkA on 01-Jan-19.
//

#ifndef BALANCEDTREE_INNERNODE_H
#define BALANCEDTREE_INNERNODE_H

#include "Node.h"

class InnerNode : public Node{
public:
    InnerNode(Node* l, Node* m, Node* r);
    InnerNode(const Key* key, Node* parent, Node* n1, Node* n2, Node* n3=NULL);
    void setChildren(Node* l, Node* m, Node* r);
    void updateKey();
    unsigned int degree();
    Node* leftChild;
};


#endif //BALANCEDTREE_INNERNODE_H
