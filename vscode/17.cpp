#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    Solution(int num) {
        n = num;
    }
    void solve();//��n�ֽ�Ϊ�����ӵĳ˻�
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
//��Ĵ��뽫��Ƕ������
