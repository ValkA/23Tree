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
    //children of x
    Node* l = x->leftChild;
    Node* m=(l==NULL?NULL:l->rightSibling);
    Node* r=(m==NULL?NULL:m->rightSibling);

    //2 children
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

    //3 children, need to split
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

LeafNode* LCRS_BalancedTree::_search(const Key *key) const {
    InnerNode* p = searchParentOf(key);
    LeafNode* next = dynamic_cast<LeafNode*>(p->leftChild);
    while(*(next->key) < *key){
        next = dynamic_cast<LeafNode*>(next -> rightSibling);
    }
    if(*key < *(next->key)){
        return NULL;
    }
    return next;
}

Value* LCRS_BalancedTree::Search(const Key *key) const {
    LeafNode* node = _search(key);
    if(node == NULL){
        return NULL;
    }
    return node->value;
}

void _print(Node* root, int d){
    if (dynamic_cast<LeafNode*>(root)!=NULL){
        LeafNode* leafNode = dynamic_cast<LeafNode*>(root);
        for(int i=0; i<d*5; ++i) std::cout<<" ";
        if(leafNode->value) leafNode->value->print();
//        else leafNode->key->print();
        std::cout << std::endl;
    } else {
        InnerNode* innerNode = dynamic_cast<InnerNode*>(root);
        Node* child = innerNode->leftChild;
        while(child!=NULL){
            _print(child, d+1);
            for(int i=0; i<d*5; ++i) std::cout<<" ";
//            if(child->rightSibling!= NULL || child == innerNode->leftChild) innerNode->key->print();
            std::cout << std::endl;
            child = child->rightSibling;
        }
    }
}

void LCRS_BalancedTree::print() const {
    _print(root, 0);
}

void LCRS_BalancedTree::Delete(const Key *dkey) {
    LeafNode* z = _search(dkey);
    if(z == NULL){
        return;
    }
    InnerNode* y = dynamic_cast<InnerNode*>(z->parent);
    //delete z:
    if (z == y->leftChild){
        y->leftChild = z->rightSibling;
    } else if (z == y->leftChild->rightSibling) {
        y->leftChild->rightSibling = y->leftChild->rightSibling->rightSibling;
    } else if (z == y->leftChild->rightSibling->rightSibling){
        y->leftChild->rightSibling->rightSibling = NULL;
    }
    delete z;
    y->size--;


    while(y != root && y->degree()<2){
        y = borrowOrMerge(y);
        y->size--;
    }

    if(y == root){
        if(root->degree()<2){
            root = dynamic_cast<InnerNode*>(y->leftChild);
            root->parent = NULL;
            delete y;
        }
    } else {
        while(y != root){
            y->updateKey();
            y=dynamic_cast<InnerNode*>(y->parent);
        }
        y->updateKey();//another bug, was size-- and key was not updated
    }



}

InnerNode *LCRS_BalancedTree::borrowOrMerge(InnerNode *y) {
    InnerNode* z = dynamic_cast<InnerNode*>(y->parent);
    InnerNode* zl = dynamic_cast<InnerNode*>(z->leftChild);
    InnerNode* zm = dynamic_cast<InnerNode*>(zl->rightSibling);
    InnerNode* zr = dynamic_cast<InnerNode*>(zm->rightSibling);
    if(y == zl){
        InnerNode* x = zm;
        Node* xl = x->leftChild;
        Node* xm = xl->rightSibling;
        Node* xr = xm->rightSibling;
        if(xr != NULL) {
            y->setChildren(y->leftChild, xl, NULL);
            x->setChildren(xm, xr, NULL);
        } else {
            x->setChildren(y->leftChild, xl, xm);
            delete y;
            z->setChildren(zm, zr, NULL);
        }
    } else if(y == zm){
        InnerNode* x = zl;
        Node* xl = x->leftChild;
        Node* xm = xl->rightSibling;
        Node* xr = xm->rightSibling;
        if(xr != NULL){
            x->setChildren(xl,xm,NULL);
            y->setChildren(xr, y->leftChild, NULL);
        } else {
            x->setChildren(xl,xm,y->leftChild);// here was (xm,xl,y->leftChild) by mistake
            delete y;
            z->setChildren(zl,zr, NULL);
        }
    } else if(y == zr) {
        InnerNode *x = zm;
        Node *xl = x->leftChild;
        Node *xm = xl->rightSibling;
        Node *xr = xm->rightSibling;
        if (xr != NULL) {
            x->setChildren(xl, xm, NULL);
            y->setChildren(xr, y->leftChild, NULL);
        } else {
            x->setChildren(xl, xm, y->leftChild);
            delete y;
            z->setChildren(zl, zm, NULL);
        }
    }
    return z;
}

unsigned int LCRS_BalancedTree::getSize() const {
    return root->size;
}

unsigned LCRS_BalancedTree::Rank(const Key *key) const {
    Node* c = _search(key);
    if(c == NULL){
        return 0;
    }
    unsigned rank = c->size;
    for(InnerNode* p = dynamic_cast<InnerNode*>(c->parent); p!=NULL; c=p, p=dynamic_cast<InnerNode*>(p->parent)){
        for(Node* s = p->leftChild; s!=c; s = s->rightSibling){
            rank += s->size;
        }
    }
    return rank;
}

const Key *LCRS_BalancedTree::Select(unsigned index) const {
    InnerNode* current = root;
    Node* next = current->leftChild;
    unsigned sum = 0;

    //children path while
    while(next != NULL){
        //brothers while
        while(sum + next->size < index){
            sum += next->size;
            next = next -> rightSibling;
            if(next == NULL) {
                return NULL;
            }
        }
        if(sum + next->size == index && dynamic_cast<LeafNode*>(next) != NULL){
            return next->key;//TODO: should we return clone of next?
        }
        current = dynamic_cast<InnerNode*>(next);
        next = current->leftChild;
    }
    return NULL;
}

void LCRS_BalancedTree::Print_Values(const Key *key1, const Key *key2) const {
    InnerNode* p = searchParentOf(key1);
    Node* x = p->leftChild;
    while(*(x->key) < *key1){
        x = x->rightSibling;
    }
    int from = PARENT_SIBLING;
    while(x!=NULL) {
        if(from == PARENT_SIBLING){
            InnerNode* innerNode = dynamic_cast<InnerNode*>(x);
            if(innerNode!=NULL){
                x = innerNode->leftChild;
            } else {
                LeafNode* node = dynamic_cast<LeafNode*>(x);
                if(node!=NULL && node->value!=NULL) {
                    if(*key2 < *(node->key)){
                        return;
                    }
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
