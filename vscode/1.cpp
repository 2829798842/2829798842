#include <iostream>
#include <windows.h>
// ... 其他include保持不变 ...
 
using namespace std;

int main()
{
    // 设置控制台代码页为UTF-8
    //SetConsoleOutputCP(65001);
    // 设置控制台输入代码页为UTF-8  
    //SetConsoleCP(65001);
    cout << "你好" << endl;
    // ... 原有main函数代码 ...
   int a;cin>>a;
   cout<<a;
   cout << "你好" << endl;
   system("pause");
   return 0;
}