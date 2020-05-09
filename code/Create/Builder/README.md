

  >  "Separate the construction of a complex object from its representation so that the same construction process can create different representations."

  将复杂对象的构建与它的表示分离，以至于相同的构建过程可以创建不同的表示

又称生成器模式，属于对象创建型模式。

### 目的：

为了解决复杂对象的构建问题。将复杂对象构建步骤分解，并隔离复杂对象创建与使用（或许会想着似乎与工厂相似，但实际有区别的，参照下述理解）

### 简单理解：

对于该模式完整含义，可以通过工厂方法模式来理解，工厂方法模式关注的是单类产品多个不同种类的构建，即不同的具体工厂返回不同种类的产品。而建造者模式，则是关注单个复杂对象的构建，抽象建造者定义"设置产品各个部分或属性"的接口，而不同的具体建造者通过对相同接口有着不同的实现逻辑，达到对于同种产品有着不同的构建内容。而指挥者则负责安排这些各个部分或属性接口的调用次序，构建并返回对象给客户。
达到隔离复杂对象的创建和使用，使得相同创建过程可以创建不同产品（比如，面向抽象编程，再将具体Builder的选择配置到xml文件中获取）

若对象各部分（即那些设置属性的接口方法）构建顺序不重要，则完全可以把指挥者合并到建造者里面去，提供一个方法以固定顺序构建和返回对象。同理，若系统只需一个具体建造者的话，则也可以省略抽象建造者。

###在实际使用中：


```
#include <iostream>

using namespace std;
//1) 产品角色：包含多个组成部件的复杂对象。
class Product
{
private:
string partA;
string partB;
string partC;
public:
        void setPartA(string partA)
        {
            this->partA=partA;
        }
        void setPartB(string partB)
        {
            this->partB=partB;
        }
        void setPartC(string partC)
        {
            this->partC=partC;
        }
        void show()
        {
            cout << partA << partB << partC << endl;
            //显示产品的特性
        }
};
//(2) 抽象建造者：包含创建产品各个子部件的抽象方法。

class Builder
{
        //创建产品对象
protected:
    Product *product=new Product();
public:
     virtual void buildPartA()=0;
     virtual void buildPartB()=0;
     virtual void buildPartC()=0;
        //返回产品对象
     virtual Product* getResult()
     {
          return product;
     }
};

//(3) 具体建造者：实现了抽象建造者接口。
class ConcreteBuilder:public Builder
{
public:
    void buildPartA()
    {
        product->setPartA("建造 PartA");
    }
    void buildPartB()
    {
        product->setPartB("建造 PartB");
    }
    void buildPartC()
    {
        product->setPartC("建造 PartC");
    }
};


//(4) 指挥者：调用建造者中的方法完成复杂对象的创建。
class Director
{
private:
    Builder *builder;
public:
    Director(Builder *builder)
    {
        this->builder=builder;
    }
//产品构建与组装方法
public:
    Product *construct()
    {
        builder->buildPartA();
        builder->buildPartB();
        builder->buildPartC();
        return builder->getResult();
    }
};


int main()
{
    Builder *builder=new ConcreteBuilder();
    Director *director=new Director(builder);
    Product *product=director->construct();
    product->show();
}
```

### 模式结构


以下各角色具体含义，在上文“简单理解”中已提到，简单说一下

    Builder（抽象建造者）
    定义"设置产品各个部分或属性"的接口，且可以定义一个产品变量并初始化产品实例，还可以再定义一个返回产品的方法

    ConcreteBuilder（具体建造者）
    继承抽象建造者，不同的具体建造者根据自己业务需求实现上述接口

    Product（产品角色）
    复杂对象

    Director（指挥者）
    （若接口调用顺序不重要则可省略）由客户端创建，并由传入的具体建造者，根据一定顺序调用其“设置对象属性”的接口方法，来设置对象，最后返回对象。

### 优缺点

    将复杂产品的创建步骤分解在不同方法中，使得创建过程更加清晰，方便控制。
    在原完整定义建造者模式下，不同具体建造者间相互独立，若想增减时无须修改其他代码，符合开闭原则。

该模式适用于那些拥有复杂内部结构的产品，且在简化的情况下，也使得客户也更能清晰对对象的每一块进行设置。
