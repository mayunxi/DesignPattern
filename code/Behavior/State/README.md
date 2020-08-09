# 状态模式（详解版）


在软件开发过程中，应用程序中的有些对象可能会根据不同的情况做出不同的行为，我们把这种对象称为有状态的对象，而把影响对象行为的一个或多个动态变化的属性称为状态。当有状态的对象与外部事件产生互动时，其内部状态会发生改变，从而使得其行为也随之发生改变。如人的情绪有高兴的时候和伤心的时候，不同的情绪有不同的行为，当然外界也会影响其情绪变化。

对这种有状态的对象编程，传统的解决方案是：将这些所有可能发生的情况全都考虑到，然后使用 if-else 语句来做状态判断，再进行不同情况的处理。但当对象的状态很多时，程序会变得很复杂。而且增加新的状态要添加新的 if-else 语句，这违背了“开闭原则”，不利于程序的扩展。

以上问题如果采用“状态模式”就能很好地得到解决。状态模式的解决思想是：当控制一个对象状态转换的条件表达式过于复杂时，把相关“判断逻辑”提取出来，放到一系列的状态类当中，这样可以把原来复杂的逻辑判断简单化。

## 状态模式的定义与特点

状态（State）模式的定义：对有状态的对象，把复杂的“判断逻辑”提取到不同的状态对象中，允许状态对象在其内部状态发生改变时改变其行为。

状态模式是一种对象行为型模式，其主要优点如下。

1.  状态模式将与特定状态相关的行为局部化到一个状态中，并且将不同状态的行为分割开来，满足“单一职责原则”。
2.  减少对象间的相互依赖。将不同的状态引入独立的对象中会使得状态转换变得更加明确，且减少对象间的相互依赖。
3.  有利于程序的扩展。通过定义新的子类很容易地增加新的状态和转换。

状态模式的主要缺点如下。

1.  状态模式的使用必然会增加系统的类与对象的个数。
2.  状态模式的结构与实现都较为复杂，如果使用不当会导致程序结构和代码的混乱。

## 状态模式的结构与实现

状态模式把受环境改变的对象行为包装在不同的状态对象里，其意图是让一个对象在其内部状态改变的时候，其行为也随之改变。现在我们来分析其基本结构和实现方法。

#### 1\. 模式的结构

状态模式包含以下主要角色。

1.  环境（Context）角色：也称为上下文，它定义了客户感兴趣的接口，维护一个当前状态，并将与状态相关的操作委托给当前状态对象来处理。
2.  抽象状态（State）角色：定义一个接口，用以封装环境对象中的特定状态所对应的行为。
3.  具体状态（Concrete    State）角色：实现抽象状态所对应的行为。

其结构图如图 1 所示。

![状态模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-16790df84f960ac9.gif?imageMogr2/auto-orient/strip)

图1 状态模式的结构图

#### 2\. 模式的实现

状态模式的实现代码如下：

state.h
```
#ifndef STATE_H
#define STATE_H
#include "context.h"
//抽象状态类
class State
{
public:
    virtual void Handle(Context *context) = 0;
};
//具体状态A类
class ConcreteStateA:public State
{
public:
    void Handle(Context *context);
};
//具体状态B类
class ConcreteStateB:public State
{
public:
    void Handle(Context *context);
};

#endif // STATE_H

```
state.cpp
```
#include "state.h"
#include "stdio.h"

void ConcreteStateA::Handle(Context *context)
{
    printf("当前状态是 A.\n");
    context->setState(new ConcreteStateB());
}

void ConcreteStateB::Handle(Context *context)
{
    printf("当前状态是 B.\n");
    context->setState(new ConcreteStateA());
}

```
context.h
```
#ifndef CONTEXT_H
#define CONTEXT_H

class State;

//环境类
class Context
{
private:
    State *state;
    //定义环境类的初始状态
public :
    Context();
    //设置新状态
    void setState(State *state);
    //读取状态
    State *getState();
    //对请求做处理
    void Handle();
};

#endif // CONTEXT_H

```
context.cpp
```
#include "context.h"
#include "state.h"

Context::Context()
{
    this->state=new ConcreteStateA();
}

void Context::setState(State *state)
{
    delete(this->state);
    this->state=state;
}

State *Context::getState()
{
    return(state);
}

void Context::Handle()
{
    state->Handle(this);
}
int main()
{
    Context *context=new Context();    //创建环境
    context->Handle();    //处理请求
    context->Handle();
    context->Handle();
    context->Handle();

    return 0;
}


```

程序运行结果如下：

```
当前状态是 A.
当前状态是 B.
当前状态是 A.
当前状态是 B.
```

## 状态模式的应用实例

【例1】用“状态模式”设计一个学生成绩的状态转换程序。

分析：本实例包含了“不及格”“中等”和“优秀” 3 种状态，当学生的分数小于 60 分时为“不及格”状态，当分数大于等于 60 分且小于 90 分时为“中等”状态，当分数大于等于 90 分时为“优秀”状态，我们用状态模式来实现这个程序。

首先，定义一个抽象状态类（AbstractState），其中包含了环境属性、状态名属性和当前分数属性，以及加减分方法 addScore(intx) 和检查当前状态的抽象方法 checkState()；然后，定义“不及格”状态类 LowState、“中等”状态类 MiddleState 和“优秀”状态类 HighState，它们是具体状态类，实现 checkState() 方法，负责检査自己的状态，并根据情况转换；最后，定义环境类（ScoreContext），其中包含了当前状态对象和加减分的方法 add(int score)，客户类通过该方法来改变成绩状态。图 2 所示是其结构图。

![学生成绩的状态转换程序的结构图](https://upload-images.jianshu.io/upload_images/21440240-b03bf57a9ef338a4.gif?imageMogr2/auto-orient/strip)

图2 学生成绩的状态转换程序的结构图

程序代码如下：

```
1.  package  state;
2.  public class  ScoreStateTest
3.  {
4.  public static void main(String[] args)
5.  {
6.  ScoreContext  account=new ScoreContext();
7.  System.out.println("学生成绩状态测试：");
8.  account.add(30);
9.  account.add(40);
10.  account.add(25);
11.  account.add(-15);
12.  account.add(-25);
13.  }
14.  }
15.  //环境类
16.  class  ScoreContext
17.  {
18.  private AbstractState  state;
19.  ScoreContext()
20.  {
21.  state=new LowState(this);
22.  }
23.  public void setState(AbstractState  state)
24.  {
25.  this.state=state;
26.  }
27.  public AbstractState  getState()
28.  {
29.  return state;
30.  }
31.  public void add(int score)
32.  {
33.  state.addScore(score);
34.  }
35.  }
36.  //抽象状态类
37.  abstract class  AbstractState
38.  {
39.  protected ScoreContext  hj;  //环境
40.  protected String  stateName; //状态名
41.  protected int score; //分数
42.  public abstract void checkState(); //检查当前状态
43.  public void addScore(int x)
44.  {
45.  score+=x;
46.  System.out.print("加上："+x+"分，\t当前分数："+score );
47.  checkState();
48.  System.out.println("分，\t当前状态："+hj.getState().stateName);
49.  }
50.  }
51.  //具体状态类：不及格
52.  class  LowState extends AbstractState
53.  {
54.  public LowState(ScoreContext  h)
55.  {
56.  hj=h;
57.  stateName="不及格";
58.  score=0;
59.  }
60.  public LowState(AbstractState  state)
61.  {
62.  hj=state.hj;
63.  stateName="不及格";
64.  score=state.score;
65.  }
66.  public void checkState()
67.  {
68.  if(score>=90)
69.  {
70.  hj.setState(new HighState(this));
71.  }
72.  else if(score>=60)
73.  {
74.  hj.setState(new MiddleState(this));
75.  }
76.  }
77.  }
78.  //具体状态类：中等
79.  class  MiddleState extends AbstractState
80.  {
81.  public MiddleState(AbstractState  state)
82.  {
83.  hj=state.hj;
84.  stateName="中等";
85.  score=state.score;
86.  }
87.  public void checkState()
88.  {
89.  if(score<60)
90.  {
91.  hj.setState(new LowState(this));
92.  }
93.  else if(score>=90)
94.  {
95.  hj.setState(new HighState(this));
96.  }
97.  }
98.  }
99.  //具体状态类：优秀
100.  class  HighState extends AbstractState
101.  {
102.  public HighState(AbstractState  state)
103.  {
104.  hj=state.hj;
105.  stateName="优秀";
106.  score=state.score;
107.  }
108.  public void checkState()
109.  {
110.  if(score<60)
111.  {
112.  hj.setState(new LowState(this));
113.  }
114.  else if(score<90)
115.  {
116.  hj.setState(new MiddleState(this));
117.  }
118.  }
119.  }

```
程序运行结果如下：

```
学生成绩状态测试：
加上：30分，    当前分数：30分，    当前状态：不及格
加上：40分，    当前分数：70分，    当前状态：中等
加上：25分，    当前分数：95分，    当前状态：优秀
加上：-15分，    当前分数：80分，    当前状态：中等
加上：-25分，    当前分数：55分，    当前状态：不及格
```

【例2】用“状态模式”设计一个多线程的状态转换程序。

分析：多线程存在 5 种状态，分别为新建状态、就绪状态、运行状态、阻塞状态和死亡状态，各个状态当遇到相关方法调用或事件触发时会转换到其他状态，其状态转换规律如图 3 所示。

![线程状态转换图](https://upload-images.jianshu.io/upload_images/21440240-036681e48e20c2d3.gif?imageMogr2/auto-orient/strip)

图3 线程状态转换图

现在先定义一个抽象状态类（TheadState），然后为图 3 所示的每个状态设计一个具体状态类，它们是新建状态（New）、就绪状态（Runnable ）、运行状态（Running）、阻塞状态（Blocked）和死亡状态（Dead），每个状态中有触发它们转变状态的方法，环境类（ThreadContext）中先生成一个初始状态（New），并提供相关触发方法，图 4 所示是线程状态转换程序的结构图。

![线程状态转换程序的结构图](https://upload-images.jianshu.io/upload_images/21440240-2583797a25874e51.gif?imageMogr2/auto-orient/strip)

图4 线程状态转换程序的结构图

程序代码如下：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  package  state;
2.  public class  ThreadStateTest
3.  {
4.  public static void main(String[] args)
5.  {
6.  ThreadContext  context=new ThreadContext();
7.  context.start();
8.  context.getCPU();
9.  context.suspend();
10.  context.resume();
11.  context.getCPU();
12.  context.stop();
13.  }
14.  }
15.  //环境类
16.  class  ThreadContext
17.  {
18.  private ThreadState  state;
19.  ThreadContext()
20.  {
21.  state=new New();
22.  }
23.  public void setState(ThreadState  state)
24.  {
25.  this.state=state;
26.  }
27.  public ThreadState  getState()
28.  {
29.  return state;
30.  }
31.  public void start()
32.  {
33.  ((New) state).start(this);
34.  }
35.  public void getCPU()
36.  {
37.  ((Runnable) state).getCPU(this);
38.  }
39.  public void suspend()
40.  {
41.  ((Running) state).suspend(this);
42.  }
43.  public void stop()
44.  {
45.  ((Running) state).stop(this);
46.  }
47.  public void resume()
48.  {
49.  ((Blocked) state).resume(this);
50.  }
51.  }
52.  //抽象状态类：线程状态
53.  abstract class  ThreadState
54.  {
55.  protected String  stateName; //状态名
56.  }
57.  //具体状态类：新建状态
58.  class  New extends ThreadState
59.  {
60.  public New()
61.  {
62.  stateName="新建状态";
63.  System.out.println("当前线程处于：新建状态.");
64.  }
65.  public void start(ThreadContext  hj)
66.  {
67.  System.out.print("调用start()方法-->");
68.  if(stateName.equals("新建状态"))
69.  {
70.  hj.setState(new Runnable());
71.  }
72.  else
73.  {
74.  System.out.println("当前线程不是新建状态，不能调用start()方法.");
75.  }
76.  }
77.  }
78.  //具体状态类：就绪状态
79.  class  Runnable extends ThreadState
80.  {
81.  public Runnable()
82.  {
83.  stateName="就绪状态";
84.  System.out.println("当前线程处于：就绪状态.");
85.  }
86.  public void getCPU(ThreadContext  hj)
87.  {
88.  System.out.print("获得CPU时间-->");
89.  if(stateName.equals("就绪状态"))
90.  {
91.  hj.setState(new Running());
92.  }
93.  else
94.  {
95.  System.out.println("当前线程不是就绪状态，不能获取CPU.");
96.  }
97.  }
98.  }
99.  //具体状态类：运行状态
100.  class  Running extends ThreadState
101.  {
102.  public Running()
103.  {
104.  stateName="运行状态";
105.  System.out.println("当前线程处于：运行状态.");
106.  }
107.  public void suspend(ThreadContext  hj)
108.  {
109.  System.out.print("调用suspend()方法-->");
110.  if(stateName.equals("运行状态"))
111.  {
112.  hj.setState(new Blocked());
113.  }
114.  else
115.  {
116.  System.out.println("当前线程不是运行状态，不能调用suspend()方法.");
117.  }
118.  }
119.  public void stop(ThreadContext  hj)
120.  {
121.  System.out.print("调用stop()方法-->");
122.  if(stateName.equals("运行状态"))
123.  {
124.  hj.setState(new Dead());
125.  }
126.  else
127.  {
128.  System.out.println("当前线程不是运行状态，不能调用stop()方法.");
129.  }
130.  }
131.  }
132.  //具体状态类：阻塞状态
133.  class  Blocked extends ThreadState
134.  {
135.  public Blocked()
136.  {
137.  stateName="阻塞状态";
138.  System.out.println("当前线程处于：阻塞状态.");
139.  }
140.  public void resume(ThreadContext  hj)
141.  {
142.  System.out.print("调用resume()方法-->");
143.  if(stateName.equals("阻塞状态"))
144.  {
145.  hj.setState(new Runnable());
146.  }
147.  else
148.  {
149.  System.out.println("当前线程不是阻塞状态，不能调用resume()方法.");
150.  }
151.  }
152.  }
153.  //具体状态类：死亡状态
154.  class  Dead extends ThreadState
155.  {
156.  public Dead()
157.  {
158.  stateName="死亡状态";
159.  System.out.println("当前线程处于：死亡状态.");
160.  }
161.  }

</pre>

程序运行结果如下：

<pre class="info-box">当前线程处于：新建状态.
调用start()方法-->当前线程处于：就绪状态.
获得CPU时间-->当前线程处于：运行状态.
调用suspend()方法-->当前线程处于：阻塞状态.
调用resume()方法-->当前线程处于：就绪状态.
获得CPU时间-->当前线程处于：运行状态.
调用stop()方法-->当前线程处于：死亡状态.</pre>

## 状态模式的应用场景

通常在以下情况下可以考虑使用状态模式。

*   当一个对象的行为取决于它的状态，并且它必须在运行时根据状态改变它的行为时，就可以考虑使用状态模式。
*   一个操作中含有庞大的分支结构，并且这些分支决定于对象的状态时。

## 状态模式的扩展

在有些情况下，可能有多个环境对象需要共享一组状态，这时需要引入享元模式，将这些具体状态对象放在集合中供程序共享，其结构图如图 5 所示。

![共享状态模式的结构图](https://upload-images.jianshu.io/upload_images/21440240-b81b3ba8f5ce6a8c.gif?imageMogr2/auto-orient/strip)

图5 共享状态模式的结构图

分析：共享状态模式的不同之处是在环境类中增加了一个 HashMap 来保存相关状态，当需要某种状态时可以从中获取，其程序代码如下：

<pre class="cpp sh_cpp snippet-formatted sh_sourceCode">

1.  package  state;
2.  import  java.util.HashMap;
3.  public class  FlyweightStatePattern
4.  {
5.  public static void main(String[] args)
6.  {
7.  ShareContext  context=new ShareContext(); //创建环境
8.  context.Handle(); //处理请求
9.  context.Handle();
10.  context.Handle();
11.  context.Handle();
12.  }
13.  }
14.  //环境类
15.  class  ShareContext
16.  {
17.  private ShareState  state;
18.  private HashMap<String, ShareState>  stateSet=new HashMap<String, ShareState>();
19.  public ShareContext()
20.  {
21.  state=new ConcreteState1();
22.  stateSet.put("1", state);
23.  state=new ConcreteState2();
24.  stateSet.put("2", state);
25.  state=getState("1");
26.  }
27.  //设置新状态
28.  public void setState(ShareState  state)
29.  {
30.  this.state=state;
31.  }
32.  //读取状态
33.  public ShareState  getState(String  key)
34.  {
35.  ShareState  s=(ShareState)stateSet.get(key);
36.  return s;
37.  }
38.  //对请求做处理
39.  public void Handle()
40.  {
41.  state.Handle(this);
42.  }
43.  }
44.  //抽象状态类
45.  abstract class  ShareState
46.  {
47.  public abstract void Handle(ShareContext  context);
48.  }
49.  //具体状态1类
50.  class  ConcreteState1 extends ShareState
51.  {
52.  public void Handle(ShareContext  context)
53.  {
54.  System.out.println("当前状态是： 状态1");
55.  context.setState(context.getState("2"));
56.  }
57.  }
58.  //具体状态2类
59.  class  ConcreteState2 extends ShareState
60.  {
61.  public void Handle(ShareContext  context)
62.  {
63.  System.out.println("当前状态是： 状态2");
64.  context.setState(context.getState("1"));
65.  }
66.  }

</pre>

程序运行结果如下：

<pre class="info-box">当前状态是： 状态1
当前状态是： 状态2
当前状态是： 状态1
当前状态是： 状态2</pre>
