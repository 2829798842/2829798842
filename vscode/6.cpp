#include <bits/stdc++.h>
using namespace std;

int main() {
    // ����һ����ά���������ڴ洢�˷���
    vector<vector<int>> outer;
    
    // ���ɳ˷���
    for (int i = 1; i <= 10; i++) {
        // ����һ��һά���������ڴ洢��ǰ�еĳ˷����
        vector<int> inner;
        for (int j = 1; j <= 10; j++)
            // ���� i * j �Ľ������ӵ���ǰ��������
            inner.push_back(i * j);
        
        // ����ǰ��������ӵ�����ά������
        outer.push_back(inner);
    }
    // ��ӡ�˷���
    for (vector<vector<int>>::iterator iter = outer.begin(); iter != outer.end(); ++iter) {
        // ��ȡ��ǰ�е�����
        vector<int> inner = *iter;
        for (vector<int>::iterator it = inner.begin(); it != inner.end(); ++it)
            // ��ӡ��ǰԪ�أ����ÿ��Ϊ 4 ���ַ���ȷ������
            cout << setw(4) << *it;
        // ��ӡ���з�����ʼ�µ�һ��
        cout << endl;
    }
    return 0;
}