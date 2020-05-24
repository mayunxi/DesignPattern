#include "vistor.h"

void CEOVisitor::visit(Engineer *engineer) {
    cout << "工程师: "<< engineer->name<< ", KPI: "<< engineer->kpi << endl;
}

void CEOVisitor::visit(Manager *manager) {
    cout << "经理: " << manager->name << ", KPI: " << manager->kpi<<", 新产品数量: " << manager->getProducts() << endl;
}

void CTOVisitor::visit(Engineer *engineer) {
    cout << "工程师: "<< engineer->name<< ", 代码行数: "<< engineer->getCodeLines() << endl;
}

void CTOVisitor::visit(Manager *manager) {
    cout << "经理: "<< manager->name<< ", 产品数量: "<< manager->getProducts() << endl;
}
