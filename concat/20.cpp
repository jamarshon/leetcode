
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
389. Find the Difference
Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter at a random position.

Find the letter that was added in t.

Example:

Input:
s = "abcd"
t = "abcde"

Output:
e

Explanation:
'e' is the letter that was added.
/*
    Submission Date: 2018-05-02
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        unordered_map<char,int> m;
        for(auto e: s) m[e]++;
        for(auto e: t) {
          if(m.count(e)) {
            if(m[e] == 0) return e;
            m[e]--;
          } else {
            return e;
          }
        }
        return '\0';
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
392. Is Subsequence
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in 
both s and t. t is potentially a very long (length ~= 500,000) string, 
and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the 
original string by deleting some (can be none) of the characters 
without disturbing the relative positions of the remaining characters. 
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, 
and you want to check one by one to see if T has its subsequence. 
In this scenario, how would you change your code?

/*
    Submission Date: 2017-08-30
    Runtime: 69 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_index = 0, t_index = 0;
        int s_len = s.size(), t_len = t.size();
        
        while(s_index < s_len && t_index < t_len) {
            if(s[s_index] == t[t_index]) {
                s_index++;
            }
            t_index++;
        }
        
        return s_index == s_len;
    }

    bool isSubsequence2(string s, string t) {
        int N = s.size(), M = t.size();
        vector<vector<bool>> dp(N + 1, vector<bool>(M + 1, false));
        for(int i = 0; i <= M; i++) dp[0][i] = true;
    
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        return dp[N][M];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
394. Decode String
Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
/*
    Submission Date: 2018-05-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        find a '[', use count to determine the matching ']'. recursively determine the string in between.
        find the number beside '[' and repeat the string in between that many times. look for '[' and repeat
        until there is no more '[', then just add the suffix.
    */
    string decodeString(string s) {
        int start = 0;
        
        string res = "";
        while(s.find('[', start) != string::npos) {
            int bracket_index = s.find('[', start);
        
            int num_index = bracket_index - 1;
            while(num_index >= 0 && isdigit(s[num_index])) {
                num_index--;
            }

            res += s.substr(start, num_index + 1 - start);
            
            int num = stoi(s.substr(num_index + 1, bracket_index - num_index - 1));
            int cnt = 0;
            for(int i = bracket_index; i < s.size(); i++) {
                cnt += s[i] == '[';            
                cnt -= s[i] == ']';
                if(cnt == 0) {
                    string to_repeat = decodeString(s.substr(bracket_index + 1, i - bracket_index - 1));
                    for(int j = 0; j < num; j++) {
                        res += to_repeat;
                    }
                    start = i + 1;
                    break;
                }
            }
        }
        
        return res + s.substr(start);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
401. Binary Watch
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
/*
    Submission Date: 2018-06-08
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    int NumBits(int x) {
        int res = 0;
        while(x) {
            x &= (x-1);
            res++;
        }
        
        return res;
    }
public:
    /*
    map with key being number of bits and value being the number
    for each hour, get the number of bits and then lookup the remaining
    number of bits needed
    */
    vector<string> readBinaryWatch(int num) {
        unordered_map<int, vector<string>> m;
        for(int i = 0; i < 60; i++) 
            m[NumBits(i)].push_back((i < 10 ? ":0" : ":") + to_string(i));
        
        vector<string> res;
        for(int i = 0; i < 12; i++) {
            int target = num - NumBits(i);
            if(!m.count(target)) continue;
            for(const auto& e: m[target])
                res.push_back(to_string(i) + e);
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
404. Sum of Left Leaves
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 0;
        if(root -> left && root -> left -> left == NULL && root -> left -> right == NULL) {
            res += root -> left -> val;
        }
        
        return res + sumOfLeftLeaves(root -> left) + sumOfLeftLeaves(root -> right);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
405. Convert a Number to Hexadecimal
Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, 
the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.
Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"
/*
    Submission Date: 2018-05-26
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
        % 16 gets the last 4 bits. if it is negative then add 16 ie -1 -> 15.
        >> 4 shifts by 4 bits through sign extending so it is not equivalent to / 16
        since the last 4 bits are added first the string must be reversed.
        the last non zero character is the first character in the string so trim it.
    */
    char helper(int x){ if(x < 0) x += 16; return (x % 10) + (x < 10 ? '0' : 'a'); }
    string toHex(int num) {
        string res = "";
        int last_non_zero = 0;
        
        for(int i = 0; i < 8; i++) {
            res.push_back(helper(num % 16));
            num >>= 4;
            if(res.back() != '0') last_non_zero = i;
        }
        
        res = res.substr(0, last_non_zero + 1);
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
409. Longest Palindrome
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
/*
    Submission Date: 2018-05-30
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // return all the frequencies floored to nearest multiple of 2 and add one for if any of the frequency is odd
    int longestPalindrome(string s) {
        unordered_map<char, int> letter_to_freq;
        for(const auto& c: s) letter_to_freq[c]++;
        int res = 0;
        bool has_odd = false;
        
        for(const auto& kv: letter_to_freq) {
            res += (kv.second / 2)*2;
            has_odd |= kv.second % 2;
        }
        
        return res + has_odd;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. 
For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
/*
    Submission Date: 2018-05-31
    Runtime: 5 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res;
        for(int i = 1; i <= n; i++) {
            string s = "";
            if(i % 3 == 0) s += "Fizz";
            if(i % 5 == 0) s += "Buzz";
            if(s.empty()) s = to_string(i);
            res.push_back(s);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
414. Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> distinct;
        int max_item = nums.front();
        for(auto num: nums) {
            max_item = max(max_item, num);
            if(distinct.count(num)) continue;
            min_heap.push(num);
            distinct.insert(num);
            if(min_heap.size() > 3) {
                int to_delete = min_heap.top();
                distinct.erase(to_delete);
                min_heap.pop();
            }
        }
        
        return min_heap.size() == 3 ? min_heap.top() : max_item;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
419. Battleships in a Board
Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. 
You may assume the following rules:
You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 
(N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
    N by checking if the element to the left and to the top of board[i][j] isn't a 'X'.
    If there is one then it means it is continuing a ship so it should not be counted.
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if(board.empty()) return 0;
        int res = 0;
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                if(board[i][j] == 'X' && (j == 0 || board[i][j-1] != 'X') && (i == 0 || board[i-1][j] != 'X')) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
433. Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices from 
"A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), 
where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. 
A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the 
minimum number of mutations needed to mutate from "start" to "end". If there is no 
such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    bool isConnect(string s1, string s2) {
        int diff_count = 0;
        for(int i = 0, len = s1.size(); i < len; i++) {
            diff_count += s1[i] != s2[i];
        }
        return diff_count == 1;
    }
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, vector<string>> graph;

        bank.push_back(start);
        int N = bank.size();
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                if(isConnect(bank[i], bank[j])) {
                    graph[bank[i]].push_back(bank[j]);
                    graph[bank[j]].push_back(bank[i]);
                }
            }
        }

        unordered_set<string> visited;
        queue<pair<string, int>> q;
        q.emplace(start, 0);
        visited.insert(start);

        string curr;
        int dist;
        while(!q.empty()) {
            tie(curr, dist) = q.front();
            // cout << curr << ' ' << dist << endl;
            q.pop();
            if(curr == end) return dist;
            for(auto neighbor: graph[curr]) {
                if(visited.count(neighbor)) continue;
                q.emplace(neighbor, dist + 1);
                visited.insert(neighbor);
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p 
will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

/*
    Submission Date: 2017-08-06
    Runtime: 106 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int M = s.size();
        int N = p.size();
        
        if(M < N) return res;
        unordered_map<char, int> freq, curr_freq;
        
        for(auto c: p) freq[c]++;
        
        for(int i = 0; i < N; i++) curr_freq[s[i]]++;
        
        int low = 0;
        int high = N;
        while(high <= M) {
            bool is_match = true;
            if(curr_freq.size() == freq.size()) {
                for(auto kv: freq) {
                    if(curr_freq.count(kv.first) && curr_freq[kv.first] == kv.second) continue;
                    is_match = false;
                    break;
                }
            } else {
                is_match = false;
            }
            
            if(is_match) res.push_back(low);
            if(high == M) break;
            char to_erase = s[low++];
            curr_freq[s[high++]]++;
            if(curr_freq[to_erase] == 1) curr_freq.erase(to_erase);
            else curr_freq[to_erase]--;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
442. Find All Duplicates in an Array
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and 
others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

/*
    Submission Date: 2017-08-06
    Runtime: 176 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int N = nums.size();
        vector<int> res;
        for(int i = 0; i < N; i++) {
            while(nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
    
        for(int i = 0; i < N; i++) {
            if(nums[i] != i + 1) {
                res.push_back(nums[i]);
            }
        }
         
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
447. Number of Boomerangs
Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) 
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
/*
    Submission Date: 2018-06-08
    Runtime: 284 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;
        int N = points.size();
        
        for(int i = 0; i < N; i++) {
            /*
            From this point find the distance of all points from this point.
            if there are m points that are at the same distance from this point,
            if m is less than 2 then it can't be used else it is permutation without
            repetition which is n!/(n-r)! = m!/(m-2)! = m*(m-1)
            */
            unordered_map<int, int> dist_sq_m;
            for(int j = 0; j < N; j++) {
                if(j == i) continue;
                int dist_sq = pow(points[i].first - points[j].first, 2) + 
                    pow(points[i].second - points[j].second, 2);
                dist_sq_m[dist_sq]++;
            }
            
            for(const auto& kv: dist_sq_m) {
                if(kv.second < 2) continue;
                res += kv.second*(kv.second - 1);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
448. Find All Numbers Disappeared in an Array
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
/*
    Submission Date: 2018-06-04
    Runtime: 155 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for(int i = 0; i < nums.size(); i++) {
            while(nums[nums[i]-1] != nums[i]) swap(nums[nums[i]-1], nums[i]);
        }
        
        vector<int> res;
        for(int i = 0; i < nums.size(); i++) {
            if(i + 1 != nums[i]) res.push_back(i+1);
        }
        
        return res;
    }
};

int main() {
    return 0;
}