#include <iostream>
using namespace std;
class Strategy
{
public:
    virtual int doOperation(int num1,int num2) = 0;
};

class OperationAdd:public Strategy
{
public:
    int doOperation(int num1,int num2)
    {
        return num1+num2;
    }
};
class OperationSub:public Strategy
{
public:
    int doOperation(int num1, int num2)
    {
        return num1 - num2;
    }
};
class OperationMul:public Strategy
{
public:
    int doOperation(int num1, int num2)
    {
        return num1 * num2;
    }
};
class Context
{
private:
    Strategy *strategy;
public:
    Context(Strategy *stra)
    {
        strategy = stra;
    }
    int executeStrategy(int num1,int num2)
    {
        return strategy->doOperation(num1,num2);
    }
};
int main()
{
    Context *context = new Context(new OperationAdd());
    cout << context->executeStrategy(1,2) << endl;
    context = new Context(new OperationSub());
    cout << context->executeStrategy(2,1) << endl;
    context = new Context(new OperationMul());
    cout << context->executeStrategy(2,1) << endl;
}
