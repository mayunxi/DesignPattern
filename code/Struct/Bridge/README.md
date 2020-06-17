我们都去买过手机，手机按照品牌分可以分为华为、小米、oppo、vivo等品牌，如果这些手机按照内存分又可以分为4G、6G、8G等等。假如我们每一种手机都想要玩一下，至少需要4*3个。这对我们来说这些手机也太多了，竟然有12个，最主要的是手机品牌和内存是放在一起的。现在有这样一种机制，手机牌品商是一个公司，做手机内存的是一个公司，想要做什么手机我们只需要让其两者搭配起来即可。有点类似于全球贸易分工明确的思想，这就是桥接模式，把两个不同维度的东西桥接起来。

一、认识桥接模式

1、概念

将抽象部分与它实现部分分离，使它们都可以独立地变化。

2、例子说明

从上面的例子我们可以看到，我们的手机可以从两个维度进行变化，一个是品牌，一个是内存。此时我们就可以通过桥接模式将这两个维度分离开来，每一个维度都可以独立扩展。比如说手机品牌，可以又出现了苹果、三星、锤子等等。内存方面又可以生产10G、16G的了。从专业的角度来看可以这样定义桥接模式：

桥接模式是一种很实用的结构型设计模式，如果软件系统中某个类存在两个独立变化的维度，通过该模式可以将这两个维度分离出来，使两者可以独立扩展，让系统更加符合“单一职责原则”。

3、类图

上面的例子我们画一张类图来表示一下：

![图片.png](https://upload-images.jianshu.io/upload_images/21440240-ecdc1120e08eaef4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


基本上意思就是这，也就是我们买手机的时候有两个维度可供我们选择:一个是品牌一个是内存。

（1）main:指的是我们买手机的人。

（2）Abstraction（抽象类）：指的是手机抽象类phone

（3）Refined Abstraction（具体类）：指的是具体手机品牌(HuaWei XiaoMi)

（4）Implementor：在这里相当于手机的其他组件，内存。(Memory)

（5）ConcreteImplementor：具体的内存型号。(Memory６G)

下面我们就使用代码来实现一下。

二、实现桥接模式

第一步：定义Implementor，这里定义手机内存接口

```
class Memory{
  public:
   virtual void addMemory() = 0;
};

```

第二步：定义ConcreteImplementor，这里指具体的内存

内存这里定义了两种一种是6G，一种是8G

```
class Memory6G:public Memory{
  public:
    void addMemory()
    {
        cout << "phone use 6G memory" << endl;
    }
};
class Memory8G:public Memory{
  public:
    void addMemory()
    {
        cout << "phone use 8G memory" << endl;
    }
};
```

第三步：定义Abstraction手机抽象类

```
class Phone{
  public:
    Memory *phoneMemory;
    void setMemory(Memory *memory)
    {
        this->phoneMemory = memory;
    }
    virtual void buyPhone() = 0;
};
```

第四步：定义Refined Abstraction（具体的手机品牌）

首先是华为

```
class HuaWei:public Phone
{
  public:
    void buyPhone()
    {
        phoneMemory->addMemory();
        cout << "buy Huawei Phone" << endl;
    }
};

```

然后是小米

```
class XiaoMi:public Phone
{
  public:
    void buyPhone()
    {
        phoneMemory->addMemory();
        cout << "buy XiaoMi Phone" << endl;
    }
};
```

第五步：测试一下

```
int main()
{
    Phone *huawei = new HuaWei();
    huawei->setMemory(new Memory8G);
    huawei->buyPhone();

    Phone *xiaomi = new XiaoMi();
    xiaomi->setMemory(new Memory6G);
    xiaomi->buyPhone();
}
```
结果：
```
phone use 8G memory
buy Huawei Phone
phone use 6G memory
buy XiaoMi Phone

```

从代码就可以看出，购买手机的时候，品牌和内存两个维度是分开的。下面我们分析一下这个桥接模式

三、分析桥接模式

1、为什么使用桥接模式不使用继承呢？

继承是一种强耦合关系，子类与父类有非常紧密的依赖关系，父类的任何变化 都会导致子类发生变化。因此才使用桥接模式，使用了桥接模式之后，我们的两个维度就像桥梁一样被链接了起来。体现了松耦合的特性。

2、桥接模式的优点

（1）分离抽象和实现部分：把手机、内存抽象出来。实现与之分离。

（2）松耦合：两个维度分开

（3）单一职责原则：每个维度各干各的活

关于桥接模式的使用场景我觉得你只需要知道他的思想，然后在遇到问题的时候能够想到这种模式即可。
