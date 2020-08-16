在软件开发系统中，常常出现“方法的请求者”与“方法的实现者”之间存在紧密的耦合关系。这不利于软件功能的扩展与维护。例如，想对行为进行“撤销、重做、记录”等处理都很不方便，因此“如何将方法的请求者与方法的实现者解耦？”变得很重要，命令模式能很好地解决这个问题。

在现实生活中，这样的例子也很多，例如，电视机遥控器（命令发送者）通过按钮（具体命令）来遥控电视机（命令接收者），还有计算机键盘上的“功能键”等。

## 命令模式的定义与特点

命令（Command）模式的定义如下：将一个请求封装为一个对象，使发出请求的责任和执行请求的责任分割开。这样两者之间通过命令对象进行沟通，这样方便将命令对象进行储存、传递、调用、增加与管理。

命令模式的主要优点如下。

1.  降低系统的耦合度。命令模式能将调用操作的对象与实现该操作的对象解耦。
2.  增加或删除命令非常方便。采用命令模式增加与删除命令不会影响其他类，它满足“开闭原则”，对扩展比较灵活。
3.  可以实现宏命令。命令模式可以与[组合模式](http://c.biancheng.net/view/1373.html)结合，将多个命令装配成一个组合命令，即宏命令。
4.  方便实现 Undo 和 Redo 操作。命令模式可以与后面介绍的[备忘录模式](http://c.biancheng.net/view/1400.html)结合，实现命令的撤销与恢复。

其缺点是：可能产生大量具体命令类。因为计对每一个具体操作都需要设计一个具体命令类，这将增加系统的复杂性。

## 命令模式的结构与实现

可以将系统中的相关操作抽象成命令，使调用者与实现者相关分离，其结构如下。

#### 1\. 模式的结构

命令模式包含以下主要角色。

1.  抽象命令类（Command）角色：声明执行命令的接口，拥有执行命令的抽象方法 execute()。
2.  具体命令角色（Concrete    Command）角色：是抽象命令类的具体实现类，它拥有接收者对象，并通过调用接收者的功能来完成命令要执行的操作。
3.  实现者/接收者（Receiver）角色：执行命令功能的相关操作，是具体命令对象业务的真正实现者。
4.  调用者/请求者（Invoker）角色：是请求的发送者，它通常拥有很多的命令对象，并通过访问命令对象来执行相关请求，它不直接访问接收者。

其结构图如图 1 所示。

![命令模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-07148fb8290b6053.gif?imageMogr2/auto-orient/strip)

图1 命令模式的结构图

#### 2\. 模式的实现

命令模式的代码如下：

```
#include<stdio.h>

//接收者
class Receiver
{
public :
    void action()
    {
      printf("接收者的action()方法被调用...\n");
    }
};
//抽象命令
class Command
{
    public :
    virtual void execute() = 0;
};
//具体命令
class ConcreteCommand:public Command
{
private:
    Receiver *receiver;

public:
    ConcreteCommand()
    {
        receiver=new Receiver();
    }
    void execute()
    {
        receiver->action();
    }
};

//调用者
class Invoker
{
private :
    Command *command;
public:
    Invoker(Command *cmd)
    {
        this->command=cmd;
    }
    void setCommand(Command *cmd)
    {
        this->command=cmd;
    }
    void call()
    {
        printf("调用者执行命令command...\n");
        command->execute();
    }
};
int main()
{
    Command *cmd=new ConcreteCommand();
    Invoker *ir=new Invoker(cmd);
    printf("客户访问调用者的call()方法...\n");
    ir->call();
    return 0;
}

```
程序的运行结果如下：

```
客户访问调用者的call()方法...
调用者执行命令command...
接收者的action()方法被调用...
```

## 命令模式的应用实例

【例1】用命令模式实现客户去餐馆吃早餐的实例。

分析：客户去餐馆可选择的早餐有肠粉、河粉和馄饨等，客户可向服务员选择以上早餐中的若干种，服务员将客户的请求交给相关的厨师去做。这里的点早餐相当于“命令”，服务员相当于“调用者”，厨师相当于“接收者”，所以用命令模式实现比较合适。

首先，定义一个早餐类（Breakfast），它是抽象命令类，有抽象方法 cooking()，说明要做什么；再定义其子类肠粉类（ChangFen）、馄饨类（HunTun）和河粉类（HeFen），它们是具体命令类，实现早餐类的 cooking() 方法，但它们不会具体做，而是交给具体的厨师去做；具体厨师类有肠粉厨师（ChangFenChef）、馄蚀厨师（HunTunChef）和河粉厨师（HeFenChef），他们是命令的接收者，由于本实例要显示厨师做菜的效果图（[点此下载要显示的效果图](http://c.biancheng.net/uploads/soft/181113/3-1Q116125200.zip)），所以把每个厨师类定义为 JFrame 的子类；最后，定义服务员类（Waiter），它接收客户的做菜请求，并发出做菜的命令。客户类是通过服务员类来点菜的，图 2 所示是其结构图。

![客户在餐馆吃早餐的结构图](https://upload-images.jianshu.io/upload_images/21440240-2f8536cf4cd2bf02.gif?imageMogr2/auto-orient/strip)

图2 客户在餐馆吃早餐的结构图

程序代码如下：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  package  command;
2.  import  javax.swing.*;
3.  public class  CookingCommand
4.  {
5.  public static void main(String[] args)
6.  {
7.  Breakfast  food1=new ChangFen();
8.  Breakfast  food2=new HunTun();
9.  Breakfast  food3=new HeFen();
10.  Waiter  fwy=new Waiter();
11.  fwy.setChangFen(food1);//设置肠粉菜单
12.  fwy.setHunTun(food2);  //设置河粉菜单
13.  fwy.setHeFen(food3);   //设置馄饨菜单
14.  fwy.chooseChangFen();  //选择肠粉
15.  fwy.chooseHeFen();     //选择河粉
16.  fwy.chooseHunTun();    //选择馄饨
17.  }
18.  }
19.  //调用者：服务员
20.  class  Waiter
21.  {
22.  private Breakfast  changFen,hunTun,heFen;
23.  public void setChangFen(Breakfast  f)
24.  {
25.  changFen=f;
26.  }
27.  public void setHunTun(Breakfast  f)
28.  {
29.  hunTun=f;
30.  }
31.  public void setHeFen(Breakfast  f)
32.  {
33.  heFen=f;
34.  }
35.  public void chooseChangFen()
36.  {
37.  changFen.cooking();
38.  }
39.  public void chooseHunTun()
40.  {
41.  hunTun.cooking();
42.  }
43.  public void chooseHeFen()
44.  {
45.  heFen.cooking();
46.  }
47.  }
48.  //抽象命令：早餐
49.  interface Breakfast
50.  {
51.  public abstract void cooking();
52.  }
53.  //具体命令：肠粉
54.  class  ChangFen implements Breakfast
55.  {
56.  private ChangFenChef  receiver;
57.  ChangFen()
58.  {
59.  receiver=new ChangFenChef();
60.  }
61.  public void cooking()
62.  {
63.  receiver.cooking();
64.  }
65.  }
66.  //具体命令：馄饨
67.  class  HunTun implements Breakfast
68.  {
69.  private HunTunChef  receiver;
70.  HunTun()
71.  {
72.  receiver=new HunTunChef();
73.  }
74.  public void cooking()
75.  {
76.  receiver.cooking();
77.  }
78.  }
79.  //具体命令：河粉
80.  class  HeFen implements Breakfast
81.  {
82.  private HeFenChef  receiver;
83.  HeFen()
84.  {
85.  receiver=new HeFenChef();
86.  }
87.  public void cooking()
88.  {
89.  receiver.cooking();
90.  }
91.  }
92.  //接收者：肠粉厨师
93.  class  ChangFenChef extends JFrame
94.  {
95.  private static final long serialVersionUID = 1L;
96.  JLabel  l=new JLabel();
97.  ChangFenChef()
98.  {
99.  super("煮肠粉");
100.  l.setIcon(new ImageIcon("src/command/ChangFen.jpg"));
101.  this.add(l);
102.  this.setLocation(30, 30);
103.  this.pack();
104.  this.setResizable(false);
105.  this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
106.  }
107.  public void cooking()
108.  {
109.  this.setVisible(true);
110.  }
111.  }
112.  //接收者：馄饨厨师
113.  class  HunTunChef extends JFrame
114.  {
115.  private static final long serialVersionUID=1L;
116.  JLabel  l=new JLabel();
117.  HunTunChef()
118.  {
119.  super("煮馄饨");
120.  l.setIcon(new ImageIcon("src/command/HunTun.jpg"));
121.  this.add(l);
122.  this.setLocation(350, 50);
123.  this.pack();
124.  this.setResizable(false);
125.  this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
126.  }
127.  public void cooking()
128.  {
129.  this.setVisible(true);
130.  }
131.  }
132.  //接收者：河粉厨师
133.  class  HeFenChef extends JFrame
134.  {
135.  private static final long serialVersionUID=1L;
136.  JLabel  l=new JLabel();
137.  HeFenChef()
138.  {
139.  super("煮河粉");
140.  l.setIcon(new ImageIcon("src/command/HeFen.jpg"));
141.  this.add(l);
142.  this.setLocation(200, 280);
143.  this.pack();
144.  this.setResizable(false);
145.  this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
146.  }
147.  public void cooking()
148.  {
149.  this.setVisible(true);
150.  }
151.  }

</pre>

程序的运行结果如图 2 所示。

![客户在餐馆吃早餐的运行结果](https://upload-images.jianshu.io/upload_images/21440240-2deefab595ded554.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

图2 客户在餐馆吃早餐的运行结果

## 命令模式的应用场景

命令模式通常适用于以下场景。

1.  当系统需要将请求调用者与请求接收者解耦时，命令模式使得调用者和接收者不直接交互。
2.  当系统需要随机请求命令或经常增加或删除命令时，命令模式比较方便实现这些功能。
3.  当系统需要执行一组操作时，命令模式可以定义宏命令来实现该功能。
4.  当系统需要支持命令的撤销（Undo）操作和恢复（Redo）操作时，可以将命令对象存储起来，采用备忘录模式来实现。

## 命令模式的扩展

在软件开发中，有时将命令模式与前面学的组合模式联合使用，这就构成了宏命令模式，也叫组合命令模式。宏命令包含了一组命令，它充当了具体命令与调用者的双重角色，执行它时将递归调用它所包含的所有命令，其具体结构图如图 3 所示。

![组合命令模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-5c0a4ecc9af9cddb.gif?imageMogr2/auto-orient/strip)

图3 组合命令模式的结构图

程序代码如下：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  package  command;
2.  import  java.util.ArrayList;
3.  public class  CompositeCommandPattern
4.  {
5.  public static void main(String[] args)
6.  {
7.  AbstractCommand  cmd1=new ConcreteCommand1();
8.  AbstractCommand  cmd2=new ConcreteCommand2();
9.  CompositeInvoker  ir=new CompositeInvoker();
10.  ir.add(cmd1);
11.  ir.add(cmd2);
12.  System.out.println("客户访问调用者的execute()方法...");
13.  ir.execute();
14.  }
15.  }
16.  //抽象命令
17.  interface AbstractCommand
18.  {
19.  public abstract void execute();
20.  }
21.  //树叶构件: 具体命令1
22.  class  ConcreteCommand1 implements AbstractCommand
23.  {
24.  private CompositeReceiver  receiver;
25.  ConcreteCommand1()
26.  {
27.  receiver=new CompositeReceiver();
28.  }
29.  public void execute()
30.  {
31.  receiver.action1();
32.  }
33.  }
34.  //树叶构件: 具体命令2
35.  class  ConcreteCommand2 implements AbstractCommand
36.  {
37.  private CompositeReceiver  receiver;
38.  ConcreteCommand2()
39.  {
40.  receiver=new CompositeReceiver();
41.  }
42.  public void execute()
43.  {
44.  receiver.action2();
45.  }
46.  }
47.  //树枝构件: 调用者
48.  class  CompositeInvoker implements AbstractCommand
49.  {
50.  private ArrayList<AbstractCommand>  children = new ArrayList<AbstractCommand>();
51.  public void add(AbstractCommand  c)
52.  {
53.  children.add(c);
54.  }
55.  public void remove(AbstractCommand  c)
56.  {
57.  children.remove(c);
58.  }
59.  public AbstractCommand  getChild(int i)
60.  {
61.  return children.get(i);
62.  }
63.  public void execute()
64.  {
65.  for(Object  obj:children)
66.  {
67.  ((AbstractCommand)obj).execute();
68.  }
69.  }
70.  }
71.  //接收者
72.  class  CompositeReceiver
73.  {
74.  public void action1()
75.  {
76.  System.out.println("接收者的action1()方法被调用...");
77.  }
78.  public void action2()
79.  {
80.  System.out.println("接收者的action2()方法被调用...");
81.  }
82.  }

</pre>

程序的运行结果如下：

<pre class="info-box">客户访问调用者的execute()方法...
接收者的action1()方法被调用...
接收者的action2()方法被调用...</pre>

当然，命令模式还可以同备忘录（Memento）模式组合使用，这样就变成了可撤销的命令模式，这将在后面介绍。
