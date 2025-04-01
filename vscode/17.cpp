#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    Solution(int num) {
        n = num;
    }
    void solve();//将n分解为素因子的乘积
private:
    int n;
};

int main()
{
    int n;
    while (cin >> n) {
        Solution obj(n);
        obj.solve();
    }
    return 0;
}
//你的代码将被嵌在这里
