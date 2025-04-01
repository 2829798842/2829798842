#include <iostream>
using namespace std;

// 定义cut函数，通过引用传参并返回引用
float& cut(float &a, float &b) {
    if (a < b) {
        a = 0;
    } else {
        b = 0;
    }
    return a; // 返回a的引用，但实际上a或b已经被修改
}

int main(){
    float a,b;
    cin>>a>>b;
    cut(a,b)=0; // 调用cut函数，修改a或b的值
    cout<<"to pay:"<<a+b<<endl;    
    return 0;
}