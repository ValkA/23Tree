//
// Created by ValkA on 01-Jan-19.
//

#include "LCRS_BalancedTree.h"
#include "LeafNode.h"
#include <iostream>

#define CHILD 0
#define PARENT_SIBLING 1

LCRS_BalancedTree::LCRS_BalancedTree(const Key *min, const Key *max) {
    LeafNode* minLeaf = new LeafNode(min,NULL,NULL);
    LeafNode* maxLeaf = new LeafNode(max,NULL,NULL);
    minLeaf->size = 0;
    maxLeaf->size = 0;
    root = new InnerNode(max, NULL, minLeaf, maxLeaf);
    minLeaf->parent = root;
    maxLeaf->parent = root;
}

LCRS_BalancedTree::~LCRS_BalancedTree() {
    Node* x = root;
    int from = PARENT_SIBLING;
    while(x!=NULL) {
        if(from == PARENT_SIBLING){
//           print x
//TODO: check no memory leaks
            InnerNode* innerNode = dynamic_cast<InnerNode*>(x);
            if(innerNode!=NULL){
                x = innerNode->leftChild;
            } else {
                Node* toDelete = x;
                if(x->rightSibling!=NULL){
                    x = x->rightSibling;
                } else {
                    from = CHILD;
                    x = x->parent;
                }
                delete toDelete;
            }
        } else {
            if(x->rightSibling!=NULL){
                from = PARENT_SIBLING;
                x = x->rightSibling;
            } else {
                x = x->parent;
            }
        }
    }
}

void LCRS_BalancedTree::Insert(const Key *nkey, const Value *nval) {
    InnerNode* x = searchParentOf(nkey);
    InnerNode* z = insertAndSplit(x, new LeafNode(nkey, x, nval));
    while(x!=root){
        x = dynamic_cast<InnerNode*>(x->parent);
        if(z!=NULL){
            z = insertAndSplit(x,z);
        } else {
            x->updateKey();
        }
    }
    if(z!=NULL){
        InnerNode* w = new InnerNode(x,z,NULL);
        root = w;
    }
}

InnerNode* LCRS_BalancedTree::insertAndSplit(InnerNode *x, Node *z) {
    Node* l = x->leftChild;
    Node* m=(l==NULL?NULL:l->rightSibling);
    Node* r=(m==NULL?NULL:m->rightSibling);
    if(r == NULL){
        if(*z->key < *l->key){
            x->setChildren(z,l,m);
        } else if(*z->key < *m->key){
            x->setChildren(l,z,m);
        } else {
            x->setChildren(l,m,z);
        }
        return NULL;
    }

    if(*z->key < *l->key){
        x->setChildren(z,l,NULL);
        return new InnerNode(m,r,NULL);
    } else if(*z->key < *m->key){
        x->setChildren(l,z,NULL);
        return new InnerNode(m,r,NULL);
    } else if(*z->key < *r->key){
        x->setChildren(l,m,NULL);
        return new InnerNode(z,r,NULL);
    } else{
        x->setChildren(l,m,NULL);
        return new InnerNode(r,z,NULL);
    }
}

InnerNode* LCRS_BalancedTree::searchParentOf(const Key *key) const{
    InnerNode* current = root;
    InnerNode* next = dynamic_cast<InnerNode*>(current->leftChild);
    //children path while
    while(next != NULL){
        //brothers while
        while(*(next->key) < *key){
            next = dynamic_cast<InnerNode*>(next -> rightSibling);
        }
        current = next;
        next = dynamic_cast<InnerNode*>(current->leftChild);
    }
    return current;
}

Value* LCRS_BalancedTree::Search(const Key *key) const {
    InnerNode* p = searchParentOf(key);
    LeafNode* next = dynamic_cast<LeafNode*>(p->leftChild);
    while(*(next->key) < *key){
        next = dynamic_cast<LeafNode*>(next -> rightSibling);
    }
    if(*key < *(next->key)){
        return NULL;
    }
    return next->value;
}

void LCRS_BalancedTree::print() const {
    Node* x = root;
    int from = PARENT_SIBLING;
    while(x!=NULL) {
        if(from == PARENT_SIBLING){
            InnerNode* innerNode = dynamic_cast<InnerNode*>(x);
            if(innerNode!=NULL){
                x = innerNode->leftChild;
            } else {
                LeafNode* node = dynamic_cast<LeafNode*>(x);
                if(node!=NULL && node->value!=NULL) {
                    node->value->print();
                }

                if(x->rightSibling!=NULL){
                    x = x->rightSibling;
                } else {
                    from = CHILD;
                    x = x->parent;
                }
            }
        } else {
            if(x->rightSibling!=NULL){
                from = PARENT_SIBLING;
                x = x->rightSibling;
            } else {
                x = x->parent;
            }
        }
    }
}