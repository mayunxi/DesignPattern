#ifndef STAFF_H
#define STAFF_H

#include <list>
#include <iostream>
#include "vistor.h"

using namespace std;
class Visitor;
// 员工基类
class Staff {

public :
    string name;
    int kpi;// 员工KPI

     Staff(string name);
    // 核心方法，接受Visitor的访问
   virtual void accept(Visitor *visitor) = 0;
};
// 工程师
class Engineer:public Staff {

public :
    Engineer(string name);

    //@Override
    void accept(Visitor *visitor);
    // 工程师一年的代码数量
    int getCodeLines();
};
// 经理
class Manager:public Staff {

public:
    Manager(string name);

    //@Override
    void accept(Visitor *visitor);
    // 一年做的产品数量
    int getProducts();
};

// 员工业务报表类
class BusinessReport {

private:
    list<Staff*> mStaffs;

public :
    BusinessReport();

    /**
     * 为访问者展示报表
     * @param visitor 公司高层，如CEO、CTO
     */
    void showReport(Visitor *visitor);
};
#endif // STAFF_H
