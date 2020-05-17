## 一、什么是适配器模式

　　适配器这个词我们应该很熟悉，天天都在使用，手机充电时，电源线头头就叫电源适配器，干什么用的呢？把220V电压转换为手机充电时使用的电压，那适配器模式是不是很好理解了，下面看一下定义。

  **适配器模式（Adapter）**，将一个类的接口转换成客户希望的另外一个接口。使原本由于接口不兼容而不能一起工作的那些类可以一起工作。

 适配器模式有“**类适配器**”和“**对象适配器**”两种不同的形式。

###     1\. 类适配器

通过继承进行适配（类间继承）。UML结构图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-207c6eaf2344ef72.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

####     (1) Target

 Target目标角色，该角色定义把其他类转换为何种接口，也就是期望接口，通常情况下是一个接口或一个抽象类，一般不会是实现类。

```
 public interface Target {
     public void request();
 }
```

####     (2) Adaptee

Adaptee源角色，想把谁转换为目标角色，这个“谁”就是源角色，它是已经存在的、运行良好的类或对象。

```
public class Adaptee {

    public void specificRequest() {
        System.out.println("特殊请求");
    }

}
```

####     (3) Adapter

Adapter适配器角色，是适配器模式的核心角色，它的职责是通过继承或是类关联的方式把源角色转换为目标角色。

```
public class Adapter extends Adaptee implements Target {

    @Override
    public void request() {
        super.specificRequest();
    }

}
```

####     (4) ConcreteTarget

目标角色的实现类。

```
public class ConcreteTarget implements Target {

    @Override
    public void request() {
        System.out.println("普通请求");
    }

}
```

####     (5) Client

```
public class Client {

    public static void main(String[] args) {
        //原有业务逻辑
        Target target = new ConcreteTarget();
        target.request();

        //增加适配器后的业务逻辑
        Target target2 = new Adapter();
        target2.request();
    }

}
```

 此时原有业务逻辑输出“普通请求”，增加适配器后的业务逻辑输出“特殊请求”，下同。

###     2\. 对象适配器

通过对象层次的关联关系进行委托（对象的合成关系/关联关系）。UML结构图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-1c90d308c8c5d9d0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

####     (1) Target

客户所期待的接口。目标可以是具体的或抽象的类，也可以是接口。

```
public class Target {

    public void request() {
        System.out.println("普通请求");
    }

}
```

####     (2) Adaptee

需要适配的类。

```
public class Adaptee {

    public void specificRequest() {
        System.out.println("特殊请求");
    }

}
```

####     (3) Adapter

 通过在内部包装一个Adaptee对象，把源接口转换成目标接口。

```
public class Adapter extends Target {

    private Adaptee adaptee = new Adaptee();

    @Override
    public void request() {
        adaptee.specificRequest();
    }
}
```
####     (4) Client

```
public class Client {

    public static void main(String[] args) {
        Target target = new Adapter();
        target.request();
    }

}
```

## 二、适配器模式的应用

###     1\. 何时使用

*   系统需要使用现有的类，而此类的接口不符合系统的需要。
*   想建立一个可以重复使用的类，用于一些彼此之间没有太大关联的一些类。
*   通过接口转换，将一个类插入另一个类系中。

###     2\. 方法

*   继承或依赖。

###     3\. 优点

*   可以让任何两个没有关联的类一起运行。
*   增加了类的透明性。我们访问Target目标角色，但具体实现都委托给了源角色，而这些对高层模块是透明的，也是不需要关心的。
*   提高了类的复用度。源角色在原有的系统中还是可以正常使用，而在目标角色中也可以充当新的演员。
*   灵活性非常好。什么时候不想要适配器了，直接删掉就可以了，基本上就类似一个灵活的构件，想用就用，不想用就卸载。

###     4\. 缺点

*   过多使用适配器，会使系统非常零乱。
*   由于Java至多继承一个类，所以至多只能适配一个适配者类，而且目标类必须是抽象类。

###     5\. 使用场景

*   有动机地修改一个正常运行的系统的接口。

###     6\. 应用实例

*   电源适配器。
*   在Linux上运行Windows程序。
*   Java中的[JDBC](http://www.cnblogs.com/adamjwh/p/8865730.html)。
*   翻译官。

###     7\. 注意事项

*   只有碰到无法改变原有设计和代码的情况下，才考虑适配器模式。

## 三、适配器模式的实现

下面我们以翻译官为例，姚明刚去美国时，不懂英文，专门为他配备了翻译，特别是在比赛场上，教练、队员与他的对话全部都通过翻译来沟通，这里翻译就是适配器。现在编写一个适配器模式的例子，火箭队比赛，教练叫暂停时给后卫、中锋、前锋分配进攻和防守任务。UML图如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-7f19b203938a6fe0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

###     1\. Player类

 抽象球员类，有进攻和防守两种方法。

```
public abstract class Player {

    protected String name;

    public Player(String name) {
        this.name = name;
    }

    public abstract void attack();    //进攻
    public abstract void defense();    //防守
}
```

###     2\. 前锋、中锋、后卫类

 这里以前锋为例，其余的就不过多赘述了。重写了Player类中的进攻和防守两个方法，此时是英文的，尚未翻译。

```
public class Forwards extends Player {

    public Forwards(String name) {
        super(name);
    }

    @Override
    public void attack() {
        System.out.println("Forward " + name + " attack");
    }

    @Override
    public void defense() {
        System.out.println("Forward " + name + " defense");
    }

}
```

###     3\. ForeignCenters类

外籍中锋类。只能听懂中文。

```
public class ForeignCenters {

    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void attackChi() {
        System.out.println("中锋 " + name + " 进攻");
    }

    public void defenseChi() {
        System.out.println("中锋 " + name + " 防守");
    }
}
```

###     4\. Translator类

翻译者类，也就是适配器。对英文的进攻和防守进行翻译。

```
public class Translator extends Player {

    private ForeignCenters foreignCenter = new ForeignCenters();

    public Translator(String name) {
        super(name);
        foreignCenter.setName(name);
    }

    @Override
    public void attack() {
        foreignCenter.attackChi();
    }

    @Override
    public void defense() {
        foreignCenter.defenseChi();
    }

}
```

###     5\. Client
```
public class Client {

    public static void main(String[] args) {
        Player bPlayer = new Forwards("巴蒂尔");
        bPlayer.attack();

        Player mPlayer = new Guards("麦克格雷迪");
        mPlayer.attack();

        Player yPlayer = new Translator("姚明");
        yPlayer.attack();
        yPlayer.defense();
    }

}
```
运行结果如下：

![image](https://upload-images.jianshu.io/upload_images/21440240-3bd2b5bd0d8860ec.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

从运行结果可以看到，“attack”和“defense”命令在姚明这里被翻译成了“进攻”和“防守”。

## 四、类适配器和对象适配器的区别

从上面的内容可以看出来，类适配器是类间继承，对象适配器是对象的合成关系，也可以说是类的关联关系，这是两者的根本区别。

 由于对象适配器是通过类间的关联关系进行耦合的，因此在设计时就可以做到比较灵活，而类适配器就只能通过覆写源角色的方法进行扩展。

 在实际项目中，对象适配器使用到的场景较多。

  源码地址：[https://gitee.com/adamjiangwh/GoF](https://gitee.com/adamjiangwh/GoF)

分类: [GoF设计模式](https://www.cnblogs.com/adamjwh/category/1215890.html)
