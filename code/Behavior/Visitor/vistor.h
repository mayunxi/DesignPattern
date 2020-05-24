#ifndef VISTOR_H
#define VISTOR_H

#include <list>
#include <iostream>
#include "staff.h"
class Engineer;
class Manager;
using namespace std;
class Visitor {

public:
    // 访问工程师类型
    virtual void visit(Engineer *engineer) = 0 ;

    // 访问经理类型
    virtual void visit(Manager *manager) = 0;
};

// CEO访问者
class CEOVisitor:public Visitor {
    //@Override
public:
    void visit(Engineer *engineer);

    //@Override
    void visit(Manager *manager);
};
class CTOVisitor:public  Visitor {
   // @Override
public :
    void visit(Engineer *engineer);

    //@Override
    void visit(Manager *manager);
};

#endif // VISTOR_H
