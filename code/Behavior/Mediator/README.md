# [简说设计模式——中介者模式](https://www.cnblogs.com/adamjwh/p/10959987.html)

## 一、什么是中介者模式

　　中介这个词并不陌生，就是房屋中介的那个“中介”，就是中间人的意思。比如MVC模式，C（Controller控制器）是M（Model模型）和V（View视图）的中介者，在前后端交互时起到了中间人的作用。

>中介者模式又称为调停者模式，作为行为型的模式之一，本身是个很低调的模式，因为应用场合有限，所以不那么被人熟知

　　**中介者模式（Mediator）**，用一个中介对象来封装一系列的对象交互。中介者使各个对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。UML结构图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-22f63ef4a5db3e82.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

　　其中，Mediator是抽象中介者，定义了同事对象到中介者对象的接口；Colleague是抽象同事类；ConcreteMediator是具体中介者对象，实现抽象类的方法，它需要知道所有具体同事类，并从具体同事接收消息，向具体同事对象发出命令；ConcreteColleague是具体同事类，每个具体同事只知道自己的行为，而不了解其它同事类的情况，但它们却都认识中介者对象。

### 　　1\. 抽象中介者

　　抽象中介者角色定义统一的接口，用于各同事角色之间的通信。

```
class Mediator {

     //抽象的发送消息方法
public :
    virtual void send(string message, Colleague *colleague) = 0;

};
```

### 　　2\. 抽象同事类

　　每一个同事角色都知道中介者角色，而且与其它的同事角色通信的时候，一定要通过中介者角色协作。每个同事类的行为分两种：一种是同事本身行为，比如改变对象本身的状态，处理自己的行为等，这种行为叫做自发行为，与其它同事类或者中介者没有任何依赖；第二种是必须依赖中介者才能完成的行为，叫做依赖方法。

```
//抽象同事类
class Colleague {

protected:
    Mediator *mediator;

public:
    Colleague(Mediator *mediator) {
        this->mediator = mediator;
    }

};
```

### 　　3\. 具体中介者类

　　具体中介者角色通过协调各同事角色实现协作行为，因此它必须依赖于各个同事角色。

```
class ConcreteMediator:public Mediator {

private :
    ConcreteColleague1 *colleague1;
    ConcreteColleague2 *colleague2;

public:
    void setColleague1(ConcreteColleague1 *colleague1) {
        this->colleague1 = colleague1;
    }

    void setColleague2(ConcreteColleague2 *colleague2) {
        this->colleague2 = colleague2;
    }

    //@Override
 void send(string message, Colleague *colleague) {
        if(colleague == colleague1) {
            colleague2->notify(message);
        } else {
            colleague1->notify(message);
        }
    }

};

```
### 　　4\. 具体同事类

　　这里以ConcreteColleague1为例，ConcreteColleague2不再赘述。

```
//具体同事类A
class ConcreteColleague1:public Colleague
{
public:
    ConcreteColleague1(Mediator *mediator):Colleague(mediator)
    {

    }

public:
    void send(string message) {
        mediator->send(message, this);
    }

    void notify(string message) {
        cout << "同事1得到消息：" << message << endl;
    }

};
//具体同事类B
class ConcreteColleague2:public Colleague
{
public:
    ConcreteColleague2(Mediator *mediator) :Colleague(mediator){

    }

public:
    void send(string message) {
        mediator->send(message, this);
    }

    void notify(string message) {
        cout << "同事2得到消息：" << message << endl;
    }

};
```

### 　　5\. Client客户端

　　首先创建一个具体中介者对象，然后实例化两个具体同事类并与该中介者进行绑定，colleague1与colleague2通过中介者发送信息。

```
int main() {
        ConcreteMediator *mediator = new ConcreteMediator();

        ConcreteColleague1 *colleague1 = new ConcreteColleague1(mediator);
        ConcreteColleague2 *colleague2 = new ConcreteColleague2(mediator);

        mediator->setColleague1(colleague1);
        mediator->setColleague2(colleague2);

        colleague1->send("Nice to meet u.");
        colleague2->send("Nice to meet u too.");


}
```


　　运行结果如下：
　　![image](https://upload-images.jianshu.io/upload_images/21440240-8e88488d3ab8f37f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 二、中介者模式的应用

### 　　1\. 何时使用

*   多个类相互耦合，形成网状结构时

### 　　2\. 方法

*   将网状结构分离为星型结构

### 　　3\. 优点

*   减少类间依赖，降低了耦合
*   符合迪米特原则

### 　　4\. 缺点

*   中介者会膨胀的很大，而且逻辑复杂

### 　　5\. 使用场景

*   系统中对象之间存在比较复杂的引用关系
*   想通过一个中间类来封装多个类的行为，而又不想生成太多的子类

### 　　6\. 应用实例

*   联合国/WTO作为中介者协调各个国家
*   房屋中介/机场调度系统
*   MVC框架，其中C（Contorller控制器）是M（Model模型）和V（View视图）的中介者

### 　　7\. 注意事项

*   不应当在职责混乱时使用

## 三、中介者模式的实现

　　上面我们有提到，联合国作为一个由各国代表组成，用来维护国际和平与安全，解决国际间经济、社会、文化和人道主义性质的问题的角色，它就是一个调停者、中介者的角色，国与国直接完全完全可以通过“联合国”这个中介者来发生关系，而不用直接通信。

　　下面就以联合国安理会作为中介者，了解一下中介者模式。UML图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-cf190fe125cd77af.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 　　1\. 联合国机构

　　抽象中介者。

<pre>1 public abstract class UnitedNations { 2
3     public abstract void declare(String message, Country country); 4
5 }</pre>

### 　　2\. 国家类

　　抽象国家类，需声明中介者角色。

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-9069883bdac863c9.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

<pre>1 public class Country { 2
3     protected UnitedNations unitedNations; 4
5     public Country(UnitedNations unitedNations) { 6         this.unitedNations = unitedNations; 7 } 8
9 }</pre>

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-50af05fb76d22cb6.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

### 　　3\. 具体国家类

　　具体国家类，继承了抽象国家类。这里以USA类为例，Iraq类不再赘述。

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-78766bec3fab7e6d.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

<pre> 1 public class USA extends Country { 2
 3     public USA(UnitedNations unitedNations) { 4         super(unitedNations);
 5     }
 6
 7     public void declare(String message) { 8         unitedNations.declare(message, this);
 9 } 10
11     public void getMessage(String message) { 12         System.out.println("美国获得对方信息：" + message); 13 } 14
15 }</pre>

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-6707e268599bff01.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

### 　　4\. 联合国安理会

　　具体中介者角色，继承抽象中介者，重写其declare()方法，对不同国家发送不同信息。

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-0d8aa8f8d470218c.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

<pre> 1 public class UnitedNationsSecurityCouncil extends UnitedNations { 2
 3     private USA usa; 4     private Iraq iraq; 5
 6     public void setUsa(USA usa) { 7         this.usa = usa; 8     }
 9
10     public void setIraq(Iraq iraq) { 11         this.iraq = iraq; 12 } 13
14 @Override 15     public void declare(String message, Country country) { 16         if(country == usa) { 17 iraq.getMessage(message); 18         } else { 19 usa.getMessage(message); 20 } 21 } 22
23 }</pre>

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-b073054eab8f469a.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

### 　　5\. Client客户端

　　实例化一个联合国安理会对象，两国通过联合国安理会进行对话。

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-45f8b538e93ceea6.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

<pre> 1 public class Client { 2
 3     public static void main(String[] args) { 4
 5         UnitedNationsSecurityCouncil UNSC = new UnitedNationsSecurityCouncil(); 6
 7         USA usa = new USA(UNSC); 8         Iraq iraq = new Iraq(UNSC); 9
10 UNSC.setUsa(usa); 11 UNSC.setIraq(iraq); 12
13         usa.declare("不准研制核武器"); 14         iraq.declare("我们没有核武器"); 15 } 16
17 }</pre>

[![复制代码](https://upload-images.jianshu.io/upload_images/21440240-0e4f1f17848f927c.gif?imageMogr2/auto-orient/strip)](javascript:void(0); "复制代码")

　　运行结果如下：

　　![image](https://upload-images.jianshu.io/upload_images/21440240-c3bb2485cd1a4fd5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
