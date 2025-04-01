#include <iostream>
#include <string>
using namespace std;

class Teacher {
private:
    string name; // ����
    string course; // ���̿γ�
public:
    Teacher() : name("unknow"), course("chinese") {} // Ĭ�Ϲ��캯��
    Teacher(string name_, string course_) : name(name_), course(course_) {} // �������Ĺ��캯��
    string getName() { return name; }
    string getCourse() { return course; }
};

class Class {
private:
    int grade; // �꼶
    int classNo; // ���
    Teacher headTeacher; // ��������ʦ
public:
    Class() : grade(0), classNo(0), headTeacher() { // Ĭ�Ϲ��캯��
        cout << "new class created." << endl;
    }
    Class(int grade_, int classNo_, string teacherName = "unknow", string course = "chinese") 
        : grade(grade_), classNo(classNo_), headTeacher(teacherName, course) { // �������Ĺ��캯��
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
