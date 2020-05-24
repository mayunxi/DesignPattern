/*年底，CEO和CTO开始评定员工一年的工作绩效，员工分为工程师和经理，
 * CTO关注工程师的代码量、经理的新产品数量；
 * CEO关注的是工程师的KPI和经理的KPI以及新产品数量。
由于CEO和CTO对于不同员工的关注点是不一样的，这就需要对不同员工类型进行不同的处理。访问者模式此时可以派上用场了。*/
#include <string>
#include <stdlib.h>
#include <list>
#include <iostream>
#include "staff.h"
#include "vistor.h"

using namespace std;




int main()
{

    // 构建报表
    BusinessReport *report = new BusinessReport();
    cout << "=========== CEO看报表 ===========" << endl;
    report->showReport(new CEOVisitor());
    cout << ("=========== CTO看报表 ===========") << endl;
    report->showReport(new CTOVisitor());

}
