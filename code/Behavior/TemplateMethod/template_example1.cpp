#include <cstdio>
class AbstractClass {

public:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;

    void TemplateMethod() {
        PrimitiveOperation1();
        PrimitiveOperation2();
    }

};
class ConcreteClassA:public AbstractClass {

public:
    void PrimitiveOperation1() {
        printf("具体方法A方法1实现\n");
    }
    void PrimitiveOperation2() {
        printf("具体方法A方法2实现\n");
    }

};
class ConcreteClassB:public AbstractClass {

public:
    void PrimitiveOperation1() {
        printf("具体方法B方法1实现\n");
    }
    void PrimitiveOperation2() {
        printf("具体方法B方法2实现\n");
    }


};

int main()
{
    AbstractClass *abstractClass;

    abstractClass = new ConcreteClassA();
    abstractClass->TemplateMethod();

    abstractClass = new ConcreteClassB();
    abstractClass->TemplateMethod();
}
