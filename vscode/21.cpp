/*
输入平面上的一个点的坐标，以及一个圆的圆心坐标和半径，输出该点到原点的距离，并判断该点在圆内，圆外还是在圆周上。
在圆外时，将输出“outside"，在圆内时，输出"inside"，在圆周上时，输出“on"。
下面已经给出了点类Point的部分定义，请将其函数定义补充完整，并添加对圆类Circle的完整定义。

裁判测试程序如下：
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
class Point{
    private:
        double x,y;
    public:
        Point();
        Point(double x_,double y_);
        double distance();
        double distance(const Point &p);
        double getX(){return x;}
        double getY(){return y;}
        void setX(double x_);
        void setY(double y_);
};
 你的代码将被嵌入这里 
int main(){
   double x1,y1,x2,y2,r; 
   cin>>x1>>y1>>x2>>y2>>r;
   Point p(x1,y1);
   Point ctr(x2,y2);
   Circle c(ctr,r);
   cout<<setprecision(3)<<p.distance()<<" "<<c.judge(p)<<endl;
} 
输入格式说明：
格式如下：


点的x坐标 点的y坐标  圆心的x坐标 圆心的y坐标 圆的半径

输入样例：
在一行中给出点坐标和圆心坐标及半径：

2 3 1 1 3
输出样例：
在这里给出相应的输出。例如：

3.61 inside
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Point{
    private:
        double x,y;
    public:
        Point();
        Point(double x_,double y_);
        double distance();
        double distance(const Point &p);
        double getX(){return x;}
        double getY(){return y;}
        void setX(double x_);
        void setY(double y_);
};
Point::Point() : x(0), y(0) {}
Point::Point(double x_, double y_) : x(x_), y(y_) {}
void Point::setX(double x_) { x = x_; }
void Point::setY(double y_) { y = y_; }
double Point::distance() {
    return sqrt(x * x + y * y);
}
double Point::distance(const Point &p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
class Circle {
    private:
        Point center;
        double radius;
    public:
        Circle(Point ctr, double r) : center(ctr), radius(r) {}
    
        string judge(const Point &p) {
            double dist = center.distance(p);
            if (dist < radius) {
                return "inside";
            } else if (dist == radius) {
                return "on";
            } else {
                return "outside";
            }
        }
    };

 int main(){
    double x1,y1,x2,y2,r; 
    cin>>x1>>y1>>x2>>y2>>r;
    Point p(x1,y1);
    Point ctr(x2,y2);
    Circle c(ctr,r);
    cout<<setprecision(3)<<p.distance()<<" "<<c.judge(p)<<endl;
 } 