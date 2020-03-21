# 观察者模式

观察者模式：定义了一种一对多的依赖关系，让多个观察者对象同时监听某一主题对象，在主题对象的状态发生变化时,会通知所有的观察者。

>观察者模式角色如下：

>抽象主题（Subject）角色：抽象主题角色提供维护一个观察者对象集合的操作方法，对集合的增加、删除等。
具体主题（ConcreteSubject）角色：将有关状态存入具体的观察者对象；在具体主题的内部状态改变时，给所有登记过的观察者发通知。具体主题角色负责实现抽象主题中的方法。
抽象观察者（Observer）角色：为具体观察者提供一个更新接口。
具体观察者（ConcreteObserver）角色：存储与主题相关的自洽状态，实现抽象观察者提供的更新接口。

```
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

```
运行结果：
```
ObserverA,I get notify:起立
ObserverC,I get notify:起立

```

再具体点的案例
Case：
在教室里老师还没有来，同学都在干着各的事情，小张正在打游戏，小李正在抄作业.....,  现在同学们要求班长当卧底，监视老师，当老师来了通知大家一声。然后打游戏的马上停止，抄作业的也停止。

这里班长相当于是一个通知者， 小张、小李，以及其他同学显然是监听者，他们监听了班长那的消息，一旦老师来了马上采取相关的行动。
```
#include <iostream>
#include <list>
using namespace std;

//首先，把通知者的行为抽象为一个接口：（subject）
class INotifier{
public:
    virtual void registerListener(ITeacherListener *l)=0;
    virtual void removeListener(ITeacherListener *l)=0;
    virtual void notify()=0;

};
//第二，然后班长作为一个具体的通知者：（ConcreteSubject）
class MonitorNotifier:public INotifier{
public:
    void registerListener(ITeacherListener *l){
        listenerList.push_back(l);
    }
    void removeListener(ITeacherListener *l)
    {
        listenerList.remove(l);
    }
    void setValue(int val)
    {
        value = val;
    }
    void notify()
    {
        for (ITeacherListener *l:listenerList)
        {
            l->onTeacherComming(value);
        }
    }
private:
    list<ITeacherListener *> listenerList;
    int value; //=the msg need notify
};

//第三，定义一个监听者的接口，想要监听老师来了这个消息的同学必须要实现这个接口，因为通知者通过这个接口传达消息：
class ITeacherListener{
public:
    virtual void onTeacherComming(int value)=0;
};
class ZhangSan:public ITeacherListener
{
public:
    void onTeacherComming(int value){
        stopCopyWork(value);
    }
    void stopCopyWork(int value)
    {
        cout << "zhang san stopCopyWork " << value << endl;
    }
};
//第四，ZhangSan,LiSi监听了老师来了这个接口：
class Lisi:public ITeacherListener
{
public:
    void onTeacherComming(int value)
    {
        stopPlayGame(value);
    }
    void stopPlayGame(int value)
    {
        cout << "Li si stopPlayGame " << value << endl;
    }
};



int main(int argc, char *argv[])
{
   cout << "--------------------"<<endl;
   MonitorNotifier monitor;
   ZhangSan zs;
   LiSi ls;
   monitor.registerListenner(&zs);
   monitor.registerListenner(&ls);
   monitor.setValue(1);

   cout << "-----------------"<<endl;
   monitor.removeListenner(&ls);
   monitor.setValue(2);


    return 0;
}
```
运行结果：
```
--------------------
zhang san stopCopyWork 1
Li si stopPlayGame 1
-----------------
zhang san stopCopyWork 2


```
