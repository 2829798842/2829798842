#include <bits/stdc++.h> 
using namespace std;

class Teacher{
    private:
        string name; //姓名 
        string course; //所教课程 
    public:
        Teacher(){};
        Teacher(string name_,string course_);
        string getName(){return name;}
        string getCourse(){return course;}
};

class Class {
    private:
        int grade; 
        int classNo; 
        Teacher headTeacher; 
    public:
        Class(int grade_, int classNo_, string name_, string course_) : grade(grade_), classNo(classNo_), headTeacher(name_, course_) {
            cout << "grade:" << grade << " class no:" << classNo << ",head teacher:" << headTeacher.getName() << "(" << headTeacher.getCourse() << ")" << endl;
        }
        Class(int grade_, int classNo_, string name_) : grade(grade_), classNo(classNo_), headTeacher(name_, "chinese") {
            cout << "grade:" << grade << " class no:" << classNo << ",head teacher:" << headTeacher.getName() << "(" << headTeacher.getCourse() << ")" << endl;
        }
        Class(int grade_, int classNo_) : grade(grade_), classNo(classNo_), headTeacher("unknown", "chinese") {
            cout << "grade:" << grade << " class no:" << classNo << ",head teacher:" << headTeacher.getName() << "(" << headTeacher.getCourse() << ")" << endl;
        }
        Class() : grade(0), classNo(0), headTeacher("unknown", "chinese") {
            cout << "new class created." << endl;
        }
};
Teacher::Teacher(string name_,string course_){
    name = name_;
    course = course_;
}

int main(){
    Class c1(2,1,"ZhangXiaowen","math");
    Class c2(3,2,"LiSisi");    
    Class c3(1,1);
    Class c4;
    return 0;
}
