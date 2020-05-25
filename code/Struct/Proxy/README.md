## 一、什么是代理模式

　　关于代理模式，我们听到的见到的最多的可能就是静态代理、动态代理之类的，当然还有大家都知道的Spring Aop，这里我们先不谈这些个代理，先说个简单的例子。游戏代练应该都听说过，许多人肯定也找过代练，曾经DNF、LOL、COC等等游戏的代练很多，当然现在各类游戏层出不穷，也都有各种代练，那这里所谓的代练是什么？就是Proxy，也即代理类，那游戏代练这件事就是一个代理模式。

　　如果觉得不好理解可以这么想，代练的流程是，你把自己的账号交给代练人员，让他们帮你打怪升级，而你只需要提供账号即可。那代练人员那边，他所要做的就是登陆你的账号，然后替你打游戏，从第三者的角度来看，你这个角色在打怪升级，但这个第三者并不知道是不是你本人在打游戏，他只能看到你这个账号正在打怪升级，但并不需要知道后面打游戏的是谁。这就是代理模式，由他人代理玩游戏。

　　如果觉得这个还不好理解，那再说一个例子。假设我现在要邀请明星来上节目，我是直接给这个明星打电话吗？当然不是，是给他的经纪人打电话，然后再由经纪人通知到该明星，这里经纪人充当的就是代理的角色。

　　更常见的例子就是Windows的快捷方式，通过快捷方式，我们可以访问某个文件夹下的exe文件，这就是一个典型的代理模式，它将接口，按上面游戏的说法说就是代练的账号，提供了出来，我们只需点击快捷方式，它会帮我们运行指定目录下的指定程序。说了这么多，现在来看一下代理模式的定义。

　　**代理模式（Proxy）**，为其他对象提供一种代理以控制对这个对象的访问。UML结构图如下：

 ![image](https://upload-images.jianshu.io/upload_images/21440240-595e802bd3f2986d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

　　其中，Subject是主题角色，定义了RealSubject和Proxy的共同接口；RealSubject是具体主题角色，定义了Proxy所代表的真实实体；Proxy为代理主题角色，保存一个引用使代理可以访问实体，并提供一个与Subject的接口相同的接口。

### 　　1\. Subject抽象类

　　定义了RealSubject和Proxy的共同接口，这样就在任何使用RealSubject的地方都可以使用Proxy。

```
class Subject
{
    virtual void request()=0;
};
```

### 　　2\. RealSubject类

定义了Proxy所代表的真实实体。
```
class RealSubject:public Subject {

    //@Override
public:
void request() {
        printf("真实的请求RealSubject\n");
    }

};
```

### 　　3\. Proxy类

　　代理类。一个代理类可以代理多个被委托者或被代理者，因此一个代理类具体代理哪个真实主题角色，是由场景类决定的。

```
class Proxy:public Subject {

private:
    RealSubject *realSubject = NULL;

public:
    Proxy() {
        this->realSubject = new RealSubject();
    }

    //@Override
    void request() {
        this->before();
        this->realSubject->request();
        this->after();
    }


private:
    //预处理
    void before() {
        printf("-------before------\n");
    }

    //善后处理
    void after() {
        printf("-------after-------\n");
    }
};
```
###  　　4\. Client客户端

```
int main()
{
    Proxy *proxy = new Proxy();
    proxy->request();
}
```

 　　运行结果如下：

　　![image](https://upload-images.jianshu.io/upload_images/21440240-1615866bbb658415.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

* `此设计模式和对象适配器模式很像，区别在于代理模式中RealSubject继承自Subject`
* ` 和策略模式也很像，区别RealSubject *realSubject变为Subject *subject，可以指向由Subject派生出的对象，由Proxy创建时传入。`

## 二、代理模式的应用

### 　　1\. 何时使用

*   想在访问一个类的时候做一些控制时

###  　　2\. 方法

*   增加中间层

###  　　3\. 优点

*   职责清晰。真实的角色就是实现实际的业务逻辑，不用担心其他非本职责的事务
*   高扩展性。代理类完全可以在不做任何修改的情况下使用
*   智能化。比如动态代理

###  　　4\. 缺点

*   有些类型的代理模式可能会造成请求的处理速度变慢
*   实现代理模式需要额外的工作，有些代理模式的实现非常复杂

###  　　5\. 使用场景

*   远程代理。为一个对象在不同的地址空间提供局部代表
*   虚拟代理。根据需要创建开销很大的对象，通过它来存放实例化需要很长时间的真实对象
*   安全代理。用来控制真实对象访问时的权限
*   智能指引，当调用真实的对象时，代理处理另外一些事

###  　　6\. 应用实例

*   游戏代练
*   邀请明星，联系其经纪人
*   Windows快捷方式
*   火车票代售点
*   Spring AOP

###  　　7\. 注意事项

*   与适配器模式的区别：适配器模式主要改变所考虑对象的接口，而代理模式不能改变所代理类的接口
*   与装饰模式区别：装饰模式是为了增强功能，而代理模式是为了加以控制

##  三、代理模式的实现

　　这里我们就以上面说过的游戏代练为例。UML图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-484af0e042436855.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 　　1\. IGamePlayer类

　　游戏玩家接口。由登陆、杀怪、升级三个方法。

```
class IGamePlayer {
    //登陆
public:
    virtual void login(string user, string password) =0;
    //杀怪
    virtual void killBoss() = 0;
    //升级
    virtual void upgrade() = 0;
};
```

###  　　2\. GamePlayer类

　　游戏玩家。正常玩家登陆、打怪、升级。

```
class GamePlayer:public IGamePlayer {

private:
    string name = "";

public:
    GamePlayer(string name) {
        this->name = name;
    }

    //@Override
public :
    void login(string user, string password) {
        cout << "登录名为<" + user + ">的用户<" + this->name + ">登陆成功！" << endl;
    }


   void killBoss() {
        cout << "<" + this->name + ">在打怪！" << endl;
    }


    void upgrade() {
        cout << "<" + this->name + ">升了一级！" << endl;
    }

};
```
###  　　3\. GamePlayerProxy类

　　游戏代练。也即代理类，用于代替玩家登陆、打怪、升级。

```
class GamePlayerProxy:public IGamePlayer {

private:
    IGamePlayer *gamePlayer = NULL;

public:
    GamePlayerProxy(IGamePlayer *gamePlayer) {
        this->gamePlayer = gamePlayer;
    }

    //@Override
public :
    void login(string user, string password) {
        this->gamePlayer->login(user, password);
    }


    void killBoss() {
        this->gamePlayer->killBoss();
    }

    void upgrade() {
        this->gamePlayer->upgrade();
    }

};
```
### 　　4\. Client客户端

　　玩家找了一个代练，代练登陆了该玩家的账号，然后替该玩家打怪升级。
```
int main()
{
    GamePlayer *player1 = new GamePlayer("player1");

    GamePlayerProxy *proxy = new GamePlayerProxy(player1);
    proxy->login("admin","123");
    proxy->killBoss();
    proxy->upgrade();
}
```

 　　运行结果如下：

　　![image](https://upload-images.jianshu.io/upload_images/21440240-527741273565e97e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

　　从这个结果我们只能看到有人登陆了这个账号，他正在打怪升级，但并不知道是不是代练，这就是代理模式。

　　有关代理模式的延伸（静态代理、动态代理）详见[《简说设计模式——代理模式（续）》](https://www.cnblogs.com/adamjwh/p/10907526.html)。

分类: [GoF设计模式](https://www.cnblogs.com/adamjwh/category/1215890.html)
