在现实生活中，常常需要对现有产品增加新的功能或美化其外观，如房子装修、相片加相框等。在软件开发过程中，有时想用一些现存的组件。这些组件可能只是完成了一些核心功能。但在不改变其结构的情况下，可以动态地扩展其功能。所有这些都可以釆用装饰模式来实现。

## 装饰模式的定义与特点

装饰（Decorator）模式的定义：指在不改变现有对象结构的情况下，动态地给该对象增加一些职责（即增加其额外功能）的模式，它属于对象结构型模式。

装饰（Decorator）模式的主要优点有：

*   采用装饰模式扩展对象的功能比采用继承方式更加灵活。
*   可以设计出多个不同的具体装饰类，创造出多个不同行为的组合。

其主要缺点是：装饰模式增加了许多子类，如果过度使用会使程序变得很复杂。

## 装饰模式的结构与实现

通常情况下，扩展一个类的功能会使用继承方式来实现。但继承具有静态特征，耦合度高，并且随着扩展功能的增多，子类会很膨胀。如果使用组合关系来创建一个包装对象（即装饰对象）来包裹真实对象，并在保持真实对象的类结构不变的前提下，为其提供额外的功能，这就是装饰模式的目标。下面来分析其基本结构和实现方法。

####
1\. 模式的结构

装饰模式主要包含以下角色。

1.  抽象构件（Component）角色：定义一个抽象接口以规范准备接收附加责任的对象。
2.  具体构件（Concrete    Component）角色：实现抽象构件，通过装饰角色为其添加一些职责。
3.  抽象装饰（Decorator）角色：继承抽象构件，并包含具体构件的实例，可以通过其子类扩展具体构件的功能。
4.  具体装饰（ConcreteDecorator）角色：实现抽象装饰的相关方法，并给具体构件对象添加附加的责任。

装饰模式的结构图如图 1 所示。

![装饰模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-c3d2f378eae1ab29.gif?imageMogr2/auto-orient/strip)

图1 装饰模式的结构图

#### 2\. 模式的实现

装饰模式的实现代码如下：

```#include<stdio.h>
//抽象构件角色
class  Component
{
    public:
    virtual void operation() = 0;
};
//具体构件角色
class ConcreteComponent:public Component
{
public :
    ConcreteComponent()
    {
        printf("创建具体构件角色\n");
    }
    void operation()
    {
        printf("调用具体构件角色的方法operation()\n");
    }
};
//抽象装饰角色
class Decorator:public Component
{
private :
    Component *component;
public :
    Decorator(Component *component)
    {
        this->component=component;
    }
    void operation()
    {
        component->operation();
    }
};
//具体装饰角色
class ConcreteDecorator:public Decorator
{
public :
    ConcreteDecorator(Component *component):Decorator(component){
    }
    void operation()
    {
        //子类如果要调用父类的成员函数，可以使用::限定符（父类名::父类成员函数）
        Decorator::operation();
        addedFunction();
    }
    void addedFunction()
    {
        printf("为具体构件角色增加额外的功能addedFunction()\n");
    }
};
int main()
{
    Component *p=new ConcreteComponent();
    p->operation();
    printf("---------------------------------\n");
    Component *d=new ConcreteDecorator(p);
    d->operation();
    return 0;
}

```

程序运行结果如下：

```
创建具体构件角色
调用具体构件角色的方法operation()
---------------------------------
调用具体构件角色的方法operation()
为具体构件角色增加额外的功能addedFunction()
```
## 装饰模式的应用实例

【例1】用装饰模式实现游戏角色“莫莉卡·安斯兰”的变身。

分析：在《恶魔战士》中，游戏角色“莫莉卡·安斯兰”的原身是一个可爱少女，但当她变身时，会变成头顶及背部延伸出蝙蝠状飞翼的女妖，当然她还可以变为穿着漂亮外衣的少女。这些都可用装饰模式来实现，在本实例中的“莫莉卡”原身有 setImage(String t) 方法决定其显示方式，而其 变身“蝙蝠状女妖”和“着装少女”可以用 setChanger() 方法来改变其外观，原身与变身后的效果用 display() 方法来显示（[点此下载其原身和变身后的图片](http://c.biancheng.net/uploads/soft/181113/3-1Q115142F6.zip)），图 2 所示是其结构图。

![游戏角色“莫莉卡·安斯兰”的结构图](https://upload-images.jianshu.io/upload_images/21440240-ef3a7979aac223ab.gif?imageMogr2/auto-orient/strip)

图2 游戏角色“莫莉卡·安斯兰”的结构图

程序代码如下：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  package  decorator;
2.  import  java.awt.*;
3.  import  javax.swing.*;
4.  public class  MorriganAensland
5.  {
6.  public static void main(String[] args)
7.  {
8.  Morrigan  m0=new original();
9.  m0.display();
10.  Morrigan  m1=new Succubus(m0);
11.  m1.display();
12.  Morrigan  m2=new Girl(m0);
13.  m2.display();
14.  }
15.  }
16.  //抽象构件角色：莫莉卡
17.  interface  Morrigan
18.  {
19.  public void display();
20.  }
21.  //具体构件角色：原身
22.  class  original extends JFrame implements Morrigan
23.  {
24.  private static final long serialVersionUID = 1L;
25.  private String  t="Morrigan0.jpg";
26.  public original()
27.  {
28.  super("《恶魔战士》中的莫莉卡·安斯兰");
29.  }
30.  public void setImage(String  t)
31.  {
32.  this.t=t;
33.  }
34.  public void display()
35.  {
36.  this.setLayout(new FlowLayout());
37.  JLabel  l1=new JLabel(new ImageIcon("src/decorator/"+t));
38.  this.add(l1);
39.  this.pack();
40.  this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
41.  this.setVisible(true);
42.  }
43.  }
44.  //抽象装饰角色：变形
45.  class  Changer implements Morrigan
46.  {
47.  Morrigan  m;
48.  public Changer(Morrigan  m)
49.  {
50.  this.m=m;
51.  }
52.  public void display()
53.  {
54.  m.display();
55.  }
56.  }
57.  //具体装饰角色：女妖
58.  class  Succubus extends Changer
59.  {
60.  public Succubus(Morrigan  m)
61.  {
62.  super(m);
63.  }
64.  public void display()
65.  {
66.  setChanger();
67.  super.display();
68.  }
69.  public void setChanger()
70.  {
71.  ((original) super.m).setImage("Morrigan1.jpg");
72.  }
73.  }
74.  //具体装饰角色：少女
75.  class  Girl extends Changer
76.  {
77.  public Girl(Morrigan  m)
78.  {
79.  super(m);
80.  }
81.  public void display()
82.  {
83.  setChanger();
84.  super.display();
85.  }
86.  public void setChanger()
87.  {
88.  ((original) super.m).setImage("Morrigan2.jpg");
89.  }
90.  }

</pre>

程序运行结果如图 3 所示。

![游戏角色“莫莉卡·安斯兰”的变身](https://upload-images.jianshu.io/upload_images/21440240-6f2219bbb9f56318.gif?imageMogr2/auto-orient/strip)

图3 游戏角色“莫莉卡·安斯兰”的变身

## 装饰模式的应用场景

前面讲解了关于装饰模式的结构与特点，下面介绍其适用的应用场景，装饰模式通常在以下几种情况使用。

*   当需要给一个现有类添加附加职责，而又不能采用生成子类的方法进行扩充时。例如，该类被隐藏或者该类是终极类或者采用继承方式会产生大量的子类。
*   当需要通过对现有的一组基本功能进行排列组合而产生非常多的功能时，采用继承关系很难实现，而采用装饰模式却很好实现。
*   当对象的功能要求可以动态地添加，也可以再动态地撤销时。

装饰模式在 [Java](http://c.biancheng.net/java/) 语言中的最著名的应用莫过于 Java I/O 标准库的设计了。例如，InputStream 的子类 FilterInputStream，OutputStream 的子类 FilterOutputStream，Reader 的子类 BufferedReader 以及 FilterReader，还有 Writer 的子类 BufferedWriter、FilterWriter 以及 PrintWriter 等，它们都是抽象装饰类。

下面代码是为 FileReader 增加缓冲区而采用的装饰类 BufferedReader 的例子：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  BufferedReader  in=new BufferedReader(new FileReader("filename.txtn));
2.  String s=in.readLine();

</pre>

## 装饰模式的扩展

装饰模式所包含的 4 个角色不是任何时候都要存在的，在有些应用环境下模式是可以简化的，如以下两种情况。

(1) 如果只有一个具体构件而没有抽象构件时，可以让抽象装饰继承具体构件，其结构图如图 4 所示。

![只有一个具体构件的装饰模式](https://upload-images.jianshu.io/upload_images/21440240-2e2a2281fc75a552.gif?imageMogr2/auto-orient/strip)

图4 只有一个具体构件的装饰模式

(2) 如果只有一个具体装饰时，可以将抽象装饰和具体装饰合并，其结构图如图 5 所示。

![只有一个具体装饰的装饰模式](https://upload-images.jianshu.io/upload_images/21440240-781cf1bc0f2fd522.gif?imageMogr2/auto-orient/strip)

图5 只有一个具体装饰的装饰模式
