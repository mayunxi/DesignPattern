# 轻量模式

[](http://fudao.biancheng.net)

在面向对象程序设计过程中，有时会面临要创建大量相同或相似对象实例的问题。创建那么多的对象将会耗费很多的系统资源，它是系统性能提高的一个瓶颈。例如，围棋和五子棋中的黑白棋子，图像中的坐标点或颜色，局域网中的路由器、交换机和集线器，教室里的桌子和凳子等。这些对象有很多相似的地方，如果能把它们相同的部分提取出来共享，则能节省大量的系统资源，这就是享元模式的产生背景。

## 享元模式的定义与特点

享元（Flyweight）模式的定义：运用共享技术来有效地支持大量细粒度对象的复用。它通过共享已经存在的对象来大幅度减少需要创建的对象数量、避免大量相似类的开销，从而提高系统资源的利用率。

享元模式的主要优点是：相同对象只要保存一份，这降低了系统中对象的数量，从而降低了系统中细粒度对象给内存带来的压力。

其主要缺点是：

1.  为了使对象可以共享，需要将一些不能共享的状态外部化，这将增加程序的复杂性。
2.  读取享元模式的外部状态会使得运行时间稍微变长。

## 享元模式的结构与实现

享元模式中存在以下两种状态：

1.  内部状态，即不会随着环境的改变而改变的可共享部分；
2.  外部状态，指随环境改变而改变的不可以共享的部分。享元模式的实现要领就是区分应用中的这两种状态，并将外部状态外部化。下面来分析其基本结构和实现方法。

#### 1\. 模式的结构

享元模式的主要角色有如下。

1.  抽象享元角色（Flyweight）:是所有的具体享元类的基类，为具体享元规范需要实现的公共接口，非享元的外部状态以参数的形式通过方法传入。
2.  具体享元（Concrete Flyweight）角色：实现抽象享元角色中所规定的接口。
3.  非享元（Unsharable Flyweight)角色：是不可以共享的外部状态，它以参数的形式注入具体享元的相关方法中。
4.  享元工厂（Flyweight Factory）角色：负责创建和管理享元角色。当客户对象请求一个享元对象时，享元工厂检査系统中是否存在符合要求的享元对象，如果存在则提供给客户；如果不存在的话，则创建一个新的享元对象。

图 1 是享元模式的结构图。图中的 UnsharedConcreteFlyweight 是非享元角色，里面包含了非共享的外部状态信息 info；而 Flyweight 是抽象享元角色，里面包含了享元方法 operation(UnsharedConcreteFlyweight state)，非享元的外部状态以参数的形式通过该方法传入；ConcreteFlyweight 是具体享元角色，包含了关键字 key，它实现了抽象享元接口；FlyweightFactory 是享元工厂角色，它逝关键字 key 来管理具体享元；客户角色通过享元工厂获取具体享元，并访问具体享元的相关方法。

![享元模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-b541564a5771b92f.gif?imageMogr2/auto-orient/strip)

图1 享元模式的结构图

#### 2\. 模式的实现

享元模式的实现代码如下：

```
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<map>
using namespace std;

//非享元角色
class UnsharedConcreteFlyweight
{
private:
    string info;

public:
    UnsharedConcreteFlyweight(string info)
    {
        this->info=info;
    }
    string getInfo()
    {
        return info;
    }
    void setInfo(string info)
    {
        this->info=info;
    }
};
//抽象享元角色
class Flyweight
{
public:
    virtual void operation(UnsharedConcreteFlyweight state) = 0;
};
//具体享元角色
class ConcreteFlyweight:public Flyweight
{
private:
    string key;

public:
    ConcreteFlyweight(string key)
    {
        this->key = key;
        cout << "具体享元" << key << "被创建！" << endl;
    }
    void operation(UnsharedConcreteFlyweight outState)
    {
        cout << "具体享元" << key << "被调用，";
        cout << "非享元信息是:" << outState.getInfo() << endl;
    }
};
//享元工厂角色
class FlyweightFactory
{
private:
    map<string, Flyweight*> flyweights;
public:
    Flyweight *getFlyweight(string key)
    {
        map<string,Flyweight*>::iterator iter = flyweights.find(key);
        Flyweight *flyweight;
        if(iter != flyweights.end())
        {
            flyweight = iter->second;
            cout << "具体享元" << key << "已经存在，被成功获取！" << endl;
        }
        else
        {
            flyweight=new ConcreteFlyweight(key);
            flyweights.insert(make_pair(key,flyweight));
        }
        return flyweight;
    }
};

int  main()
{
    FlyweightFactory *factory=new FlyweightFactory();
    Flyweight *f01=factory->getFlyweight("a");
    Flyweight *f02=factory->getFlyweight("a");
    Flyweight *f03=factory->getFlyweight("a");
    Flyweight *f11=factory->getFlyweight("b");
    Flyweight *f12=factory->getFlyweight("b");
    f01->operation(UnsharedConcreteFlyweight("第1次调用a。"));
    f02->operation(UnsharedConcreteFlyweight("第2次调用a。"));
    f03->operation(UnsharedConcreteFlyweight("第3次调用a。"));
    f11->operation(UnsharedConcreteFlyweight("第1次调用b。"));
    f12->operation(UnsharedConcreteFlyweight("第2次调用b。"));

    return 0;
}

```

程序运行结果如下：

```
具体享元a被创建！
具体享元a已经存在，被成功获取！
具体享元a已经存在，被成功获取！
具体享元b被创建！
具体享元b已经存在，被成功获取！
具体享元a被调用，非享元信息是:第1次调用a。
具体享元a被调用，非享元信息是:第2次调用a。
具体享元a被调用，非享元信息是:第3次调用a。
具体享元b被调用，非享元信息是:第1次调用b。
具体享元b被调用，非享元信息是:第2次调用b。
```

## 享元模式的应用实例

【例1】享元模式在五子棋游戏中的应用。

分析：五子棋同围棋一样，包含多个“黑”或“白”颜色的棋子，所以用享元模式比较好。

本实例中的棋子（ChessPieces）类是抽象享元角色，它包含了一个落子的 DownPieces(Graphics g,Point pt) 方法；白子（WhitePieces）和黑子（BlackPieces）类是具体享元角色，它实现了落子方法；Point 是非享元角色，它指定了落子的位置；WeiqiFactory 是享元工厂角色，它通过 ArrayList 来管理棋子，并且提供了获取白子或者黑子的 getChessPieces(String type) 方法；客户类（Chessboard）利用 Graphics 组件在框架窗体中绘制一个棋盘，并实现 mouseClicked(MouseEvent e) 事件处理方法，该方法根据用户的选择从享元工厂中获取白子或者黑子并落在棋盘上。图 2 所示是其结构图。

![五子棋游戏的结构图](https://upload-images.jianshu.io/upload_images/21440240-808cb8c94a930941.gif?imageMogr2/auto-orient/strip)

图2 五子棋游戏的结构图

程序代码如下：
```

1.  package  flyweight;
2.  import  java.awt.*;
3.  import  java.awt.event.*;
4.  import  java.util.ArrayList;
5.  import  javax.swing.*;
6.  public class  WzqGame
7.  {
8.  public static void main(String[] args)
9.  {
10.  new Chessboard();
11.  }
12.  }
13.  //棋盘
14.  class  Chessboard extends MouseAdapter
15.  {
16.  WeiqiFactory  wf;
17.  JFrame  f;
18.  Graphics  g;
19.  JRadioButton  wz;
20.  JRadioButton  bz;
21.  private final int x=50;
22.  private final int y=50;
23.  private final int w=40;    //小方格宽度和高度
24.  private final int rw=400;    //棋盘宽度和高度
25.  Chessboard()
26.  {
27.  wf=new WeiqiFactory();
28.  f=new JFrame("享元模式在五子棋游戏中的应用");
29.  f.setBounds(100,100,500,550);
30.  f.setVisible(true);
31.  f.setResizable(false);
32.  f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
33.  JPanel  SouthJP=new JPanel();
34.  f.add("South",SouthJP);
35.  wz=new JRadioButton("白子");
36.  bz=new JRadioButton("黑子",true);
37.  ButtonGroup  group=new ButtonGroup();
38.  group.add(wz);
39.  group.add(bz);
40.  SouthJP.add(wz);
41.  SouthJP.add(bz);
42.  JPanel  CenterJP=new JPanel();
43.  CenterJP.setLayout(null);
44.  CenterJP.setSize(500, 500);
45.  CenterJP.addMouseListener(this);
46.  f.add("Center",CenterJP);
47.  try
48.  {
49.  Thread.sleep(500);
50.  }
51.  catch(InterruptedException  e)
52.  {
53.  e.printStackTrace();
54.  }
55.  g=CenterJP.getGraphics();
56.  g.setColor(Color.BLUE);
57.  g.drawRect(x, y, rw, rw);
58.  for(int i=1;i<10;i++)
59.  {
60.  //绘制第i条竖直线
61.  g.drawLine(x+(i*w),y,x+(i*w),y+rw);
62.  //绘制第i条水平线
63.  g.drawLine(x,y+(i*w),x+rw,y+(i*w));
64.  }
65.  }
66.  public void mouseClicked(MouseEvent  e)
67.  {
68.  Point  pt=new Point(e.getX()-15,e.getY()-15);
69.  if(wz.isSelected())
70.  {
71.  ChessPieces  c1=wf.getChessPieces("w");
72.  c1.DownPieces(g,pt);
73.  }
74.  else if(bz.isSelected())
75.  {
76.  ChessPieces  c2=wf.getChessPieces("b");
77.  c2.DownPieces(g,pt);
78.  }
79.  }
80.  }
81.  //抽象享元角色：棋子
82.  interface ChessPieces
83.  {
84.  public void DownPieces(Graphics  g,Point  pt);    //下子
85.  }
86.  //具体享元角色：白子
87.  class  WhitePieces implements ChessPieces
88.  {
89.  public void DownPieces(Graphics  g,Point  pt)
90.  {
91.  g.setColor(Color.WHITE);
92.  g.fillOval(pt.x,pt.y,30,30);
93.  }
94.  }
95.  //具体享元角色：黑子
96.  class  BlackPieces implements ChessPieces
97.  {
98.  public void DownPieces(Graphics  g,Point  pt)
99.  {
100.  g.setColor(Color.BLACK);
101.  g.fillOval(pt.x,pt.y,30,30);
102.  }
103.  }
104.  //享元工厂角色
105.  class  WeiqiFactory
106.  {
107.  private ArrayList<ChessPieces>  qz;
108.  public WeiqiFactory()
109.  {
110.  qz=new ArrayList<ChessPieces>();
111.  ChessPieces  w=new WhitePieces();
112.  qz.add(w);
113.  ChessPieces  b=new BlackPieces();
114.  qz.add(b);
115.  }
116.  public ChessPieces  getChessPieces(String  type)
117.  {
118.  if(type.equalsIgnoreCase("w"))
119.  {
120.  return (ChessPieces)qz.get(0);
121.  }
122.  else if(type.equalsIgnoreCase("b"))
123.  {
124.  return (ChessPieces)qz.get(1);
125.  }
126.  else
127.  {
128.  return null;
129.  }
130.  }
131.  }

```
程序运行结果如图 3 所示。

![五子棋游戏的运行结果](https://upload-images.jianshu.io/upload_images/21440240-9f0c585f710e287e.gif?imageMogr2/auto-orient/strip)

图3 五子棋游戏的运行结果

## 享元模式的应用场景

前面分析了享元模式的结构与特点，下面分析它适用的应用场景。享元模式是通过减少内存中对象的数量来节省内存空间的，所以以下几种情形适合采用享元模式。

1.  系统中存在大量相同或相似的对象，这些对象耗费大量的内存资源。
2.  大部分的对象可以按照内部状态进行分组，且可将不同部分外部化，这样每一个组只需保存一个内部状态。
3.  由于享元模式需要额外维护一个保存享元的[数据结构](http://c.biancheng.net/data_structure/)，所以应当在有足够多的享元实例时才值得使用享元模式。

## 享元模式的扩展

在前面介绍的享元模式中，其结构图通常包含可以共享的部分和不可以共享的部分。在实际使用过程中，有时候会稍加改变，即存在两种特殊的享元模式：单纯享元模式和复合享元模式，下面分别对它们进行简单介绍。

(1) 单纯享元模式，这种享元模式中的所有的具体享元类都是可以共享的，不存在非共享的具体享元类，其结构图如图 4 所示。

![单纯享元模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-5fb0a5e56e39f0c2.gif?imageMogr2/auto-orient/strip)

图4 单纯享元模式的结构图

(2) 复合享元模式，这种享元模式中的有些享元对象是由一些单纯享元对象组合而成的，它们就是复合享元对象。虽然复合享元对象本身不能共享，但它们可以分解成单纯享元对象再被共享，其结构图如图 5 所示。

![复合享元模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-39f83672c9650d2f.gif?imageMogr2/auto-orient/strip)

图5 复合享元模式的结构图
