#include <iostream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
unsigned long long stringToULL(const string& str) {
    unsigned long long result = 0;
    for (char c : str) {
        result = result * 10 + (c - '0');
    }
    return result;
}
string ullToString(unsigned long long ull) {
    if (ull == 0) return "0";
    string result;
    while (ull > 0) {
        result += char(ull % 10 + '0');
        ull /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string addStrings(const string& num1, const string& num2) {
    string result;
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        carry = sum / 10;
        result += char(sum % 10 + '0');
    }
    reverse(result.begin(), result.end());
    return result;
}
string multiplyStrings(const string& num1, const string& num2) {
    unsigned long long n1 = stringToULL(num1);
    unsigned long long n2 = stringToULL(num2);
    return ullToString(n1 * n2);
}

int main() {
    string num1, num2, op;
    
    cin >> num1 >> op >> num2;
    
    if (op == "+") {
        cout << addStrings(num1, num2) << std::endl;
    } else if (op == "*") {
        cout << multiplyStrings(num1, num2) << std::endl;
    } else {
        cout << "Invalid operator" << std::endl;
    }

    return 0;
}
