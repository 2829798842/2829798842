#include<bits/stdc++.h>
using namespace std;
int main()
{ 
    string num1,num2,op;
    cin>>num1>>op>>num2;
    int n1=num1.length(),n2=num2.length();
    int max=n1>n2?n1:n2;
    int min=n1<n2?n1:n2;
    if (op=="+"){
        cout<<'1';
        for(int i=0;i<max-min-1;i++)
            cout<<'0';
        cout<<'1';
        for(int i=0;i<min-1;i++)
            cout<<'0';
    }
    if (op=="*"){
        cout<<'1';
        for(int i=0;i<n1+n2-2;i++)
            cout<<'0';
    }
    return 0;
}