#include <iostream>
#include <list>
using namespace std;
/******观察者*********/
//抽象观察者
class Observer
{
public:
    virtual void response(string msg) = 0;
};
//具体观察者A
class ObserverA:public Observer
{
public:
    void response(string msg)
    {
        cout << "ObserverA,I get notify:" << msg << endl;
    }
};
class ObserverB:public Observer
{
public:
    void response(string msg)
    {
        cout << "ObserverB,I get notify:" << msg << endl;
    }
};
class ObserverC:public Observer
{
public:
    void response(string msg)
    {
        cout << "ObserverC,I get notify:" << msg << endl;
    }
};
/*******被观察者********/
//抽象被观察者
class subject
{
public:
    virtual void add(Observer *ob)=0;
    virtual void remove(Observer *ob) = 0;
    virtual void notify(string msg)=0;
};
//具体被观察者
class ConcreteSubject:public subject
{
private:
    list<Observer *> observers;
public:
    void add(Observer *ob)
    {
        observers.push_back(ob);
    }
    void remove(Observer *ob)
    {
        observers.remove(ob);
    }
    void notify(string msg)
    {

        for(auto ob=observers.begin();ob!=observers.end();ob++)
        {
            (*ob)->response(msg);
        }
    }
};

int main(int argc, char *argv[])
{
    ObserverA a;
    ObserverB b;
    ObserverC c;

    ConcreteSubject subject;

    subject.add(&a);
    subject.add(&b);
    subject.add(&c);

    subject.remove(&b);

    subject.notify("起立");
    return 0;
}
