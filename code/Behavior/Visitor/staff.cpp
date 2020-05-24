#include "staff.h"


Staff::Staff(string name) {
    this->name = name;
    kpi = rand()%101;
}

Engineer::Engineer(string name):Staff(name)
{

}

void Engineer::accept(Visitor *visitor) {
    //visitor->visit(this); //
}

int Engineer::getCodeLines() {
    return rand()%10000;
}

Manager::Manager(string name):Staff(name){

}

void Manager::accept(Visitor *visitor) {
    visitor->visit(this);
}

int Manager::getProducts() {
    return rand()%11;
}

BusinessReport::BusinessReport() {
    mStaffs.push_back(new Manager("经理-A"));
    mStaffs.push_back(new Engineer("工程师-A"));
    mStaffs.push_back(new Engineer("工程师-B"));
    mStaffs.push_back(new Engineer("工程师-C"));
    mStaffs.push_back(new Manager("经理-B"));
    mStaffs.push_back(new Engineer("工程师-D"));
}

void BusinessReport::showReport(Visitor *visitor) {
    for (Staff *staff : mStaffs) {
        staff->accept(visitor);
    }
}
