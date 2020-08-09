#include<stdio.h>
#include<string>
#include<set>
#include<list>
#include<iostream>
#include<vector>
using namespace std;
/*文法规则
  <expression> ::= <city>的<person>
  <city> ::= 韶关|广州
  <person> ::= 老人|妇女|儿童
*/

//抽象表达式类
class Expression
{
public:
    virtual bool interpret(string info) = 0;
};
//终结符表达式类
class TerminalExpression:public Expression
{
private:
    std::set<string> info_set;
public:
    TerminalExpression(vector<string> data)
    {
        for(int i=0;i<data.size();i++)
            info_set.insert(data.at(i));
    }
    bool interpret(string info)
    {
        if(info_set.find(info) != info_set.end())
        {
            return true;
        }
        return false;
    }
};
//非终结符表达式类
class AndExpression:public Expression
{
private :
    Expression *city=NULL;
    Expression *person=NULL;
public:
    AndExpression(Expression *city,Expression *person)
    {
        this->city=city;
        this->person=person;
    }
    bool interpret(string info)
    {
        int pos = info.find("的");
        string city_str = info.substr(0,pos);
        int index = sizeof("的");
        string person_str = info.substr(pos+index-1);
        return city->interpret(city_str)&&person->interpret(person_str);
    }
};
//环境类
class Context
{
private:
    vector<string> citys={"韶关","广州"};
    vector<string>  persons={"老人","妇女","儿童"};
    Expression *cityPerson;
public:
    Context()
    {
        Expression *city=new TerminalExpression(citys);
        Expression *person=new TerminalExpression(persons);
        cityPerson=new AndExpression(city,person);
    }
    void freeRide(string info)
    {
        bool ok=cityPerson->interpret(info);
        if(ok)
            cout << ("您是"+info+"，您本次乘车免费！") << endl;
        else
            cout << (info+"，您不是免费人员，本次乘车扣费2元！") << endl;
    }
};

int main()
{
    Context *bus=new Context();
    bus->freeRide("韶关的老人");
    bus->freeRide("韶关的年轻人");
    bus->freeRide("广州的妇女");
    bus->freeRide("广州的儿童");
    bus->freeRide("山东的儿童");

    return 0;
}
