/*
599. Minimum Index Sum of Two Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of 
favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there 
is a choice tie between answers, output all of them with no order requirement. You could assume 
there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with 
index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.
/*
    Submission Date: 2017-05-29
    Runtime: 103 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> m;
        for(int i = 0; i < list1.size(); i++) {
            m[list1[i]] = i;
        }
        
        vector<string> res;
        int min_index_sum = -1;
        for(int i = 0; i < list2.size(); i++) {
            string s2 = list2[i];
            if(m.count(s2)) {
                int new_sum = i + m[s2];
                if(min_index_sum == -1) {
                    min_index_sum = new_sum;
                    res.push_back(s2);
                    continue;
                }
                
                if(new_sum == min_index_sum) {
                    res.push_back(s2);
                } else if(new_sum < min_index_sum) {
                    min_index_sum = new_sum;
                    res.clear();
                    res.push_back(s2);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<string> v1{"Shogun","Tapioca Express","Burger King","KFC"};
    vector<string> v2{"Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"};
    vector<string> t = s.findRestaurant(v1, v2);
    cout << t.size() << endl;
    return 0;
}