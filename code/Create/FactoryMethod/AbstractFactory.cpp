
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

class PC{
public:
    virtual void make()=0;
};
class MiPC:public PC
{
public:
    MiPC(){
        this->make();
    }
    void make()
    {
        cout << "make a MiPC!" << endl;
    }
};
class Mac:public PC{
public:
    Mac(){
        this->make();
    }
    void make()
    {
        cout << "make a Mac!" << endl;
    }
};
class AbstractFactory
{
public:
    virtual phone *makePhone()=0;
    virtual PC *makePC()=0;
};

class XiaoMIFactory:public AbstractFactory
{
public:
    phone *makePhone(){
            return new MiPhone();
    }
    PC *makePC(){
        return new MiPC();
    }
};
class AppleFactory:public AbstractFactory
{
public:
    phone *makePhone(){
        return new IPhone();
    }
    PC *makePC(){
        return new Mac();
    }
};



int main(int argc, char *argv[])
{
    XiaoMIFactory xiaomi;
    AppleFactory apple;


    phone *mi = xiaomi.makePhone();
    phone *app=apple.makePhone();

    xiaomi.makePC();
    apple.makePC();

    return 0;
}
