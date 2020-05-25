#include <iostream>

using namespace std;

class Memory{
  public:
   virtual void addMemory() = 0;
};

class Memory6G:public Memory{
  public:
    void addMemory()
    {
        cout << "phone use 6G memory" << endl;
    }
};
class Memory8G:public Memory{
  public:
    void addMemory()
    {
        cout << "phone use 8G memory" << endl;
    }
};

class Phone{
  public:
    Memory *phoneMemory;
    void setMemory(Memory *memory)
    {
        this->phoneMemory = memory;
    }
    virtual void buyPhone() = 0;
};
class HuaWei:public Phone
{
  public:
    void buyPhone()
    {
        phoneMemory->addMemory();
        cout << "buy Huawei Phone" << endl;
    }
};

class XiaoMi:public Phone
{
  public:
    void buyPhone()
    {
        phoneMemory->addMemory();
        cout << "buy XiaoMi Phone" << endl;
    }
};

int main()
{
    Phone *huawei = new HuaWei();
    huawei->setMemory(new Memory8G);
    huawei->buyPhone();

    Phone *xiaomi = new XiaoMi();
    xiaomi->setMemory(new Memory6G);
    xiaomi->buyPhone();
}
