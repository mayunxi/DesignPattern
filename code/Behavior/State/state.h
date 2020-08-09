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
