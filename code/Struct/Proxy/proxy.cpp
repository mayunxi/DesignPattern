#include <cstdio>
class Subject
{
    virtual void request()=0;
};

class RealSubject:public Subject {

    //@Override
public:
void request() {
        printf("真实的请求RealSubject\n");
    }

};
class Proxy:public Subject {

private:
    RealSubject *realSubject = NULL;  //很像对象适配器模式

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
int main()
{
    Proxy *proxy = new Proxy();
    proxy->request();
}
