using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if(len <= 1) return;
        
        vector<int>::reverse_iterator ceilIt, endIt;
        for(int i = 0; i < len; i++) {
            endIt = nums.rbegin() + i;
            ceilIt = upper_bound(nums.rbegin(), endIt, nums[len - i - 1]);
            if(ceilIt != endIt) {
              swap(nums[len - i - 1], *ceilIt);
              for(int t : nums) cout << t << endl;
              sort(nums.rbegin(), endIt, greater<int>());
              for(int t : nums) cout << t << endl;
              return;
            }
        }
        
        reverse(nums.begin(), nums.end());
    }
};
int main() {
    Solution s;
    vector<int> v{1,3,2};
    s.nextPermutation(v);
    return 0;
}