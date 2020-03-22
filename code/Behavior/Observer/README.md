# 观察者模式

![image.png](https://upload-images.jianshu.io/upload_images/21440240-3ffdf3f6782e7b60.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


观察者模式：定义了一种一对多的依赖关系，让多个观察者对象同时监听某一主题对象，在主题对象的状态发生变化时,会通知所有的观察者。

>观察者模式角色如下：

>抽象主题（Subject）角色：抽象主题角色提供维护一个观察者对象集合的操作方法，对集合的增加、删除等。
具体主题（ConcreteSubject）角色：将有关状态存入具体的观察者对象；在具体主题的内部状态改变时，给所有登记过的观察者发通知。具体主题角色负责实现抽象主题中的方法。
抽象观察者（Observer）角色：为具体观察者提供一个更新接口。
具体观察者（ConcreteObserver）角色：存储与主题相关的自洽状态，实现抽象观察者提供的更新接口。



# 二、观察者模式的应用
1. 何时使用
* 一个对象状态改变，所有的依赖对象都将得到通

2. 方法
* 使用面向对象技术

3. 优点
* 观察者与被观察者抽象耦合，容易扩展；
* 建立了一套触发机制。

4. 缺点
* 循环依赖会导致系统崩溃；
* 观察者太多会浪费时间;
* 没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的

5. 使用场景
* 关联行为场景
* 事件多级触发场景
* 跨系统的消息变换场景，如消息队列的处理机制

6. 应用实例
* 手机丢了，委托别人给其他人发消息通知
* 通知老师/老板来了
* 拍卖，拍卖师观察最高标价，然后通知给其它竞价者竞价
* 在一个目录下建立一个文件，会同时通知目录管理器增加目录，并通知磁盘减少空间，文件是被观察者，目录管理器和磁盘管理器是观察者
* 猫叫了一声，吓着了老鼠，也惊到了主人，猫是被观察者，老鼠和人是观察者

7. 注意事项
* 避免循环引用
* 如果顺序执行，某一观察者错误会导致系统卡壳，一般采用异步方式


# 三、观察者模式实现
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
以上是初级的观察者模式，这里用C++11搭配一点模板技巧，实现一个更加通用的观察者模式。

也可以叫发布-订阅模式。
```

#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//Subject 事件或消息的主体。模板参数为观察者类型
template<typename ObserverType>
class Subject {
public:
    //订阅
    void subscibe(ObserverType *obs)
    {
        auto itor = std::find(m_observerList.begin(), m_observerList.end(), obs);
        if (m_observerList.end() == itor) {
            m_observerList.push_back(obs);
        }
    }
    //取消订阅
    void unSubscibe(ObserverType *obs)
    {
        m_observerList.erase(std::remove(m_observerList.begin(), m_observerList.end(), obs));
    }
    //发布。这里的模板参数为函数类型。
    template <typename FuncType>
    void publish(FuncType func)
    {
        for (auto obs: m_observerList)
        {
            //调用回调函数，将obs作为第一个参数传递
            func(obs);
        }
    }
private:
    std::vector<ObserverType *> m_observerList;
};

//CatObserver 接口 猫的观察者
class CatObserver {
public:
    //猫叫事件
    virtual void onMiaow() = 0;
public:
    virtual ~CatObserver() {}
};

//Tom 继承于Subject模板类，模板参数为CatObserver。这样Tom就拥有了订阅、发布的功能。
class Tom : public Subject<CatObserver>
{
public:
    void miaoW()
    {
        cout << "喵!" << endl;
        //发布"猫叫"。
        //这里取CatObserver类的成员函数指针onMiaow。而成员函数指针调用时，要传递一个对象的this指针才行的。
        //所以用std::bind 和 std::placeholders::_1将第一个参数 绑定为 函数被调用时的第一个参数，也就是前面Subject::publish中的obs
        publish(std::bind(&CatObserver::onMiaow, std::placeholders::_1));
    }
};
//Jerry 继承于 CatObserver
class Jerry: public CatObserver
{
public:
    //重写“猫叫事件”
    void onMiaow() override
    {
        //发生 “猫叫”时 调用 逃跑
        RunAway();
    }
    void RunAway()
    {
        cout << "那只猫又来了，快溜！" << endl;
    }
};
int main(int argc, char *argv[])
{
    Tom tom;
    Jerry jerry;

    //拿jerry去订阅Tom的 猫叫事件
    tom.subscibe(&jerry);

    tom.miaoW();
    return 0;
}

```
运行结果：
```
喵!
那只猫又来了，快溜！

```
