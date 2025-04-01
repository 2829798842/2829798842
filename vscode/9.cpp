#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int main()
{

    //int arr[4] = {2,5,3,1};
    //int *p = find(arr, arr + 4, 3);
    //if (p - arr != 4 && *p == 3)
    //{
        //cout << p - arr;//输出索引
    //}
    /*int i = 0;

    string str = "hello world";
    auto p1 = find(str.begin(), str.end(), 'r');
    while(i++ < str.length())cout << p1 - str.begin() << endl; // 输出索引
    cout << *p1 << endl; // 输出字符 'r'
    
    string str2 = "hello world";

    auto p = find(str2.begin(), str2.end(), 'o'); // 使用 auto 或者 std::string::iterator
    if (p != str2.end() && *p == 'o') { // 检查是否找到了字符 'o' 并且迭代器没有到达字符串末尾
        cout << p - str2.begin() << endl; // 输出索引
    }


    int arr[6] = {0};
    fill(arr, arr + 3, 2) ;
    for (auto x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
    */
    int arr2[10] = {2,3,4,5,5,5,6,7,6,5};
    int cnt = count(arr2, arr2 + 10, 5);
    cout << cnt<<endl;
    string str = "hello world";
    int cnt2 = count(str.begin(), str.end(), 'l');
    cout << cnt2;
    return 0;
}
