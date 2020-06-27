# [简说设计模式——外观模式](https://www.cnblogs.com/adamjwh/p/9048594.html)

## 一、什么是外观模式

　　有些人可能炒过股票，但其实大部分人都不太懂，这种没有足够了解证券知识的情况下做股票是很容易亏钱的，刚开始炒股肯定都会想，如果有个懂行的帮帮手就好，其实基金就是个好帮手，支付宝里就有许多的基金，它将投资者分散的资金集中起来，交由专业的经理人进行管理，投资于股票、债券、外汇等领域，而基金投资的收益归持有者所有，管理机构收取一定比例的托管管理费用。

　　其实本篇要说的这个设计模式就和这很有关系，由于当投资者自己买股票时，由于众多投资者对众多股票的联系太多，反而不利于操作，这在软件中就成为耦合性太高，而有了基金后，就变成众多用户只和基金打交道，关心基金的上涨和下跌，而实际上的操作确是基金经理人与股票和其它投资产品打交道，这就是外观模式。

　　**外观模式（Facade）**，为子系统中的一组接口提供一个一致的界面，此模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。UML结构图如下：

 ![image](https://upload-images.jianshu.io/upload_images/21440240-a4f3026a5afaa25b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

　　其中Facade是外观角色，也叫门面角色，客户端可以调用这个角色的方法，此角色知晓子系统的所有功能和责任，将客户端的请求代理给适当的子系统对象；Subsystem是子系统角色，可以同时拥有一个或多个子系统，每一个子系统都不是一个单独的类，而是一个类的集合，子系统并不知道门面的存在。

### 　　1\. 外观类

　　这里我给出了四个Subsystem子系统，分别为A、B、C、D。

```
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
```

###  　　2\. Subsystem子系统角色

这里为了不过多赘述，只放上A的代码，其余子系统类似。

```
class SubSystemA {
public:
    void dosomethingA() {
        cout << "子系统方法A" << endl;
    }

};
```

### 　　3\. Client客户端
```
int main()
{
    Facade *facade = new Facade();
    facade->methodA();
    facade->methodD();
}

```

　　运行结果如下：

　　![image](https://upload-images.jianshu.io/upload_images/21440240-4cfdc539a862d6fd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 二、外观模式的应用

### 　　1\. 何时使用

*   客户端不需要知道系统内部的复杂联系，整个系统只提供一个“接待员”即可
*   定义系统的入口

###  　　2\. 方法

*   客户端不与系统耦合，外观类与系统耦合

###  　　3\. 优点

*   减少了系统的相互依赖
*   提高了灵活性。不管系统内部如何变化，只要不影响到外观对象，任你自由活动
*   提高了安全性。想让你访问子系统的哪些业务就开通哪些逻辑，不在外观上开通的方法，你就访问不到

###  　　4\. 缺点

*   不符合开不原则，修改很麻烦

###  　　5\. 使用场景

*   为一个复杂的模块或子系统提供一个外界访问的接口
*   子系统相对独立，外界对子系统的访问只要黑箱操作即可
*   预防低水平人员带来的风险扩散

###  　　6\. 应用实例

*   基金（用户只和基金打交道，实际操作为基金经理人与股票和其它投资品打交道）

##  三、外观模式的实现

　　我们就以开篇说的基金为例，来编写一下代码，熟悉外观模式的使用。UML图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-d97680bd5e3e89cd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 　　1\. 基金类（Fund）

　　基金类，基金经理人通过该类作为中间交互者，可以接受投资者的资金，统一对股票、国债、房地产进行购买和赎回操作。

```
public class Fund {

    Stock1 stock1;
    Stock2 stock2;
    Stock3 stock3;
    NationalDebt1 nationalDebt1;
    Realty1 realty1;

    public Fund() {
        stock1 = new Stock1();
        stock2 = new Stock2();
        stock3 = new Stock3();
        nationalDebt1 = new NationalDebt1();
        realty1 = new Realty1();
    }

    //购买基金
    public void buyFund() {
        stock1.buy();
        stock2.buy();
        stock3.buy();
        nationalDebt1.buy();
        realty1.buy();
    }

    //赎回基金
    public void sellFund() {
        stock1.sell();
        stock2.sell();
        stock3.sell();
        nationalDebt1.sell();
        realty1.sell();
    }

}
```
###  　　2\. 股票、国债、房地产类

　　这里放一个股票作为示例，其余债券类似。内部由买入和卖出两种操作。

```
public class Stock1 {

    //买股票
    public void buy() {
        System.out.println("股票1买入");
    }

    //卖股票
    public void sell() {
        System.out.println("股票1卖出");
    }

}
```

### 　　3\. Client客户端

　　用户通过该类对基金进行购买和赎回操作。

```
public class Client {

    public static void main(String[] args) {
        Fund fund = new Fund();

        //基金购买
        fund.buyFund();
        System.out.println("-------------");
        //基金赎回
        fund.sellFund();
    }

}
```

　　运行结果如下：

　　![image](https://upload-images.jianshu.io/upload_images/21440240-5bff2f467dcb83d7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

　　由此可见，外观模式十分的简单，我们只需在客户端购买和赎回即可，内部的任何操作都不需要我们关注，对于面向对象有一定基础的朋友，即使没有听说过外观模式，也完全有可能在很多时候使用它，因为它完美地体现了依赖倒转原则和迪米特法则的思想，所以是非常常用的模式之一。

　　我们使用外观模式的情况有很多，比如经典的MVC三层架构，可以考虑在数据访问层和业务逻辑层、业务逻辑层和表示层的层与层之间简历外观Facade，降低耦合。对于复杂难以维护的老系统，直接去修改或扩展都可能产生很多问题，可以分两个小组，一个开发Facade与老系统的交互，另一个只要了解Facade接口，直接开发新系统调用这些接口即可。
