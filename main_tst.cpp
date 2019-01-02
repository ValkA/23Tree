//
// Created by ValkA on 02-Jan-19.
//
#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>
#include "LCRS_BalancedTree.h"
using namespace std;

class MyKey :public Key
{
public:
    MyKey(int k) : key(k) {}
    MyKey(MyKey const &mk) :key(mk.key) {}
    ~MyKey() {
//        std::cout << this << std::endl;
//        cout<<key<<endl;
    }
    MyKey* clone() const
    {
        return new MyKey(*this);
    }
    int get_key() { return key; }
    void set_key(int k) { key = k; }
    bool operator<(const Key &rhs) const { return key < ((MyKey&)rhs).key; }
    void print() const { cout << key; }
private:
    int key;
};


class MyValue : public Value
{
public:
    MyValue(string val) : value(val) {}
    ~MyValue() {}
    MyValue(MyValue const &v) { value = v.value; }
    MyValue* clone() const
    {
        return new MyValue(*this);
    }
    string get_value() { return value; }
    void set_value(string val) { value = val; }
    void print() const {
        cout << value<<",";
    }
private:
    string value;
};

int main(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);

    MyKey k(7);
    MyValue v("seven");
    tree.Insert(&k, &v);
    k.set_key(10);
    v.set_value("ten");
    tree.Insert(&k, &v);
    k.set_key(9);
    v.set_value("nine");
    tree.Insert(&k, &v);
    k.set_key(8);
    v.set_value("eight");
    tree.Insert(&k, &v);

    tree.print();
    return 0;
}
