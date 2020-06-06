#include <iostream>
#include <list>

using namespace std;

class ContactPerson
{
public:
    ContactPerson(string Name,string MobileNumber):Name(Name),MobileNumber(MobileNumber)
    {}
    string getName()
    {
        return Name;
    }
    string getMobliNumber(void)
    {
        return MobileNumber;
    }
private:
    //姓名
    string Name;
    //电话号码
    string MobileNumber;
};
class ContactPersonMemento
{
    // 保存发起人创建的电话名单数据，就是所谓的状态
public :
    list<ContactPerson> ContactPersonListBack;

    ContactPersonMemento(list<ContactPerson> personList)
    {
        ContactPersonListBack = personList;
    }
};
//发起人--相当于【发起人角色】Originator
class MobileBackOriginator
{
    // 发起人需要保存的内部状态
public :
    list<ContactPerson> *_personList;


public:
    list<ContactPerson> *get()
    {
        return this->_personList;
    }


    void set(list<ContactPerson>* value)
    {
        this->_personList = value;
    }

    //初始化需要备份的电话名单
    MobileBackOriginator(list<ContactPerson> *_personList)
    {
        if (_personList != NULL)
        {
            this->_personList = _personList;
        }
        else
        {
           cout << "参数不能为空！" << endl;
        }
    }

    // 创建备忘录对象实例，将当期要保存的联系人列表保存到备忘录对象中
    ContactPersonMemento *CreateMemento()
    {
        return new ContactPersonMemento(*_personList);
    }

    // 将备忘录中的数据备份还原到联系人列表中
    void RestoreMemento(ContactPersonMemento *memento)
    {
        this->_personList = &memento->ContactPersonListBack;
    }
    void Show()
    {

        for ( list<ContactPerson>::iterator iter = _personList->begin();iter!=_personList->end();iter++)
        {
            cout << "姓名:" << iter->getName() << "; 号码:" <<  iter->getMobliNumber() << endl;
        }
    }
};

class MementoManager
{
    //如果想保存多个【备忘录】对象，可以通过字典或者堆栈来保存，堆栈对象可以反映保存对象的先后顺序
    //比如：public Dictionary<string, ContactPersonMemento> ContactPersonMementoDictionary { get; set; }
public:
    ContactPersonMemento *getMemento(void)
    {
        return Memento;
    }
    void setMemento(ContactPersonMemento *Memento)
    {
        this->Memento = Memento;
    }
private :
    ContactPersonMemento  *Memento;
};
int main()
{
    list<ContactPerson> persons;

    persons.push_back(ContactPerson("黄飞鸿","13533332222"));
    persons.push_back(ContactPerson("方世玉","13966554433"));
    persons.push_back(ContactPerson("洪熙官","13198765544"));

    //手机名单发起人
    MobileBackOriginator *mobileOriginator = new MobileBackOriginator(&persons);
    mobileOriginator->Show();

    // 创建备忘录并保存备忘录对象
    MementoManager *manager = new MementoManager();
    manager->setMemento(mobileOriginator->CreateMemento());

    // 更改发起人联系人列表
    printf("----移除最后一个联系人--------\n");
    mobileOriginator->_personList->pop_back();
    mobileOriginator->Show();

    // 恢复到原始状态
    printf("-------恢复联系人列表------\n");
    mobileOriginator->RestoreMemento(manager->getMemento());
    mobileOriginator->Show();
}
