/*
330. Patching Array
Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] 
inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.

Example 1:

Input: nums = [1,3], n = 6
Output: 1 
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
/*
    Submission Date: 2018-05-30
    Runtime: 9 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    /*
        suppose furthest is the sum of all elements before nums[i], then 
        if furthest >= nums[i] - 1, it means we can include this element and furthest += nums[i]
        else furthest is too small so we can add furthest + 1 (res increases as element is added)
        meaning furthest = 2*furthest + 1 and keep doing this until furthest >= nums[i] - 1
    */
    int minPatches(vector<int>& nums, int n) {
        int res = 0;
        int furthest = 0;
        for(const auto& x: nums) {
            if(furthest >= n) break;
            while(x > furthest + 1 && furthest < n) {
                furthest = (furthest <= (INT_MAX-1)/2) ? furthest*2 + 1 : INT_MAX;
                res++;
            }
            furthest += x;
        }
        
        while(n > furthest) {
            furthest = (furthest <= (INT_MAX-1)/2) ? furthest*2 + 1 : INT_MAX;
            res++;
        }
        return res;
    }
};

int main() {
    return 0;
}