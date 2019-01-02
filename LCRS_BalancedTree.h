//
// Created by ValkA on 01-Jan-19.
//

#ifndef BALANCEDTREE_LCRS_BALANCEDTREE_H
#define BALANCEDTREE_LCRS_BALANCEDTREE_H

#include "Key.h"
#include "Value.h"
#include "InnerNode.h"

class LCRS_BalancedTree{
public:
    LCRS_BalancedTree(const Key* min, const Key* max);
    ~LCRS_BalancedTree();
    void Insert(const Key* nkey, const Value* nval);
    void Delete(const Key* dkey);
    Value* Search(const Key* key) const;
    //TODO: rank tree
//    unsigned Rank(const Key* key) const;
//    const Key* Select(unsigned index) const;
//    void Print_Values(const Key* key1, const Key* key2) const;
    void print() const;
private:
    InnerNode* searchParentOf(const Key* key) const;
    InnerNode* insertAndSplit(InnerNode* x, Node* z);
    InnerNode* root;
};

#endif //BALANCEDTREE_LCRS_BALANCEDTREE_H
