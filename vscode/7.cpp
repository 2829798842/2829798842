#include <bits/stdc++.h>
using namespace std;

class point{
    public:
        point(int a, int b){
            x = a;
            y = b;
        }
        point(int x){
            this->x = x;
            y = 0;
        }
        point(const point& p){
            x =2 * p.x;
            y =2 * p.y;
        }
        ~point(){
            cout << "destructor called" << endl;
        }
        void print(){    
            cout << "x = " << x << " y = " << y << endl;
        }
    private:
        int x, y;
};

int main(){
    point p1(30, 40);
    p1.print();
    point p2(p1);
    p2.print();
    point p3(10);
    p3.print();
    return 0;
}