//
// Created by ValkA on 02-Jan-19.
//
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <cstdlib>
#include <assert.h>     /* assert */

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

void TEST_INSERT_SEARCH(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);
    assert(tree.getSize() == 0);

    MyKey k(7);
    assert(tree.Search(&k)==NULL);
    MyValue v("seven");
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 1);

    k.set_key(10);
    v.set_value("ten");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 2);

    k.set_key(17);
    v.set_value("SeVeNtEeN!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 3);

    cout << "TEST_INSERT_SEARCH passed" <<endl;
}

void TEST_DELETE(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);
    assert(tree.getSize() == 0);

    MyKey k(7);
    assert(tree.Search(&k)==NULL);
    MyValue v("seven");
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 1);

    k.set_key(10);
    v.set_value("ten");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 2);

    k.set_key(17);
    v.set_value("SeVeNtEeN!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    assert(tree.getSize() == 3);

    tree.Delete(&k);
    assert(tree.Search(&k)==NULL);
    assert(tree.getSize() == 2);

    k.set_key(7);
    tree.Delete(&k);
    assert(tree.Search(&k)==NULL);
    assert(tree.getSize() == 1);

    k.set_key(10);
    tree.Delete(&k);
    assert(tree.Search(&k)==NULL);
    assert(tree.getSize() == 0);

    cout << "TEST_DELETE passed" <<endl;
}



void TEST_RANK(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);

    MyKey k(0);
    assert(tree.Search(&k)==NULL);
    MyValue v("0!");
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(10);
    v.set_value("10!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(50);
    v.set_value("50!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(40);
    v.set_value("40!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(30);
    v.set_value("30!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(60);
    v.set_value("60!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(20);
    v.set_value("20!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(-1);
    assert(tree.Rank(&k)==0);
    k.set_key(0);
    assert(tree.Rank(&k)==1);
    k.set_key(10);
    assert(tree.Rank(&k)==2);
    k.set_key(20);
    assert(tree.Rank(&k)==3);
    k.set_key(30);
    assert(tree.Rank(&k)==4);
    k.set_key(40);
    assert(tree.Rank(&k)==5);
    k.set_key(50);
    assert(tree.Rank(&k)==6);
    k.set_key(60);
    assert(tree.Rank(&k)==7);
    k.set_key(99);
    assert(tree.Rank(&k)==0);

    //TODO: what is tree.Rank(infinity) and tree.Rank(-infinity)
    //TODO: what c++ we should use? 11? 14?


    cout << "TEST_RANK passed" <<endl;
}

void TEST_SELECT(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);

    MyKey k(0);
    assert(tree.Search(&k)==NULL);
    MyValue v("0!");
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(10);
    v.set_value("10!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(50);
    v.set_value("50!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(40);
    v.set_value("40!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(30);
    v.set_value("30!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(60);
    v.set_value("60!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(20);
    v.set_value("20!");
    assert(tree.Search(&k)==NULL);
    tree.Insert(&k, &v);
    assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());

    k.set_key(-1);
    assert(tree.Rank(&k)==0);
    k.set_key(0);
    assert(tree.Rank(&k)==1);
    k.set_key(10);
    assert(tree.Rank(&k)==2);
    k.set_key(20);
    assert(tree.Rank(&k)==3);
    k.set_key(30);
    assert(tree.Rank(&k)==4);
    k.set_key(40);
    assert(tree.Rank(&k)==5);
    k.set_key(50);
    assert(tree.Rank(&k)==6);
    k.set_key(60);
    assert(tree.Rank(&k)==7);
    k.set_key(99);
    assert(tree.Rank(&k)==0);

    assert(((MyKey*)tree.Select(0))->get_key() == -1);
    assert(((MyKey*)tree.Select(1))->get_key() == 0);
    assert(((MyKey*)tree.Select(2))->get_key() == 10);
    assert(((MyKey*)tree.Select(3))->get_key() == 20);
    assert(((MyKey*)tree.Select(4))->get_key() == 30);
    assert(((MyKey*)tree.Select(5))->get_key() == 40);
    assert(((MyKey*)tree.Select(6))->get_key() == 50);
    assert(((MyKey*)tree.Select(7))->get_key() == 60);
    assert((MyKey*)tree.Select(8) == NULL);

    //TODO: what is tree.Rank(infinity) and tree.Rank(-infinity)
    //TODO: what c++ we should use? 11? 14?


    cout << "TEST_SELECT passed" <<endl;
}

void TEST_PRINT_RANGE(){
    MyKey a(-1), b(101);
    LCRS_BalancedTree tree(&a,&b);

    MyKey k(0);
    MyValue v("0!");

    for(int i=20; i<=70; i+=1){
        k.set_key(i);
        char val[] = {'v','=',' ',' ',' ',0};
        itoa (i, val+2, 10);
        v.set_value(val);
        assert(tree.Search(&k)==NULL);
        tree.Insert(&k, &v);
        assert(((MyValue*)tree.Search(&k))->get_value()==v.get_value());
    }


    MyKey k1(30);
    MyKey k2(60);
    tree.Print_Values(&k1, &k2);

    cout << "TEST_SELECT passed" <<endl;
}

int main(){
    TEST_INSERT_SEARCH();
    TEST_DELETE();
    TEST_RANK();
    TEST_SELECT();
    TEST_PRINT_RANGE();
    return 0;
}
