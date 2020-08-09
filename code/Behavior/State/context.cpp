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
