#include <iostream>

using namespace std;

class A{
    public:
    virtual void print(){
        cout << "A" << endl;
    }
};

class B : public A{
public:
    void print() override{
        cout << "B" << endl;
    }
};

int main(int argc, char const *argv[])
{
    A *b = new B();
    b->print();
    A &a(*b);
    a.print();
    return 0;
}
