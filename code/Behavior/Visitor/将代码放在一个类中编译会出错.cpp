/*年底，CEO和CTO开始评定员工一年的工作绩效，员工分为工程师和经理，
 * CTO关注工程师的代码量、经理的新产品数量；
 * CEO关注的是工程师的KPI和经理的KPI以及新产品数量。
由于CEO和CTO对于不同员工的关注点是不一样的，这就需要对不同员工类型进行不同的处理。访问者模式此时可以派上用场了。*/
#include <string>
#include <stdlib.h>
#include <list>
#include <iostream>
class Visitor;

using namespace std;
// 员工基类
class Staff {

public :
    string name;
    int kpi;// 员工KPI

     Staff(string name) {
        this->name = name;
        kpi = rand()%101;
    }
    // 核心方法，接受Visitor的访问
   virtual void accept(Visitor *visitor) = 0;
};
// 工程师
class Engineer:public Staff {

public :
    Engineer(string name):Staff(name)
    {

    }

    //@Override
    void accept(Visitor *visitor) {
        //visitor->visit(this); //
    }
    // 工程师一年的代码数量
    int getCodeLines() {
        return rand()%10000;
    }
};
// 经理
class Manager:public Staff {

public:
    Manager(string name):Staff(name){

    }

    //@Override
    void accept(Visitor *visitor) {
       visitor->visit(this);
    }
    // 一年做的产品数量
    int getProducts() {
        return rand()%11;
    }
};

// 员工业务报表类
class BusinessReport {

private:
    list<Staff*> mStaffs;

public :
    BusinessReport() {
        mStaffs.push_back(new Manager("经理-A"));
        mStaffs.push_back(new Engineer("工程师-A"));
        mStaffs.push_back(new Engineer("工程师-B"));
        mStaffs.push_back(new Engineer("工程师-C"));
        mStaffs.push_back(new Manager("经理-B"));
        mStaffs.push_back(new Engineer("工程师-D"));
    }

    /**
     * 为访问者展示报表
     * @param visitor 公司高层，如CEO、CTO
     */
    void showReport(Visitor *visitor) {
        for (Staff *staff : mStaffs) {
            staff->accept(visitor);
        }
    }
};

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
    void visit(Engineer *engineer) {
        cout << "工程师: "<< engineer->name<< ", KPI: "<< engineer->kpi << endl;
    }

    //@Override
    void visit(Manager *manager) {
        cout << "经理: " << manager->name << ", KPI: " << manager->kpi<<", 新产品数量: " << manager->getProducts() << endl;
    }
};
class CTOVisitor:public  Visitor {
   // @Override
public :
    void visit(Engineer *engineer) {
        cout << "工程师: "<< engineer->name<< ", 代码行数: "<< engineer->getCodeLines() << endl;
    }

    //@Override
    void visit(Manager *manager) {
        cout << "经理: "<< manager->name<< ", 产品数量: "<< manager->getProducts() << endl;
    }
};

int main()
{

    // 构建报表
    BusinessReport *report = new BusinessReport();
    cout << "=========== CEO看报表 ===========" << endl;
    report->showReport(new CEOVisitor());
    cout << ("=========== CTO看报表 ===========") << endl;
    report->showReport(new CTOVisitor());

}

