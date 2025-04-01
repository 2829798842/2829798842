#include <bits/stdc++.h>
using namespace std;
/*
int main() {
    vector<int> nums;
    nums.insert(nums.end(), {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    nums.erase(nums.begin() + 5, nums.begin() + 8);
    for(auto num : nums)
        cout << num << " ";
    cout << endl;
    for(int i=0;i<nums.size();i++)
        cout << nums.at(i) << " ";
    cout << endl;
    return 0;
}
*//*
int main() {
    int i;
    vector<int> num(5,99);
    for(i=0;i<num.size();i++)
        cout << num[i] << " ";
    cout << endl;
    vector<int> num1(num);
    for(i=0;i<num1.size();i++)
        cout << num1[i] << " ";
    cout << endl;
    vector<int> num2(num.begin(),num.end());
    for(i=0;i<num2.size();i++)
        cout << num2[i] << " ";
    cout << endl;
    return 0;
}
*//*
int main(){
    vector<int> nums;
    nums.insert(nums.end(), {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    for(auto it = nums.begin(); it != nums.end(); it++)
    {
        cout << *it << " ";
    }

}
*/
int main() {
    vector<int> nums;
    if(nums.empty()==0) cout << "not empty";
    else cout << "empty";
    cout<<endl;
    nums.push_back(1);
    nums.push_back(2);
    if(nums.empty()==0) cout << "not empty";
    else cout << "empty";
    cout<<endl;
    nums.clear();
    if(nums.empty()==0) cout << "not empty";
    else cout << "empty";
    cout<<endl;
    return 0;
}