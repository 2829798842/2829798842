#include <iostream>
#include <string>
using namespace std;

class Teacher {
private:
    string name; // 姓名
    string course; // 所教课程
public:
    Teacher() : name("unknow"), course("chinese") {} // 默认构造函数
    Teacher(string name_, string course_) : name(name_), course(course_) {} // 带参数的构造函数
    string getName() { return name; }
    string getCourse() { return course; }
};

class Class {
private:
    int grade; // 年级
    int classNo; // 班号
    Teacher headTeacher; // 班主任老师
public:
    Class() : grade(0), classNo(0), headTeacher() { // 默认构造函数
        cout << "new class created." << endl;
    }
    Class(int grade_, int classNo_, string teacherName = "unknow", string course = "chinese") 
        : grade(grade_), classNo(classNo_), headTeacher(teacherName, course) { // 带参数的构造函数
        cout << "grade:" << grade << " class no:" << classNo 
             << ",head teacher:" << headTeacher.getName() << "(" << headTeacher.getCourse() << ")" << endl;
    }
};

int main() {
    Class c1(2, 1, "ZhangXiaowen", "math");
    Class c2(3, 2, "LiSisi");
    Class c3(1, 1);
    Class c4;
    return 0;
}
