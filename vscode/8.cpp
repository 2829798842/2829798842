#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
int cmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b)*(-1);
}
bool comp(int a, int b)
{
    return a > b;    //意思是：若a>b，则a的优先级更大！ 也就是说大的在前面。
}
int main()
{
    // 2、如果想将数组降序排序，就需要写一个简单的函数，改变默认的排序功能
    int arr_2[6] = {4,5,2,-12,3,4};
    qsort(arr_2, 6, sizeof(int), cmp);
    for (auto x : arr_2)
    {
        cout << x << " ";
    }
    cout << '\n';
    sort(arr_2,arr_2+6,comp);
    for (auto x : arr_2)
    {
        cout << x << " ";
    }
    cout << '\n';
    return 0;
}
