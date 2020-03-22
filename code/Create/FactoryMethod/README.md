# 工厂模式

工厂模式有三种：

（1）简单工厂模式；

（2）工厂方法模式；

（3）抽象工厂模式；

### 1.简单工厂模式
该模式对对象创建管理方式最为简单，因为其仅仅简单的对不同类对象的创建进行了一层薄薄的封装。该模式通过向工厂传递类型来指定要创建的对象，其UML类图如下：
![](https://img2018.cnblogs.com/blog/1419489/201906/1419489-20190628144601084-563759643.png)

下面我们使用手机生产来讲解该模式：
```

#include <iostream>
using namespace std;
//Phone类：手机标准规范类(AbstractProduct)
class phone{
public:

    virtual void make()=0;
};

//  MiPhone类：制造小米手机（Product1）
class MiPhone:public phone
{
public:
    MiPhone()
    {
        this->make();
    }

    void make()
    {
        cout << "make a miphone!" << endl;
    }
};

//IPhone类：制造苹果手机（Product2）
class IPhone:public phone{
public:
    IPhone()
    {
        this->make();
    }
    void make()
    {
        cout << "make a Applephone!" << endl;
    }
};

//PhoneFactory类：手机代工厂（Factory）
class PhoneFactory
{
public:
    phone *makePhone(string phoneType){
        if (phoneType == "mi")
        {
            return new MiPhone();
        }
        else if (phoneType == "apple")
        {
            return new ApplePhone();
        }
    }
};

int main(int argc, char *argv[])
{
    PhoneFactory factory;

    phone *mi = factory.makePhone("mi");
    phone *apple=factory.makePhone("apple");

    return 0;
}

```
运行结果：
```
make a miphone!
make a Applephone!

```
`这么做有一个缺点`：当Factory要生产一个新的产品时，就要修改factory类，然而这样就违背了开放封闭原则，即软件实体（类、函数、模块）不可修改，只能扩展；所以为了通过扩展来实现可以生产新的产品，引入了工厂方法模式；
### 2.工厂方法模式
和简单工厂模式中工厂负责生产所有产品相比，工厂方法模式将生成具体产品的任务分发给具体的产品工厂，其UML类图如下：

![](https://img2018.cnblogs.com/blog/1419489/201906/1419489-20190628154133368-906051111.png)

也就是定义一个抽象工厂，其定义了产品的生产接口，但不负责具体的产品，将生产任务交给不同的派生类工厂。这样不用通过指定类型来创建对象了。

接下来继续使用生产手机的例子来讲解该模式。

其中和产品相关的Phone类、MiPhone类和IPhone类的定义不变。
把工厂抽象出来：

```
//AbstractFactory类：生产不同产品的工厂的抽象类
class AbstractFactory
{
public:
    virtual phone *makePhone()=0;
};
//XiaoMiFactory类：生产小米手机的工厂（ConcreteFactory1）
class XiaoMIFactory:public AbstractFactory
{
public:
    phone *makePhone(){
            return new MiPhone();
    }
};
//AppleFactory类：生产苹果手机的工厂（ConcreteFactory2）
class AppleFactory:public AbstractFactory
{
public:
    phone *makePhone(){
        return new IPhone();
    }
};

int main(int argc, char *argv[])
{
    XiaoMIFactory xiaomi;
    AppleFactory apple;


    phone *mi = xiaomi.makePhone();
    phone *app=apple.makePhone();

    return 0;
}
```
### 3. 抽象工厂模式(Abstract Factory)
上面两种模式不管工厂怎么拆分抽象，都只是针对一类产品Phone（AbstractProduct），如果要生成另一种产品PC，应该怎么表示呢？

最简单的方式是把2中介绍的工厂方法模式完全复制一份，不过这次生产的是PC。但同时也就意味着我们要完全复制和修改Phone生产管理的所有代码，显然这是一个笨办法，并不利于扩展和维护。

抽象工厂模式通过在AbstarctFactory中增加创建产品的接口，并在具体子工厂中实现新加产品的创建，当然前提是子工厂支持生产该产品。否则继承的这个接口可以什么也不干。

其UML类图如下：
![](https://img2018.cnblogs.com/blog/1419489/201906/1419489-20190628170705865-1781414242.png)
从上面类图结构中可以清楚的看到如何在工厂方法模式中通过增加新产品接口来实现产品的增加的。

接下来我们继续通过小米和苹果产品生产的例子来解释该模式。

为了弄清楚上面的结构，我们使用具体的产品和工厂来表示上面的UML类图，能更加清晰的看出模式是如何演变的：
![](https://img2018.cnblogs.com/blog/1419489/201906/1419489-20190628164001258-637961514.png)
```
//PC类：定义PC产品的接口(AbstractPC)
class PC{
public:
    virtual void make()=0;
};
//MiPC类：定义小米电脑产品(MIPC)
class MiPC:public PC
{
public:
    MiPC(){
        this->make();
    }
    void make()
    {
        cout << "make a MiPC!" << endl;
    }
};
//MAC类：定义苹果电脑产品(MAC)
class Mac:public PC{
public:
    Mac(){
        this->make();
    }
    void make()
    {
        cout << "make a Mac!" << endl;
    }
};
//下面需要修改工厂相关的类的定义：

class AbstractFactory
{
public:
    virtual phone *makePhone()=0;
    virtual PC *makePC()=0;
};
//XiaoMiFactory类：增加小米PC的制造（ConcreteFactory1）
class XiaoMIFactory:public AbstractFactory
{
public:
    phone *makePhone(){
            return new MiPhone();
    }
    PC *makePC(){
        return new MiPC();
    }
};
//AppleFactory类：增加苹果PC的制造（ConcreteFactory2）

class AppleFactory:public AbstractFactory
{
public:
    phone *makePhone(){
        return new IPhone();
    }
    PC *makePC(){
        return new Mac();
    }
};
//演示：
int main(int argc, char *argv[])
{
    XiaoMIFactory xiaomi;
    AppleFactory apple;


    phone *mi = xiaomi.makePhone();
    phone *app=apple.makePhone();

    xiaomi.makePC();
    apple.makePC();

    return 0;
}

```
运行结果：
```
make a miphone!
make a Applephone!
make a MiPC!
make a Mac!

```
