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
        //cout << p - arr;//�������
    //}
    /*int i = 0;

    string str = "hello world";
    auto p1 = find(str.begin(), str.end(), 'r');
    while(i++ < str.length())cout << p1 - str.begin() << endl; // �������
    cout << *p1 << endl; // ����ַ� 'r'
    
    string str2 = "hello world";

    auto p = find(str2.begin(), str2.end(), 'o'); // ʹ�� auto ���� std::string::iterator
    if (p != str2.end() && *p == 'o') { // ����Ƿ��ҵ����ַ� 'o' ���ҵ�����û�е����ַ���ĩβ
        cout << p - str2.begin() << endl; // �������
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
