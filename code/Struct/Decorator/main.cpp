#include<stdio.h>
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
