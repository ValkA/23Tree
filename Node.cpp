//
// Created by ValkA on 01-Jan-19.
//

#include "Node.h"
#include <iostream>

Node::Node(const Key *key, Node *parent) :
    rightSibling(NULL),
    parent(parent),
    key(NULL),
    size(0){
        if(key!=NULL){
            this->key = key->clone();
        }
}

Node::~Node() {
    delete key;
};