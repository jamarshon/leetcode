
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
174. Dungeon Game
The demons had captured the princess (P) and imprisoned her in the bottom-right
corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid.
Our valiant knight (K) was initially positioned in the top-left room and must
fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at
any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative
integers) upon entering these rooms; other rooms are either empty (0's) or
contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to
move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is
able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be
at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)  -3  3
-5  -10 1
10  30  -5 (P)

Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters
and the bottom-right room where the princess is imprisoned.

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int rows = dungeon.size();
    if (rows == 0) return 0;

    int cols = dungeon.front().size();
    vector<vector<int>> hp(rows + 1, vector<int>(cols + 1, INT_MAX));
    hp[rows][cols - 1] = 1;
    hp[rows - 1][cols] = 1;

    for (int i = rows - 1; i >= 0; i--) {
      for (int j = cols - 1; j >= 0; j--) {
        hp[i][j] = max(1, min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j]);
      }
    }

    return hp[0][0];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the
largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an
integer.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string concat(const vector<string>& nums_str) {
    return accumulate(
        nums_str.begin(), nums_str.end(), string(),
        [](const string& memo, const string& el) { return memo + el; });
  }

  string largestNumber(vector<int>& nums) {
    if (nums.empty()) return "0";
    int N = nums.size();
    vector<string> nums_str(N);
    transform(nums.begin(), nums.end(), nums_str.begin(),
              [](const int& num) { return to_string(num); });
    sort(nums_str.begin(), nums_str.end(),
         [](const string& lhs, const string& rhs) {
           return lhs + rhs > rhs + lhs;
         });

    if (nums_str.front()[0] == '0') return "0";
    return concat(nums_str);
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify
repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that
occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<string, int> freq;
    for (int i = 0; i <= (int)s.size() - 10; i++) {
      string seq = s.substr(i, 10);
      freq[seq]++;
    }

    vector<string> res;
    for (auto kv : freq) {
      if (kv.second > 1) {
        res.push_back(kv.first);
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
188. Best Time to Buy and Sell Stock IV
Say you have an array for which the ith element is the price of a given stock on
day i.

Design an algorithm to find the maximum profit. You may complete at most k
transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell
the stock before you buy again).

/*
    Submission Date: 2017-08-07
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(int K, vector<int>& prices) {
    int N = prices.size();
    if (N < 2) return 0;

    if (K > N) {
      // unlimited transactions
      int count = 0;
      for (int i = 1; i < N; i++) {
        count += max(prices[i] - prices[i - 1], 0);
      }
      return count;
    }

    // space saving dp where dp[k][i] is maximum of k transactions from indices
    // 0 to i dp[k][i] = max(
    //              dp[k][i-1],
    //              prices[i] + max(dp[k-1][j] - prices[j]) for all j < i )
    // dp[0][i] = 0
    vector<int> dp(N, 0);
    for (int k = 1; k <= K; k++) {
      int max_prev_trans = -prices[0];
      for (int i = 1; i < N; i++) {
        max_prev_trans = max(max_prev_trans, dp[i] - prices[i]);
        dp[i] = max(dp[i - 1], prices[i] + max_prev_trans);
      }
    }

    return dp[N - 1];
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
189. Rotate Array
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to
[5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways
to solve this problem.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<int>& nums, int start, int end, int k) {
    if (start >= end) return;
    int N = end - start;

    k %= N;
    if (k == 0) return;

    for (int i = 0; i < k; i++) {
      swap(nums[start + i], nums[end - k + i]);
    }

    rotate(nums, start + k, end, k);
  }
  void rotate2(vector<int>& nums, int k) { rotate(nums, 0, nums.size(), k); }

  void rotate(vector<int>& nums, int k) {
    k %= nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
190. Reverse Bits
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as
00000010100101000001111010011100), return 964176192 (represented in binary as
00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
      res |= n % 2;
      n /= 2;
      if (i != 31) res *= 2;
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
191. Number of 1 Bits
Write a function that takes an unsigned integer and returns the number of ’1'
bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation
00000000000000000000000000001011, so the function should return 3.

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
      n = n & (n - 1);
      count++;
    }
    return count;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
198. House Robber
You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed, the only constraint stopping you from
robbing each of them is that adjacent houses have security system connected and
it will automatically contact the police if two adjacent houses were broken into
on the same night.

Given a list of non-negative integers representing the amount of money of each
house, determine the maximum amount of money you can rob tonight without
alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int rob(vector<int>& nums) {
    if (nums.empty()) return 0;
    int N = nums.size();
    vector<int> dp(N);
    dp[N - 1] = nums[N - 1];

    for (int i = N - 2; i >= 0; i--) {
      dp[i] = max(dp[i + 1], nums[i] + (i + 2 < N ? dp[i + 2] : 0));
    }

    return dp[0];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return
the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

/*
    Submission Date: 2017-07-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    rightSideView(root, res, 0);
    return res;
  }

  void rightSideView(TreeNode* root, vector<int>& res, int depth) {
    if (root == NULL) return;
    if (res.size() <= depth) {
      res.push_back(root->val);
    }

    rightSideView(root->right, res, depth + 1);
    rightSideView(root->left, res, depth + 1);
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of
islands. An island is surrounded by water and is formed by connecting adjacent
lands horizontally or vertically. You may assume all four edges of the grid are
all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3

/*
    Submission Date: 2017-08-03
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int dx_[4] = {0, 0, -1, 1};
  int dy_[4] = {-1, 1, 0, 0};

 public:
  void fill(vector<vector<char>>& grid, int i, int j, int rows, int cols) {
    for (int k = 0; k < 4; k++) {
      int new_row = i + dx_[k];
      int new_col = j + dy_[k];
      if (0 <= new_row && new_row < rows && 0 <= new_col && new_col < cols) {
        if (grid[new_row][new_col] == '1') {
          grid[new_row][new_col] = '0';
          fill(grid, new_row, new_col, rows, cols);
        }
      }
    }
  }
  int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    if (rows == 0) return 0;
    int cols = grid.front().size();
    int res = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (grid[i][j] == '1') {
          fill(grid, i, j, rows, cols);
          res++;
        }
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
201. Bitwise AND of Numbers Range
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of
all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.

/*
    Submission Date: 2017-07-25
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  int rangeBitwiseAnd(int m, int n) {
    int res = 0;
    for (int i = 30; i >= 0; i--) {
      int shift = 1 << i;
      if ((shift & m) == (shift & n)) {
        res |= shift & m;
      } else {
        break;
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  cout << s.rangeBitwiseAnd(5, 7) << endl;
  cout << s.rangeBitwiseAnd(5, 5) << endl;
  cout << s.rangeBitwiseAnd(INT_MAX, INT_MAX - 1) << endl;
  cout << s.rangeBitwiseAnd(0, 0) << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
202. Happy Number
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any
positive integer, replace the number by the sum of the squares of its digits,
and repeat the process until the number equals 1 (where it will stay), or it
loops endlessly in a cycle which does not include 1. Those numbers for which
this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <cmath>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
  unordered_set<int> seen;

 public:
  bool isHappy(int n) {
    if (n == 1) return true;
    if (n == 0 || seen.count(n)) return false;
    seen.insert(n);
    int sum = 0;
    while (n) {
      sum += pow(n % 10, 2);
      n /= 10;
    }
    return isHappy(sum);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
203. Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

/*
    Submission Date: 2017-07-26
    Runtime: 26 ms
    Difficulty: EASY
*/

#include <climits>
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy_head = new ListNode(INT_MIN);
    dummy_head->next = head;

    ListNode* curr = dummy_head;
    while (curr) {
      ListNode* next = curr->next;
      while (next && next->val == val) {
        ListNode* to_delete = next;
        next = next->next;
        delete to_delete;
      }

      curr->next = next;
      curr = next;
    }

    ListNode* to_delete = dummy_head;
    head = dummy_head->next;
    delete to_delete;
    return head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
204. Count Primes
Count the number of prime numbers less than a non-negative number, n.

/*
    Submission Date: 2017-08-03
    Runtime: 43 ms
    Difficulty: EASY
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int countPrimes(int n) {
    if (n <= 2) return 0;
    vector<bool> mask(n, true);

    mask[0] = mask[1] = false;

    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; i++) {
      if (mask[i]) {
        int temp = i * i;
        while (temp < n) {
          mask[temp] = false;
          temp += i;
        }
      }
    }
    // for(auto e: mask) cout << e << ' '; cout << endl;
    return count(mask.begin(), mask.end(), true);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
205. Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while
preserving the order of characters. No two characters may map to the same
character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

/*
    Submission Date: 2017-08-01
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    int N = s.size();
    unordered_map<char, char> hash_map;
    unordered_set<char> mapped;
    for (int i = 0; i < N; i++) {
      if (hash_map.count(s[i])) {
        if (t[i] != hash_map[s[i]]) {
          return false;
        }
      } else {
        if (mapped.count(t[i])) return false;
        hash_map[s[i]] = t[i];
        mapped.insert(t[i]);
      }
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
206. Reverse Linked List
Reverse a singly linked list.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (head == NULL) return NULL;

    ListNode* prev = NULL;
    ListNode* curr = head;
    ListNode* next = head->next;

    while (curr != NULL) {
      curr->next = prev;
      prev = curr;
      curr = next;
      if (next != NULL) next = next->next;
    }

    return prev;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
207. Course Schedule
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to
first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it
possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0, and to take course 0 you should also have finished course 1.
So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency
matrices. Read more about how a graph is represented. You may assume that there
are no duplicate edges in the input prerequisites.

/*
    Submission Date: 2017-08-03
    Runtime: 23 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool checkForCycle(int vertex, const vector<vector<int>>& graph,
                     unordered_set<int>& visited,
                     unordered_set<int>& expanding) {
    if (expanding.count(vertex)) return false;

    expanding.insert(vertex);
    for (auto neighbor : graph[vertex]) {
      if (visited.count(neighbor)) continue;
      if (!checkForCycle(neighbor, graph, visited, expanding)) {
        return false;
      }
    }

    visited.insert(vertex);
    expanding.erase(vertex);

    return true;
  }
  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto prereq : prerequisites) {
      graph[prereq.second].push_back(prereq.first);
    }

    unordered_set<int> visited, expanding;
    for (int i = 0; i < numCourses; i++) {
      if (visited.count(i)) continue;
      if (!checkForCycle(i, graph, visited, expanding)) {
        return false;
      }
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
208. Implement Trie (Prefix Tree)
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

/*
    Submission Date: 2017-08-03
    Runtime: 62 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TrieNode {
  bool is_word;
  TrieNode* child[26];
  TrieNode() {
    is_word = false;
    for (int i = 0; i < 26; i++) child[i] = NULL;
  }
};

class Trie {
  TrieNode* root_;

 public:
  /** Initialize your data structure here. */
  Trie() { root_ = new TrieNode(); }

  /** Inserts a word into the trie. */
  void insert(string word) {
    TrieNode* curr = root_;
    for (auto c : word) {
      if (curr->child[c - 'a'] == NULL) curr->child[c - 'a'] = new TrieNode();
      curr = curr->child[c - 'a'];
    }
    curr->is_word = true;
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
    TrieNode* curr = root_;

    for (int i = 0, N = word.size(); i < N; i++) {
      if (curr->child[word[i] - 'a'] == NULL) return false;
      curr = curr->child[word[i] - 'a'];
    }

    return curr->is_word;
  }

  /** Returns if there is any word in the trie that starts with the given
   * prefix. */
  bool startsWith(string prefix) {
    TrieNode* curr = root_;

    for (int i = 0, N = prefix.size(); i < N; i++) {
      if (curr->child[prefix[i] - 'a'] == NULL) return false;
      curr = curr->child[prefix[i] - 'a'];
    }

    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
209. Minimum Size Subarray Sum
Given an array of n positive integers and a positive integer s, find the minimal
length of a contiguous subarray of which the sum ≥ s. If there isn't one, return
0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

/*
    Submission Date: 2017-07-26
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minSubArrayLen(int s, vector<int>& nums) {
    if (nums.empty()) return 0;

    int N = nums.size();
    int i = 0;
    int curr_sum = 0;
    int start = 0;
    int min_size = INT_MAX;
    while (i < N) {
      curr_sum += nums[i++];
      while (curr_sum >= s) {
        min_size = min(min_size, i - start);
        curr_sum -= nums[start++];
      }
    }
    return min_size == INT_MAX ? 0 : min_size;
  }
};

int main() {
  Solution s;
  return 0;
}