#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<map>
using namespace std;


//抽象类
class AbstractClass
{
public:
    virtual void TemplateMethod() //模板方法
    {
        SpecificMethod();
        abstractMethod1();
        abstractMethod2();
    }
    void SpecificMethod() //具体方法
    {
        printf("抽象类中的具体方法被调用...\n");
    }
    virtual void abstractMethod1() = 0; //抽象方法1
    virtual void abstractMethod2() = 0; //抽象方法2
};
//具体子类
class ConcreteClass:public AbstractClass
{
public:
    void abstractMethod1()
    {
        printf("抽象方法1的实现被调用...\n");
    }

    void abstractMethod2()
    {
        printf("抽象方法2的实现被调用...\n");
    }
};



int  main()
{
    AbstractClass *tm=new ConcreteClass();
    tm->TemplateMethod();
    return 0;
}
