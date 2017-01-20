using namespace std;
#include <iostream>

class Solution {
public:
    int mySqrt(int x) {
        if(x == 0) return 0;
        int low = 1;
        int high = x;
        int mid, midComplement;
        while(true) {
            mid = (low + high) / 2;
            if(midComplement == mid) {
                return mid;
            } else if(mid > x / mid) {
                high = mid - 1;
            } else if(mid + 1 > x / (mid + 1)) {
                return mid;                
            } else {
                low = mid + 1;
            }
        }
    }
};
int main() {
    Solution s;
    cout << s.mySqrt(8192) << endl;
    cout << s.mySqrt(1) << endl;
    cout << s.mySqrt(2) << endl;
    return 0;
}