
#include<string>
#include<iostream>
using namespace std;
class IGamePlayer {
    //登陆
public:
    virtual void login(string user, string password) =0;
    //杀怪
    virtual void killBoss() = 0;
    //升级
    virtual void upgrade() = 0;
};
class GamePlayer:public IGamePlayer {

private:
    string name = "";

public:
    GamePlayer(string name) {
        this->name = name;
    }

    //@Override
public :
    void login(string user, string password) {
        cout << "登录名为<" + user + ">的用户<" + this->name + ">登陆成功！" << endl;
    }


   void killBoss() {
        cout << "<" + this->name + ">在打怪！" << endl;
    }


    void upgrade() {
        cout << "<" + this->name + ">升了一级！" << endl;
    }

};
class GamePlayerProxy:public IGamePlayer {

private:
    IGamePlayer *gamePlayer = NULL;

public:
    GamePlayerProxy(IGamePlayer *gamePlayer) {
        this->gamePlayer = gamePlayer;
    }

    //@Override
public :
    void login(string user, string password) {
        this->gamePlayer->login(user, password);
    }


    void killBoss() {
        this->gamePlayer->killBoss();
    }

    void upgrade() {
        this->gamePlayer->upgrade();
    }

};
int main()
{
    GamePlayer *player1 = new GamePlayer("player1");

    GamePlayerProxy *proxy = new GamePlayerProxy(player1);
    proxy->login("admin","123");
    proxy->killBoss();
    proxy->upgrade();
}
