
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
565. Array Nesting
A zero-indexed array A consisting of N different integers is given. The array contains 
all integers in the range [0, N - 1].

Sets S[K] for 0 <= K < N are defined as follows:

S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.

Sets S[K] are finite for each K and should NOT contain duplicates.

Write a function that given an array A consisting of N integers, return the size of 
the largest set S[K] for this array.

Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
Note:
N is an integer within the range [1, 20,000].
The elements of A are all distinct.
Each element of array A is an integer within the range [0, N-1].
/*
    Submission Date: 2017-05-29
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int N = nums.size();
        vector<bool> mask(N, true);
        int max_set = 0;
        for(int i = 0; i < N; i++) {
            if(mask[i]) { // hasn't been processed
                int current = i;
                int current_set = 0;
                while(true) {
                    if(current >= N || !mask[current]) break;
                    mask[current] = false;
                    current = nums[current];
                    current_set++;
                }
                max_set = max(current_set, max_set);
            }
        }
        return max_set;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
566. Reshape the Matrix
In MATLAB, there is a very useful function called 'reshape', which can reshape a
matrix into a new one with different size but keep its original data.

You're given a matrix represented by a two-dimensional array, and two positive
integers r and c representing the row number and column number of the wanted
reshaped matrix, respectively.

The reshaped matrix need to be filled with all the elements of the original
matrix in the same row-traversing order as they were.

If the 'reshape' operation with given parameters is possible and legal, output
the new reshaped matrix; Otherwise, output the original matrix.

Example 1:
Input:
nums =
[[1,2],
 [3,4]]
r = 1, c = 4
Output:
[[1,2,3,4]]
Explanation:
The row-traversing of nums is [1,2,3,4]. The new reshaped matrix is a 1 * 4
matrix, fill it row by row by using the previous list. Example 2: Input: nums =
[[1,2],
 [3,4]]
r = 2, c = 4
Output:
[[1,2],
 [3,4]]
Explanation:
There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix. So output the
original matrix. Note: The height and width of the given matrix is in range [1,
100]. The given r and c are all positive.
/*
    Submission Date: 2018-05-31
    Runtime: 39 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
    if (nums.empty()) return {};
    int N = nums.size();
    int M = nums[0].size();

    // cannot gain or lose elements
    if (N * M != r * c) return nums;

    vector<vector<int>> res(r, vector<int>(c));
    int x = 0;
    int y = 0;

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        res[i][j] = nums[y][x];
        x++;
        if (x == M) {
          x = 0;
          y++;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
567. Permutation in String
Given two strings s1 and s2, write a function to return true if s2 contains the
permutation of s1. In other words, one of the first string's permutations is the
substring of the second string. Example 1: Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
/*
    Submission Date: 2018-06-02
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  frequency map of s1 with variable to_use as global to check if everything
  equals 0 use sliding window where everything in a window is a valid character
  and does not exceed the frequency map limit for certain character for a new
  character, if it exceeds the limit or its not a valid character than keep
  moving front (restoring freq map). if it is not a valid character, the map
  will be restored and to_do = original Check if character is valid, if it is
  use it else move front so that it is not included
  */
  bool checkInclusion(string s1, string s2) {
    vector<int> freq(26, 0);
    unordered_set<char> letters(s1.begin(), s1.end());
    for (const auto& c : s1) freq[c - 'a']++;

    int front = 0;
    int back = 0;

    int N = s2.size();
    int to_use = s1.size();

    while (back < N) {
      if (to_use == 0) return true;
      // slide the front until the letter is removed
      int back_val = s2[back] - 'a';
      while (front < back && freq[back_val] == 0) {
        freq[s2[front] - 'a']++;
        front++;
        to_use++;
      }

      /* if the back letter is in s1, decrease the frequency and to_use
          else it means front == back as freq[s2[back]] == 0 so increase front
          to not include this letter
      */
      if (letters.count(s2[back])) {
        freq[back_val]--;
        to_use--;
      } else {
        front++;
      }

      back++;
    }

    return to_use == 0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
572. Subtree of Another Tree
Given two non-empty binary trees s and t, check whether tree t has exactly the
same structure and node values with a subtree of s. A subtree of s is a tree
consists of a node in s and all of this node's descendants. The tree s could
also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of
s. Example 2: Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
/*
    Submission Date: 2018-06-09
    Runtime: 29 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  void serialize(TreeNode* node, string& res) {
    if (node == NULL) {
      res += "null,";
    } else {
      res += to_string(node->val) + ",";
      serialize(node->left, res);
      serialize(node->right, res);
    }
  }

  // check if s == t or s contains a subtree t
  bool isSubtree(TreeNode* s, TreeNode* t) {
    string s1 = "", s2 = "";
    serialize(s, s1);
    serialize(t, s2);
    return s1 == s2 || s1.find("," + s2) != string::npos;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
575. Distribute Candies
Given an integer array with even length, where different numbers in this array
represent different kinds of candies. Each number means one candy of the
corresponding kind. You need to distribute these candies equally in number to
brother and sister. Return the maximum number of kinds of candies the sister
could gain. Example 1: Input: candies = [1,1,2,2,3,3] Output: 3 Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for
each kind. Optimal distribution: The sister has candies [1,2,3] and the brother
has candies [1,2,3], too. The sister has three different kinds of candies.
Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has
candies [1,1]. The sister has two different kinds of candies, the brother has
only one kind of candies. Note:

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].
/*
    Submission Date: 2018-05-31
    Runtime: 247 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  // Count the number of distinct candies. Return the min of this and the max
  // size of the array which is candies.size()/2.
  int distributeCandies(vector<int>& candies) {
    unordered_set<int> st(candies.begin(), candies.end());
    return min(candies.size() / 2, st.size());
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this 
subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array 
sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

/*
    Submission Date: 2017-05-13
    Runtime: 52 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
            int N = nums.size();
            vector<int> cpy(N);
            copy(nums.begin(), nums.end(), cpy.begin());
            sort(nums.begin(), nums.end());

            int i;
            for(i = 0; i < N; i++) {
                if(nums[i] != cpy[i]) break;
            }

            int j;
            for(j = N-1; j >= 0; j--) {
                if(nums[j] != cpy[j]) break;
            }

        return max(j - i + 1, 0);
    }
};

int main() {
    Solution s;
    vector<int> v{2, 6, 4, 8, 10, 9, 15};
    cout << s.findUnsortedSubarray(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
582. Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This 
is just like a tree structure. Only one process has PPID that is 0, which means this process 
has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains 
PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list 
of PIDs of processes that will be killed in the end. You should assume that when a process 
is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.
/*
    Submission Date: 2017-05-13
    Runtime: 166 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        int N = pid.size();
        for(int i = 0; i < N; i++) {
            int _ppid = ppid[i];
            int _pid = pid[i];

            if(m.find(_ppid) == m.end()) {
                m[_ppid] = {_pid};
            } else {
                m[_ppid].push_back(_pid);
            }
        }

        vector<int> result{kill};
        int i = 0;
        while(i < result.size()) {
            int current = result[i];
            if(m.find(current) != m.end()) { // non leaf
                vector<int> children = m[current];
                for(auto c: children) {
                    result.push_back(c);
                }
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution s;
    vector<int> pid{1, 3, 10, 5, 4, 1};
	vector<int> ppid{3, 0, 5, 3, 10, 5};
    int kill = 5;
    vector<int> t = s.killProcess(pid, ppid, kill);
	for(auto l: t) cout << l << " ";
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
583. Delete Operation for Two Strings
Given two words word1 and word2, find the minimum number of steps required to 
make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

/*
    Submission Date: 2017-05-13
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int row = word2.size() + 1;
        int col = word1.size() + 1;
        int dp[501][501];
        for(int i = 0; i < row; i++) dp[i][0] = i;
        for(int i = 0; i < col; i++) dp[0][i] = i;

        for(int i = 1; i < row; i++) {
            for(int j = 1; j < col; j++) {
                if(word2[i - 1] == word1[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + 1;
                }
            }
        }
        
        return dp[row - 1][col - 1];
    }
};

int main() {
	Solution s;
    cout << s.minDistance("sea", "eat");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
589. N-ary Tree Preorder Traversal
Given an n-ary tree, return the preorder traversal of its nodes' values.
 

For example, given a 3-ary tree:


 

Return its preorder traversal as: [1,3,5,6,2,4].
 

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2018-07-14
    Runtime: 52 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
 public:
  vector<int> preorder(Node* root) {
    if (root == NULL) return {};
    stack<Node*> stk;
    stk.emplace(root);
    vector<int> res;

    while (!stk.empty()) {
      Node* curr = stk.top();
      stk.pop();
      res.push_back(curr->val);
      for (int i = curr->children.size() - 1; i >= 0; i--) {
        if (curr->children[i]) stk.push(curr->children[i]);
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
590. N-ary Tree Postorder Traversal
Given an n-ary tree, return the postorder traversal of its nodes' values.
 

For example, given a 3-ary tree:


 

Return its postorder traversal as: [5,6,3,2,4,1].
 

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2018-07-13
    Runtime: 44 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
 public:
  vector<int> postorder(Node* root) {
    if (root == NULL) return {};
    stack<pair<int, Node*>> stk;
    stk.emplace(0, root);
    vector<int> res;

    int ind;
    Node* curr;
    while (!stk.empty()) {
      tie(ind, curr) = stk.top();
      stk.pop();
      if (ind == curr->children.size()) {
        res.push_back(curr->val);
      } else {
        stk.emplace(ind + 1, curr);
        if (curr->children[ind]) stk.emplace(0, curr->children[ind]);
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
592. Fraction Addition and Subtraction
Given a string representing an expression of fraction addition
and subtraction, you need to return the calculation result in string
format. The final result should be irreducible fraction. If your final
result is an integer, say 2, you need to change it to the format of
fraction that has denominator 1. So in this case, 2 should be
converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'.
So does the output.
Each fraction (input and output) has format ±numerator/denominator.
If the first input fraction or the output is positive, then '+' will
be omitted.
The input only contains valid irreducible fractions, where the
numerator and denominator of each fraction will always be in the
range [1,10]. If the denominator is 1, it means this fraction is
actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed
to be valid and in the range of 32-bit int.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
struct Fraction {
  ll num, den;
};

class Solution {
 public:
  ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

  ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

  // a/b + c/d = (a*lcm(b,d)/b + c*lcm(b,d)/d)/lcm(b,d)
  // 1/4 + 1/16 = (1*16/4 + 1*16/16)/16 = (4+1)/16
  // 1/3 + 2/4 = (1*12/3 + 2*12/4)/12 = (4+6)/12

  // (a*(b*d/gcd(b,d))/b + c*(b*d/gcd(b,d))/d)/(b*d/gcd(b,d))
  // (a*d/gcd(b,d) + c*b/gcd(b,d))/(b*d/gcd(b,d))
  // ((a*d + c*b)/gcd(b,d)*gcd(b,d))/(b*d)
  // (a*d + b*c)/(b*d)
  Fraction add(Fraction a, Fraction b) {
    return {a.num * b.den + a.den * b.num, a.den * b.den};
  }

  Fraction reduce(Fraction a) {
    int gcd_num_den = gcd(abs(a.num), a.den);
    return {a.num / gcd_num_den, a.den / gcd_num_den};
  }

  string fractionAddition(string s) {
    vector<Fraction> v;
    int N = s.size();
    bool is_negative = false;
    for (int i = 0; i < N;) {
      // s[i] is beginning of numerator which is either '-' (negative num), '+'
      // (positive num) or a number (positive num and is start of string)
      Fraction fr;
      is_negative = s[i] == '-';

      if (s[i] == '+' || is_negative) {
        i++;
      }

      ll curr = 0;
      while (isdigit(s[i])) {
        curr = curr * 10 + (s[i] - '0');
        i++;
      }

      fr.num = is_negative ? -curr : curr;
      // s[i] is the '/' followed by a number so end i where the next operator
      // starts
      assert(s[i++] == '/');

      curr = 0;
      while (isdigit(s[i]) && i < N) {
        curr = curr * 10 + (s[i] - '0');
        i++;
      }

      fr.den = curr;
      v.push_back(fr);
    }

    Fraction res = v.front();
    res = reduce(res);
    for (int i = 1; i < v.size(); i++) {
      res = add(res, v[i]);
      res = reduce(res);
    }

    return to_string(res.num) + "/" + to_string(res.den);
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-05-27
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    double eucl_sq(vector<int>& p1, vector<int>& p2) {
        return pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2);
    }

    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // distance squared
        vector<double> dist{eucl_sq(p1, p2), eucl_sq(p1, p3), eucl_sq(p1, p4), eucl_sq(p2, p3), eucl_sq(p2, p4), eucl_sq(p3, p4)};

        sort(dist.begin(), dist.end());

        // should result in 4 equal length sides and two longer sides that are the diagonals 
        bool equal_sides = dist[0] == dist[1] && dist[1] == dist[2] && dist[2] == dist[3];
        bool non_zero_sides = dist[0] > 0;

        // pythagoras: x^2 + x^2 = y^2 => 2x^2 = y^2
        bool correct_diagonals = dist[4] == dist[5] &&  2*dist[0] == dist[4];
        return equal_sides && non_zero_sides && correct_diagonals;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the
four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array
with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four
equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
 public:
  int distSq(vector<int>& a, vector<int>& b) {
    return pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2);
  }
  bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3,
                   vector<int>& p4) {
    vector<int> dist;
    vector<vector<int>> v{p1, p2, p3, p4};
    for (int i = 0; i < 4; i++) {
      for (int j = i + 1; j < 4; j++) {
        dist.push_back(distSq(v[i], v[j]));
      }
    }

    // given points a,b,c,d -> dist will contain ab ac ad bc bd cd
    // out of these 6 distances, there are 4 distances which are the side
    // distances (s) and 2 that are hypotenuse (h) s^2 + s^2 = h^2

    assert(dist.size() == 6);
    map<int, int> freq;
    for (auto e : dist) freq[e]++;

    if (freq.size() != 2) return false;
    int s = freq.begin()->first;
    int h = next(freq.begin(), 1)->first;
    return 2 * s == h;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
594. Longest Harmonious Subsequence
We define a harmonious array is an array where the difference between its maximum value and its minimum 
value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all 
its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.
/*
    Submission Date: 2017-05-27
    Runtime: 109 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        int max_len = 0;
        for(int d: nums) {
            int current = 0;
            if(freq.find(d) != freq.end()) {
                current += freq[d];
                freq[d] += 1;
            } else {
                freq[d] = 1;
            }

            int adj = 0;
            if(freq.find(d-1) != freq.end()) {
                adj = max(adj, freq[d-1]);
            }

            if(freq.find(d+1) != freq.end()) {
                adj = max(adj, freq[d+1]);
            }

            if(adj == 0) continue;
            current += adj + 1;
            max_len = max(current, max_len);
        }
        return max_len;
    }
};

int main() {
    vector<int> v{1,3,2,2,5,2,3,7};
    Solution s;
    cout << s.findLHS(v) << endl;
    return 0;
}