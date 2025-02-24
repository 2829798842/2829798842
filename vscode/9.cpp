#include <iostream>
#include <algorithm>
using namespace std;
int main()
{

    int arr[4] = {2,5,3,1};
    int* p = find(arr, arr + 4, 3);
    //if (p - arr != 4 && *p == 3)
    //{
        cout << p - arr;//Êä³öË÷Òı
    //}
    return 0;
}
