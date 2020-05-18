#include<iostream>
#include <string>
using namespace std;
class TestPaper {

    //问题
public:
    void question1() {
        cout <<"1+1=?" << endl;
        cout <<"答案：" + answer1() << endl;
    }

    void question2() {
        cout <<"2+2=?" << endl;
        cout <<"答案：" + answer2() << endl;
    }

    void question3() {
        cout <<"3+3=?" <<endl;
        cout <<"答案：" + answer3() <<endl;
    }

    //答案
protected:
    virtual string answer1() = 0;

    virtual string answer2() = 0;

    virtual string answer3() = 0;
};
class TestPaperA:public TestPaper {

protected:
    string answer1() {
        return "2";
    }

    string answer2() {
        return "4";
    }

    string answer3() {
        return "6";
    }

};
class TestPaperB:public TestPaper {

protected:
    string answer1() {
        return "11";
    }

    string answer2() {
        return "22";
    }

    string answer3() {
        return "33";
    }

};

int main()
{
    cout <<"学生甲的试卷："<<endl;
    TestPaper *studentA = new TestPaperA();
    studentA->question1();
    studentA->question2();
    studentA->question3();

    //分隔符
    cout <<"------------------------------------------------" <<endl;

    cout <<"学生乙的试卷：" << endl;
    TestPaper *studentB = new TestPaperB();
    studentB->question1();
    studentB->question2();
    studentB->question3();
}
