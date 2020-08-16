#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;


//抽象构件
class Component
{
public:
    virtual void add(Component *c) = 0;
    virtual void remove(Component *c) = 0;
    virtual Component *getChild(int i) = 0;
    virtual void operation() = 0;
};
//树叶构件
class Leaf:public Component
{
private:
    string name;
public:
    Leaf(string name)
    {
        this->name=name;
    }
    void add(Component *c){ }
    void remove(Component *c){ }
    Component *getChild(int i)
    {
        return NULL;
    }
    void operation()
    {
        cout << "树叶"<< name << "：被访问！" << endl;
    }
};
//树枝构件
class Composite:public Component
{
private:
    vector<Component*> children;
public:void add(Component *c)
    {
        children.push_back(c);
    }
    void remove(Component *c)
    {
        //children.erase(c);
    }
    Component *getChild(int i)
    {
        return children.at(i);
    }
    void operation()
    {
        //增强型for循环
        for (auto obj:children)
        {
            obj->operation();
        }
    }
};


int main()
{
    Component *c0=new Composite();
    Component *c1=new Composite();
    Component *leaf1=new Leaf("1");
    Component *leaf2=new Leaf("2");
    Component *leaf3=new Leaf("3");
    c0->add(leaf1);
    //
    c0->add(c1);

    c1->add(leaf2);
    c1->add(leaf3);

    c0->operation();

    return 0;
}
