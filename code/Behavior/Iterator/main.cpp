#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


//抽象迭代器
class Iterator
{
public:
    virtual string first() = 0;
    virtual string next() = 0;
    virtual bool hasNext() = 0;
};
//具体迭代器
class ConcreteIterator:public Iterator
{
private:
    list<string> *obj_list;
    int index=-1;
public:
    ConcreteIterator(list<string> *list)
    {
        this->obj_list=list;
    }
    bool hasNext()
    {
        int size = obj_list->size()-1;
        if(index < size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string first()
    {
        index=0;
        string obj=obj_list->front();
        return obj;
    }
    string next()
    {
        string obj;
        if(this->hasNext())
        {
            index++;
            list<string>::iterator itor = obj_list->begin();
            for(int i=0; i<index; ++i)
                ++itor;
            obj=*itor;
        }
        return obj;
    }
};
//抽象聚合
class Aggregate
{
public:
    virtual void add(string obj) = 0;
    virtual void remove(string obj) = 0;
    virtual Iterator *getIterator() = 0;
};
//具体聚合
class ConcreteAggregate:public Aggregate
{
private:
    list<string> obj_list;

public:
    void add(string obj)
    {
        obj_list.push_back(obj);
    }
    void remove(string obj)
    {
        obj_list.remove(obj);
    }
    Iterator* getIterator()
    {
        return(new ConcreteIterator(&obj_list));
    }
};

int main()
{

    Aggregate *ag=new ConcreteAggregate();
    ag->add("中山大学");
    ag->add("华南理工");
    ag->add("韶关学院");
    printf("聚合的内容有：");
    Iterator *it=ag->getIterator();
    ag->add("首都师范");
    while(it->hasNext())
    {
        string ob=it->next();
        cout << ob << "  ";
    }
    string ob=it->first();
    cout << endl << "First：" << ob << endl;

    return 0;
}
