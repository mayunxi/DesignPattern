# Design Pattern

设计模式

[gitee镜像:https://gitee.com/jaredtao/DesignPattern](https://gitee.com/jaredtao/DesignPattern)

## 简介

参考书籍 《图解设计模式》，实现23种设计模式

使用C++11实现

## CI - Travis/Appveyor

| [Ubuntu][lin-link] | [Windows][win-link] | [Coveralls][cov-link] |
| :---------------: | :-----------------: | :-------------------: |
| ![lin-badge]      | ![win-badge]        | ![cov-badge]          |

[lin-badge]: https://travis-ci.org/jaredtao/DesignPattern.svg?branch=master "Travis build status"
[lin-link]: https://travis-ci.org/jaredtao/DesignPattern "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/cckdwxaagrh2ncvo?svg=true "AppVeyor build status"
[win-link]: https://ci.appveyor.com/project/jiawentao/designpattern "AppVeyor build status"
[cov-badge]: https://coveralls.io/repos/github/wentaojia2014/DesignPattern/badge.svg?branch=master "Coveralls coverage"
[cov-link]: https://coveralls.io/github/wentaojia2014/DesignPattern?branch=master "Coveralls coverage"

## CI - Github-Actions

| [Github-Actions][actions-link]|
| :---------------:|
| ![actions-badge] |

[actions-link]: https://github.com/JaredTao/DesignPattern/actions "Github-Actions"
[actions-badge]: https://github.com/JaredTao/DesignPattern/workflows/DesignPatternCI/badge.svg  "Github-Actions"

## License
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/jaredtao/TaoJson/blob/master/LICENSE)

 简说设计模式


设计模式是一个很重要的内容，接下来将逐步的介绍一下常用的23种设计模式及其它的一些设计模式，每一个设计模式都配有模板代码和简单测试用例方便理解.


本篇主要介绍一下设计模式的基本原则，并给出目录。
一、什么是设计模式

设计模式是一套被反复使用的、多数人知晓的、经过分类编目的、代码设计经验的总结。使用设计模式是为了重用代码、让代码更容易被他人理解、保证代码可靠性。

二、设计模式的基本原则
1. 单一职责原则（Single Responsibility Principle，SRP）

类的职责要单一。就一个类而言，应该仅有一个引起它变化的原因。

  举个简单的例子，我们现在很多时候都直接使用手机拍照，但新闻、时尚杂志等的拍照使用的是相机。手机其实就相当于把相机耦合到手机中去了，而相机却只有拍照这一个职责。大多数时候，一件产品简单一些，职责单一一些，或许是更好的选择，这就是单一职责原则。

 如果一个类承担的职责过多，就等于把这些职责耦合在一起，一个职责的变化可能会削弱或者抑制这个类完成其它职责的能力。

2. 开闭原则（Open Close Principle，OCP）

软件实体可扩展，但不可修改。

 就好比“一国两制”，一个国家有两种制度，没有修改原有的管理制度，而是增加了一种新的制度。正所谓对于扩展的开放的，对于更改是封闭的。

3. 依赖倒转原则（Dependence Inversion Principle，DIP）

高层模块不应该依赖底层模块，两个都应该依赖抽象；抽象不应该依赖细节，细节应该依赖抽象。后面这句话换个方式说就是针对接口编程，不要对实现编程。

  举个例子，就好比你的电脑，如果CPU、内存、硬盘都需要依赖具体的主板，主板坏了，所有的部件都不能用了，这显然是不合理的。

 换句话说，即谁也不要依赖谁，除了约定的接口，大家都可以灵活自如。

4. 里氏代换原则（Liskov Substitution Principle，LSP）

子类型必须能够替换掉它们的父类型。

 举个例子，假如现在父类是鸟类，有个属性是可以飞，子类有个企鹅类，那么很明显企鹅类不能继承鸟类，因为鸟类有会飞的属性，如果子类企鹅类继承父类鸟类，则企鹅必须会飞。

5. 接口隔离原则（Interface Segregation Principle，ISP）

这个原则的意思是：使用多个隔离的接口，比使用单个接口要好。它还有另外一个意思是：降低类之间的耦合度。由此可见，其实设计模式就是从大型软件架构出发、便于升级和维护的软件设计思想，它强调降低依赖，降低耦合。


6. 迪米特法则（Law of Demeter，LoD）/最少知识原则（Least Knowledge Principle，LKP）

 一个类对自己依赖的类知道的越少越好；一个对象应该对其他对象有最少的了解。

   比如体育老师上课前清点人数，他让体育委员来替他清点人数，之后再由体育委员告知结果即可，老师本身并没有接触到其他学生。

 换句话说，每个类都应该尽量降低成员的访问权限，强调了类之间的松耦合。

7. 合成/聚合复用原则（Composite/Aggregate Reuse Principle，CARP）

 尽量使用合成/聚合，尽量不要使用类继承。

合成表示一种强的“拥有”关系，体现了严格的部分与整体的关系，他们的生命周期相同；而聚合表示一种弱的“拥有”关系，体现的是A对象可以包含B对象，但B对象不是A对象的一部分。

这里再举个简单的例子，大雁与翅膀是合成关系；而每只大雁都属于一个雁群，即一个雁群可以有多只大雁，所以大雁和雁群是聚合关系。

三、设计模式的类型

   常见的设计模式有23种，这些模式可分为三大类：创建型模式、结构型模式、行为型模式。

创建型模式提供了一种在创建对象的同时隐藏创建逻辑的方式，而不是使用new运算符直接实例化对象；结构型模式主要关注类和对象的组合；行为型模式特别关注对象间的通信。

下面给出一个目录，至于扩展的新模式后续有机会会继续更新。

## 目录

|编号| 类型   | 模式         | 说明                                                                                                |
|:----:| :----: | :----------: | :-------------------------------------------------------------------------------------------------: |
| 1 | 创建型 | 工厂方法模式 | [工厂方法模式](code/Create/FactoryMethod/README.md)                                                 |
| 2 | 创建型 | 抽象工厂模式 | [抽象工厂模式](code/Create/FactoryMethod/README.md)                                               |
| 3 | 创建型 | 建造者模式     | [建造者模式](code/Create/Builder/README.md)                                                           |
| 4 | 创建型 | 单例模式     | [单例模式](code/Create/Singleton/README.md)                                                         |
| 5 | 创建型 | 原型模式     | [原型模式](code/Create/Prototype/README.md)                                                         |
| 6 | 结构型 | 复合模式     | [复合模式](code/Struct/Composite/README.md)                                                         |
| 7 | 结构型 | 适配器模式   | [类适配器模式and对象适配器模式](code/Struct/Adapter/README.md)  |
| 8 | 结构型 | 装饰模式     | [装饰模式](code/Struct/Decorator/README.md)                                                         |
| 9 | 结构型 | 窗口模式     | [窗口模式](code/Struct/Facade/README.md)                                                            |
| 10 | 结构型 | 轻量模式     | [轻量模式](code/Struct/FlyWeight/README.md)                                                         |
| 11 | 结构型 | 代理模式     | [代理模式](code/Struct/Proxy/README.md)                                                             |
| 12 | 结构型 | 桥接模式     | [桥接模式](code/Struct/Bridge/README.md)                                                            |
| 13 | 行为型 | 迭代器模式   | [迭代器模式](code/Behavior/Iterator/README.md)                                                      |
| 14 | 行为型 | 模板方法模式 | [模板方法模式](code/Behavior/TemplateMethod/README.md)                                              |
| 15 | 行为型 | 策略模式     | [策略模式](code/Behavior/Strategy/README.md)                                                        |
| 16 | 行为型 | 访问者模式   | [访问者模式](code/Behavior/Visitor/README.md)                                                       |
| 17 | 行为型 | 责任链模式   | [责任链模式](code/Behavior/ResponsibilityChain/README.md)                                           |
| 18 | 行为型 | 仲裁者模式   | [仲裁者模式](code/Behavior/Mediator/README.md)                                                      |
| 19 | 行为型 | 观察者模式   | [观察者模式](code/Behavior/Observer/README.md)                                                      |
| 20 | 行为型 | 备忘录模式   | [备忘录模式](code/Behavior/Memento/README.md)                                                       |
| 21 | 行为型 | 状态模式     | [状态模式](code/Behavior/State/README.md)                                                           |
| 22 | 行为型 | 命令模式     | [命令模式](code/Behavior/Command/README.md)                                                         |
| 23| 行为型 | 解释器模式   | [解释器模式](code/Behavior/Interpreter/README.md)                                                   |
## 总结

### 创建型模式
创建型模式对类的实例化过程进行抽象，将软件中对象的创建和使用分离。
为了使软件的结构更加清晰，外界对于这些对象只需要知道共同的接口，而不清楚其内部实现细节，使整个系统的设计更加符合单一职责原则。

创建型模式在创建什么（what） 、由谁创建（who）、何时创建（when）等方面都为软件设计者提供了尽可能大的灵活性，隐藏了类的实例创建细节，通过隐藏对象
如何被创建和组合在一起，达到整个系统独立的目的

### 结构型模式

描述如何将类和对象结合在一起形成更大的结构，就像搭积木，通过简单积木的组合形成结构复杂、功能强大的结构
分为 类结构型模式 和 对象结构型模式：
* 类结构型模式

 关心类的组合，由多个类可以组合成一个更大的
系统，在类结构型模式中一般只存在继承关系和实现关系

* 对象结构型模式

 关心类与对象的组合，通过关联关系使得在一 个类中定义另一个类的实例对象，然后通过该对象调用其方法。 根据“合成复用原则”，在系统中尽量使用关联关系来替代继 承关系，因此大部分结构型模式都是对象结构型模式。
### 行为型模式
对不同的对象之间划分责任和算法的抽象。
行为型模式不仅仅关注类和对象的结构，而且重点关注它们之间的相互作用。
通过行为型模式，可以更加清晰地划分类与对象的职责，并研究系统在运行时实例对象 之间的交互。在系统运行时，对象并不是孤立的，它们可以通过相互通信与协作完成某些复杂功能，一个对象在运行时也将影响到其他对象的运行。

行为型模式分为类行为型模式和对象行为型模式两种：

* 类行为型模式

    类的行为型模式使用继承关系在几个类之间分配行为，类行为型模式主要通过多态等方式来分配父类与子类的职责。
* 对象行为型模式

    对象的行为型模式则使用对象的聚合关联关系来分配行为，对象行为型模式主要是通过对象关联等方式来分配两个或多个类的职责。根据“合成复用原则”，系统中要尽量使用关联关系来取代继承关系，因此大部分行为型设计模式都属于对象行为型设计模式。

### 代码结构

-code  上面"23种指针的使用方式"

    Create  5种创建型

    Behavior 11种行为型

    Struct  7种结构型

-Template 用C++模板技巧实现的，个别能复用的设计模式

    Create -> SingleTon

    单例模板，继承模板以实现复用。

    c++11的static保证多线程唯一实例。

    Behavior -> Observer

    观察者模板，继承模板以复用。
