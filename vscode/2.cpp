
#include<iostream>
#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//SetConsoleOutputCP(936);
    //SetConsoleOutputCP(CP_UTF8);
    //system("chcp 65001");
    string msg1 =   "Œ“∫‹Àß";
    int a=MessageBoxA(NULL,msg1.c_str(),"hello",MB_OKCANCEL|MB_ICONINFORMATION|MB_HELP|MB_DEFBUTTON2);
    if(a==IDOK) cout<<"OK"<<endl;
    else if(a==IDCANCEL) cout<<"Cancel"<<endl;
    else if(a==IDHELP) cout<<"Help"<<endl;
    else cout<<"Default"<<endl;
    //cout<<"Hello World"<<endl;
    cout<<"ƒ„∫√"<<endl;
    string s1;
    cin>>s1;
    cout<<s1<<endl;
	cout<<s1<<endl;
    system("pause");
	return 0;
}