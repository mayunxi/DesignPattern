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
