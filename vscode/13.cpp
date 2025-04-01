#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    /*
    int arr[6] = {2,5,4,3,3,1};
    int* p = find(arr, arr + 4, 3);
    if (p - arr != 4 && *p == 3)
    {
        cout << p - arr;//Êä³öË÷Òý
    }
     */
    vector<int> v;
    v.push_back(2);
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(3);
    v.push_back(1);
    size_t a=v.size();
    cout<<a<<endl;
    for_each(v.begin(), v.end(), [&v, a](int& x){
        if(&x != &v[a-1]) cout << x << " ";
        else cout << 0;
    });
    
    cout << endl;
    remove(v.begin(), v.end(), 3);
    for(auto x:v) cout << x << " ";
    cout << endl;
    remove_if(v.begin(), v.end(), [](int& x){
        return x == 3;
    });
    for(auto x:v) cout << x << " ";
    cout << endl;
    return 0;
}