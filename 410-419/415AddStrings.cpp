/*
415. Add Strings
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int carry = 0;
        int i = num1.size() - 1, 
            j = num2.size() - 1;
        
        while(i >= 0 || j >= 0) {
            int x = carry;
            if(i >= 0) x += (num1[i] - '0');
            if(j >= 0) x += (num2[j] -'0');
            
            carry = x / 10;
            res.push_back((x % 10) + '0');
            
            i--;
            j--;
        }
        
        if(carry > 0) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    return 0;
}