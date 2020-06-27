#include<iostream>
using namespace std;
class SubSystemA {
public:
    void dosomethingA() {
        cout << "子系统方法A" << endl;
    }

};
class SubSystemB {
public:
    void dosomethingB() {
        cout << "子系统方法B" << endl;
    }

};
class SubSystemC {
public:
    void dosomethingC() {
        cout << "子系统方法C" << endl;
    }

};
class SubSystemD {
public:
    void dosomethingD() {
        cout << "子系统方法D" << endl;
    }

};
class Facade {

    //被委托的对象
    SubSystemA *a;
    SubSystemB *b;
    SubSystemC *c;
    SubSystemD *d;

public :
    Facade() {
        a = new SubSystemA();
        b = new SubSystemB();
        c = new SubSystemC();
        d = new SubSystemD();
    }

    //提供给外部访问的方法
    void methodA() {
        this->a->dosomethingA();
    }

    void methodB() {
        this->b->dosomethingB();
    }

    void methodC() {
        this->c->dosomethingC();
    }

    void methodD() {
        this->d->dosomethingD();
    }

};

int main()
{
    Facade *facade = new Facade();
    facade->methodA();
    facade->methodD();
}
