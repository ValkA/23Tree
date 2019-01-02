//
// Created by ValkA on 01-Jan-19.
//

#include "InnerNode.h"

InnerNode::InnerNode(const Key *key, Node *parent, Node *n1, Node *n2, Node *n3) : Node(key, parent), leftChild(n1) {
    n1->parent = this;
    n2->parent = this;
    if(n3 != NULL) n3->parent = this;
    n1->rightSibling = n2;
    n2->rightSibling = n3;
    size = n1->size + n2->size + (n3 != NULL ? n3->size : 0);
}

unsigned int InnerNode::degree() {
    Node* child = this->leftChild;
    unsigned int count = 0;
    while(child!=NULL){
        count++;
        child = child->rightSibling;
    }
    return count;
}

void InnerNode::setChildren(Node *l, Node *m, Node *r) {
    this->leftChild = l;
    if(l!=NULL) {
        l->parent = this;
        l->rightSibling = m;
    }
    if(m!=NULL){
        m->parent = this;
        m->rightSibling = r;
    }
    if(r!=NULL){
        r->parent = this;
        r->rightSibling = NULL;
    }
    updateKey();
}

InnerNode::InnerNode(Node *l, Node *m, Node *r) : Node(NULL,NULL){
    setChildren(l,m,r);
}

void InnerNode::updateKey() {
    Node* c = this->leftChild;
    Key* k;
    while(c){
        k = c->key;
        c = c->rightSibling;
    }

    if(k != this->key){
        delete this->key;
        this->key = k->clone();
    }
}
