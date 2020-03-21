#include <iostream>
#include <list>
using namespace std;
class ITeacherListener{
public:
    virtual void onTeacherComming(int value)=0;
};
class ZhangSan:public ITeacherListener
{
public:
    void onTeacherComming(int value){
        stopCopyWork(value);
    }
    void stopCopyWork(int value)
    {
        cout << "zhang san stopCopyWork " << value << endl;
    }
};
class Lisi:public ITeacherListener
{
public:
    void onTeacherComming(int value)
    {
        stopPlayGame(value);
    }
    void stopPlayGame(int value)
    {
        cout << "Li si stopPlayGame " << value << endl;
    }
};

class INotifier{
public:
    virtual void registerListener(ITeacherListener *l)=0;
    virtual void removeListener(ITeacherListener *l)=0;
    virtual void notify()=0;

};
class MonitorNotifier:public INotifier{
public:
    void registerListener(ITeacherListener *l){
        listenerList.push_back(l);
    }
    void removeListener(ITeacherListener *l)
    {
        listenerList.remove(l);
    }
    void setValue(int val)
    {
        value = val;
        notify();
    }
    void notify()
    {
        for (ITeacherListener *l:listenerList)
        {
            l->onTeacherComming(value);
        }
    }
private:
    list<ITeacherListener *> listenerList;
    int value; //=the msg need notify
};

int main(int argc, char *argv[])
{
    cout << "--------------------"<<endl;
    MonitorNotifier monitor;
    ZhangSan zs;
    Lisi ls;
    monitor.registerListener(&zs);
    monitor.registerListener(&ls);
    monitor.setValue(1);

    cout << "-----------------"<<endl;
    monitor.removeListener(&ls);
    monitor.setValue(2);

    return 0;
}
