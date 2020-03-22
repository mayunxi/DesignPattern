
#include <iostream>
using namespace std;
//Phone类：手机标准规范类(AbstractProduct)
class phone{
public:

    virtual void make()=0;
};

class MiPhone:public phone
{
public:
    MiPhone()
    {
        this->make();
    }

    void make()
    {
        cout << "make a miphone!" << endl;
    }
};
class IPhone:public phone{
public:
    IPhone()
    {
        this->make();
    }
    void make()
    {
        cout << "make a Applephone!" << endl;
    }
};
class AbstractFactory
{
public:
    virtual phone makePhone()=0;
};

class XiaoMIFactory:public AbstractFactory
{
public:
    phone *makePhone(){
            return new MiPhone();
    }
};
class AppleFactory:public phone
{
public:
    phone *makePhone(){
        return new IPhone();
    }
};

int main(int argc, char *argv[])
{
    XiaoMIFactory xiaomi;
    AppleFactory apple;


    phone *mi = xiaomi.makePhone();
    phone *apple=apple.makePhone();

    return 0;
}

