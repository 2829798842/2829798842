#include <list>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main() {
    list<int> myList = {1, 2, 3, 4, 5, 3};
    myList.remove(3);
    for (const auto& elem : myList) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}