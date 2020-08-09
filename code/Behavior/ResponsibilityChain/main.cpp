#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;

//抽象处理者角色
class Handler
{
private:
    Handler *next;
public:
    void setNext(Handler *next)
    {
        this->next=next;
    }
    Handler* getNext()
    {
        return next;
    }
    //处理请求的方法
    virtual void handleRequest(string request)=0;
};
//具体处理者角色1
class ConcreteHandler1:public Handler
{
public :
    void handleRequest(string request)
    {
        if(request == "one")
        {
            printf("具体处理者1负责处理该请求！\n");
        }
        else
        {
            if(getNext()!= nullptr)
            {
                getNext()->handleRequest(request);
            }
            else
            {
                printf("没有人处理该请求！\n");
            }
        }
    }
};
//具体处理者角色2
class ConcreteHandler2:public Handler
{
public :
    void handleRequest(string request)
    {
        if(request == "two")
        {
            printf("具体处理者2负责处理该请求！\n");
        }
        else
        {
            if(getNext()!=nullptr)
            {
                getNext()->handleRequest(request);
            }
            else
            {
                printf("没有人处理该请求！\n");
            }
        }
    }
};
int main()
{

    //组装责任链
    Handler *handler1=new ConcreteHandler1();
    Handler *handler2=new ConcreteHandler2();
    handler1->setNext(handler2);
    //提交请求
    handler1->handleRequest("two");
    return 0;

}
