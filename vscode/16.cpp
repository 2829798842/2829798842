#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,p;
    cin>>n>>p;
    int arr[n]; 
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<p;i++){
        int a,b,c;
        cin>>a>>b>>c;
        for(int j=a-1;j<b;j++){
            arr[j]+=c;
        }
    }
    sort(arr,arr+n);
    cout<<arr[0]<<endl;
    return 0;
}