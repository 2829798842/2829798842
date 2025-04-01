/*
����ƽ���ϵ�һ��������꣬�Լ�һ��Բ��Բ������Ͱ뾶������õ㵽ԭ��ľ��룬���жϸõ���Բ�ڣ�Բ�⻹����Բ���ϡ�
��Բ��ʱ���������outside"����Բ��ʱ�����"inside"����Բ����ʱ�������on"��
�����Ѿ������˵���Point�Ĳ��ֶ��壬�뽫�亯�����岹������������Ӷ�Բ��Circle���������塣

���в��Գ������£�
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
 ��Ĵ��뽫��Ƕ������ 
int main(){
   double x1,y1,x2,y2,r; 
   cin>>x1>>y1>>x2>>y2>>r;
   Point p(x1,y1);
   Point ctr(x2,y2);
   Circle c(ctr,r);
   cout<<setprecision(3)<<p.distance()<<" "<<c.judge(p)<<endl;
} 
�����ʽ˵����
��ʽ���£�


���x���� ���y����  Բ�ĵ�x���� Բ�ĵ�y���� Բ�İ뾶

����������
��һ���и����������Բ�����꼰�뾶��

2 3 1 1 3
���������
�����������Ӧ����������磺

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