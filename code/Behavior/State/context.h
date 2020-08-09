#ifndef CONTEXT_H
#define CONTEXT_H

class State;

//环境类
class Context
{
private:
    State *state;
    //定义环境类的初始状态
public :
    Context();
    //设置新状态
    void setState(State *state);
    //读取状态
    State *getState();
    //对请求做处理
    void Handle();
};

#endif // CONTEXT_H
