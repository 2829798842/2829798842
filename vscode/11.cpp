#include <iostream>
using namespace std;

// ����cut������ͨ�����ô��β���������
float& cut(float &a, float &b) {
    if (a < b) {
        a = 0;
    } else {
        b = 0;
    }
    return a; // ����a�����ã���ʵ����a��b�Ѿ����޸�
}

int main(){
    float a,b;
    cin>>a>>b;
    cut(a,b)=0; // ����cut�������޸�a��b��ֵ
    cout<<"to pay:"<<a+b<<endl;    
    return 0;
}