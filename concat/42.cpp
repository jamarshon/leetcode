
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
959. Regions Cut By Slashes
In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \,
or blank space.  These characters divide the square into contiguous regions.

(Note that backslash characters are escaped, so a \ is represented as "\\".)

Return the number of regions.

Example 1:

Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:

Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:

Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/,
and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:

Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\,
and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:

Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

Note:

  1 <= grid.length == grid[0].length <= 30
  grid[i][j] is either '/', '\', or ' '.
/*
  Submission Date: 2019-02-10
  Runtime: 176 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct UnionFind {
  unordered_map<int, int> parent_, rank_;
  void Create(int x) {
    parent_[x] = x;
    rank_[x] = 0;
  }

  int Find(int x) {
    if (parent_[x] != x) parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Union(int x, int y) {
    int r1 = Find(x);
    int r2 = Find(y);

    if (r1 == r2) return;
    if (rank_[r1] < rank_[r2]) {
      parent_[r1] = r2;
    } else {
      parent_[r2] = r1;
      if (rank_[r1] == rank_[r2]) rank_[r1]++;
    }
  }
};

enum Directions { NORTH, EAST, SOUTH, WEST };

class Solution {
 public:
  /*
  4*n*n grid where the four represents north, east, south, west of a single
  1x1 block where the block is split into 4 by the diagonals
  ----
  |\/|
  |/\|
  ----

  if grid[i][j] is '/' then we can only join north,west and south,east
  if grid[i][j] is '\' then we can only join north,east and south,west
  if its empty join all 4

  then connect adjacent cells.

  flatten a 2d array of [N][M] than element [i][j] is i*M + j
  flatten a 3d array of [N][M][O] than element [i][j][k] is i*M + j + k*N*M or
    O*(i*M + j) + k which has the z elements be contiguous and not the x elments
  */
  int regionsBySlashes(vector<string>& grid) {
    UnionFind uf;
    int N = grid.size();
    for (int i = 0; i < 4 * N * N; i++) uf.Create(i);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        char c = grid[i][j];
        int key = 4 * (i * N + j);
        if (c != '/') {
          uf.Union(key + NORTH, key + EAST);  // north,east
          uf.Union(key + SOUTH, key + WEST);  // south,west
        }
        if (c != '\\') {
          uf.Union(key + NORTH, key + WEST);  // north,west
          uf.Union(key + SOUTH, key + EAST);  // south,east
        }

        // adjacent cells
        // north and south
        if (i > 0) uf.Union(key + NORTH, (key - 4 * N) + SOUTH);
        if (i + 1 < N) uf.Union(key + SOUTH, (key + 4 * N) + NORTH);

        // west and east
        if (j > 0) uf.Union(key + WEST, (key - 4) + EAST);
        if (j + 1 < N) uf.Union(key + EAST, (key + 4) + WEST);
      }
    }

    int ans = 0;
    // find the number of components
    for (int i = 0; i < 4 * N * N; i++) ans += uf.Find(i) == i;
    return ans;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
961. N-Repeated Element in Size 2N Array
In a array A of size 2N, there are N+1 unique elements, and exactly one of these
elements is repeated N times.

Return the element repeated N times.

Example 1:

Input: [1,2,3,3]
Output: 3

Example 2:

Input: [2,1,2,5,3,2]
Output: 2

Example 3:

Input: [5,1,5,2,5,3,5,4]
Output: 5

Note:

  4 <= A.length <= 10000
  0 <= A[i] < 10000
  A.length is even
/*
  Submission Date: 2019-01-26
  Runtime: 32 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int repeatedNTimes(vector<int>& A) {
    /*
    2N elements with N+1 unique and one that repeats N times.
    That means half the elements are the repeating value so we can check
    adjacent values. If not, it must be [x, x, y, z] or [x, y, z, x] where we
    miss the check between A[0] and A[1]
    */

    for (int i = 2; i < A.size(); i++) {
      if (A[i] == A[i - 1] || A[i] == A[i - 2]) return A[i];
    }
    return A[0];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
965. Univalued Binary Tree
A binary tree is univalued if every node in the tree has the same value.

Return true if and only if the given tree is univalued.

Example 1:

Input: [1,1,1,1,1,null,1]
Output: true

Example 2:

Input: [2,2,2,5,2]
Output: false

Note:

  The number of nodes in the given tree will be in the range [1, 100].
  Each node's value will be an integer in the range [0, 99].
/*
  Submission Date: 2019-02-04
  Runtime: 0 ms
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
  bool isUnivalTree(TreeNode *root) {
    return (root == nullptr) ||
           ((root->left == nullptr || root->left->val == root->val) &&
            (root->right == nullptr || root->right->val == root->val)) &&
               isUnivalTree(root->left) && isUnivalTree(root->right);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
969. Pancake Sorting
Given an array A, we can perform a pancake flip: We choose some positive
integer k <= A.length, then reverse the order of the first k elements of A.  We
want to perform zero or more pancake flips (doing them one after another in
succession) to sort the array A.

Return the k-values corresponding to a sequence of pancake flips that sort A. 
Any valid answer that sorts the array within 10 * A.length flips will be judged
as correct.

Example 1:

Input: [3,2,4,1]
Output: [4,2,4,3]
Explanation:
We perform 4 pancake flips, with k values 4, 2, 4, and 3.
Starting state: A = [3, 2, 4, 1]
After 1st flip (k=4): A = [1, 4, 2, 3]
After 2nd flip (k=2): A = [4, 1, 2, 3]
After 3rd flip (k=4): A = [3, 2, 1, 4]
After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.

Example 2:

Input: [1,2,3]
Output: []
Explanation: The input is already sorted, so there is no need to flip anything.
Note that other answers, such as [3, 3], would also be accepted.

Note:

  1 <= A.length <= 100
  A[i] is a permutation of [1, 2, ..., A.length]
/*
  Submission Date: 2019-02-10
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  take the largest number x at index j and flip j+1 so its at the front
  then flip x so its at the back at the correct location
  O(N^2)
  */
  vector<int> pancakeSort(vector<int>& A) {
    int N = A.size();
    vector<int> res;
    res.reserve(2 * N);
    for (int i = N; i >= 1; i--) {
      auto it = find(A.begin(), A.begin() + i, i);
      res.push_back(it - A.begin() + 1);
      res.push_back(i);
      reverse(A.begin(), it + 1);
      reverse(A.begin(), A.begin() + i);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
970. Powerful Integers
Given two non-negative integers x and y, an integer is powerful if it is equal
to x^i + y^j for some integers i >= 0 and j >= 0.

Return a list of all powerful integers that have value less than or equal to
bound.

You may return the answer in any order.  In your answer, each value should occur
at most once.

Example 1:

Input: x = 2, y = 3, bound = 10
Output: [2,3,4,5,7,9,10]
Explanation:
2 = 2^0 + 3^0
3 = 2^1 + 3^0
4 = 2^0 + 3^1
5 = 2^1 + 3^1
7 = 2^2 + 3^1
9 = 2^3 + 3^0
10 = 2^0 + 3^2

Example 2:

Input: x = 3, y = 5, bound = 15
Output: [2,4,6,8,10,14]

Note:

  1 <= x <= 100
  1 <= y <= 100
  0 <= bound <= 10^6
/*
  Submission Date: 2019-02-05
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> powerfulIntegers(int x, int y, int bound) {
    unordered_set<int> res;
    for (int i = 1; i <= bound; i *= x) {
      for (int j = 1; j <= bound && i + j <= bound; j *= y) {
        res.insert(i + j);
        if (y == 1) break;
      }
      if (x == 1) break;
    }
    return vector<int>(res.begin(), res.end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
973. K Closest Points to Origin
We have a list of points on the plane.  Find the K closest points to the origin
(0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.  The answer is guaranteed to be unique
(except for the order that it is in.)

Example 1:

Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just
[[-2,2]].

Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Note:

  1 <= K <= points.length <= 10000
  -10000 < points[i][0] < 10000
  -10000 < points[i][1] < 10000
/*
  Submission Date: 2019-02-04
  Runtime: 124 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Item {
  int dist, ind;
  Item(int d, int i) : dist(d), ind(i) {}
  bool operator<(const Item& other) const { return dist < other.dist; }
};

class Solution {
 public:
  vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    vector<vector<int>> res;
    res.reserve(K);

    priority_queue<Item> pq;
    for (int i = 0; i < points.size(); i++) {
      pq.emplace(points[i][0] * points[i][0] + points[i][1] * points[i][1], i);
      if (pq.size() > K) pq.pop();
    }

    while (!pq.empty()) {
      res.push_back(points[pq.top().ind]);
      pq.pop();
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
976. Largest Perimeter Triangle
Given an array A of positive lengths, return the largest perimeter of a triangle
with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

Example 1:

Input: [2,1,2]
Output: 5

Example 2:

Input: [1,2,1]
Output: 0

Example 3:

Input: [3,2,3,4]
Output: 10

Example 4:

Input: [3,6,2,3]
Output: 8

Note:

  3 <= A.length <= 10000
  1 <= A[i] <= 10^6
/*
  Submission Date: 2019-02-05
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestPerimeter(vector<int>& A) {
    /*
    triangle inequality formula: sum of two sides greater than the other
    a + b > c
    a + c > b
    b + c > a */
    sort(A.begin(), A.end());
    for (int i = A.size() - 1; i >= 2; i--) {
      // don't need to check A[i] + A[i-1] > A[i-2] and A[i] + A[i-2] > A[i-i]
      // because A[i] >= A[i-2] and A[i] >= A[i-1] and A only consists of
      // numbers > 1
      if (A[i - 1] + A[i - 2] > A[i]) return A[i] + A[i - 1] + A[i - 2];
    }

    return 0;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
977. Squares of a Sorted Array
Given an array of integers A sorted in non-decreasing order, return an array of
the squares of each number, also in sorted non-decreasing order.

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:

  1 <= A.length <= 10000
  -10000 <= A[i] <= 10000
  A is sorted in non-decreasing order.
/*
  Submission Date: 2019-01-26
  Runtime: 132 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& A) {
    int N = A.size();
    vector<int> res(N);
    int i = 0;
    int j = N - 1;
    int wr = N - 1;

    while (i < j && A[i] < 0) {
      if (-A[i] > A[j]) {
        res[wr--] = A[i] * A[i];
        i++;
      } else {
        res[wr--] = A[j] * A[j];
        j--;
      }
    }

    while (j >= i) {
      res[wr--] = A[j] * A[j];
      j--;
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
979. Distribute Coins in Binary Tree
Given the root of a binary tree with N nodes, each node in the tree has node.val
coins, and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to
another.  (The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

Example 1:

Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and
one coin to its right child.

Example 2:

Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root
[taking two moves].  Then, we move one coin from the root of the tree to the
right child.

Example 3:

Input: [1,0,2]
Output: 2

Example 4:

Input: [1,0,0,null,3]
Output: 4

Note:

  1<= N <= 100
  0 <= node.val <= N
/*
  Submission Date: 2019-02-09
  Runtime: 12 ms
  Difficulty: MEDIUM
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
  int ans;

  /*
  dfs returns the number of extra coins there are in this subtree.
  if it is positive then we can move coins up else if it is negative
  we move coins down from parent.
  at the node, the total moves would be the absolute value of the left and right
  subtree's number of extra coins.
  the number of excess coins is the number of coins in the root plus the excess
  amount of the left and right minus one for the root node requiring one.
  */
  int dfs(TreeNode* root) {
    if (root == nullptr) return 0;
    int L = dfs(root->left);
    int R = dfs(root->right);
    ans += abs(L) + abs(R);
    return root->val + L + R - 1;
  }

  int distributeCoins(TreeNode* root) {
    ans = 0;
    dfs(root);
    return ans;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
980. Unique Paths III
On a 2-dimensional grid, there are 4 types of squares:

  1 represents the starting square.  There is exactly one starting square.
  2 represents the ending square.  There is exactly one ending square.
  0 represents empty squares we can walk over.
  -1 represents obstacles that we cannot walk over.

Return the number of 4-directional walks from the starting square to the ending
square, that walk over every non-obstacle square exactly once.

Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation:
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Note:

  1 <= grid.length * grid[0].length <= 20
/*
  Submission Date: 2019-02-20
  Runtime: 16 ms
  Difficulty: HARD
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {-1, 1, 0, 0};
  int N, M, zeros;
  unordered_set<int> s;

 public:
  /*
  count number of zeros and do dfs keep tracking of visited cells
  (don't revisit cells). if reach end point and number of visited
  equals number of zero return 1.
  */
  int dfs(const vector<vector<int>>& grid, int i, int j) {
    int res = 0;
    for (int k = 0; k < 4; k++) {
      int n_i = i + dx[k];
      int n_j = j + dy[k];
      if (0 <= n_i && n_i < N && 0 <= n_j && n_j < M) {
        int key = n_i * M + n_j;
        if (grid[n_i][n_j] == 2 && s.size() == zeros) {
          res += 1;
          continue;
        }
        if (grid[n_i][n_j] != 0 || s.count(key)) continue;
        s.insert(key);
        res += dfs(grid, n_i, n_j);
        s.erase(key);
      }
    }

    return res;
  }

  int uniquePathsIII(vector<vector<int>>& grid) {
    N = grid.size();
    M = grid[0].size();
    s.clear();
    int s_i = -1, s_j = -1;
    zeros = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        zeros += (grid[i][j] == 0);
        if (grid[i][j] == 1) {
          s_i = i;
          s_j = j;
        }
      }
    }
    return dfs(grid, s_i, s_j);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
983. Minimum Cost For Tickets
In a country popular for train travel, you have planned some train travelling
one year in advance.  The days of the year that you will travel is given as an
array days.  Each day is an integer from 1 to 365.

Train tickets are sold in 3 different ways:

  a 1-day pass is sold for costs[0] dollars;
  a 7-day pass is sold for costs[1] dollars;
  a 30-day pass is sold for costs[2] dollars.

The passes allow that many days of consecutive travel.  For example, if we get a
7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

Return the minimum number of dollars you need to travel every day in the given
list of days.

Example 1:

Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation:
For example, here is one way to buy passes that lets you travel your travel
plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4,
..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total you spent $11 and covered all the days of your travel.

Example 2:

Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation:
For example, here is one way to buy passes that lets you travel your travel
plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2,
..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total you spent $17 and covered all the days of your travel.

Note:

  1 <= days.length <= 365
  1 <= days[i] <= 365
  days is in strictly increasing order.
  costs.length == 3
  1 <= costs[i] <= 1000
/*
  Submission Date: 2019-02-12
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  dp[j] is the min cost of days[j] to days[N-1]
  find the first o which days[o] > days[j] + cost_dur[i]
  we can have a new cost of dp[o] + cost[i] or not use the new cost by
  keeping dp[j]

  the inner loop is the costs because we want to try all the costs for
  day[j] to get lowest cost before moving j down.
  */
  int mincostTickets(vector<int>& days, vector<int>& costs) {
    if (days.empty()) return 0;
    int N = days.size();
    vector<int> dp(N, INT_MAX);
    vector<int> cost_dur{1, 7, 30};

    for (int j = N - 1; j >= 0; j--) {
      for (int i = 0; i < costs.size(); i++) {
        int c_d = cost_dur[i];
        auto it = lower_bound(days.begin() + j, days.end(), days[j] + c_d);
        auto it_cost = (it == days.end()) ? 0 : dp[it - days.begin()];
        dp[j] = min(dp[j], costs[i] + it_cost);
      }
    }

    return dp[0];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
984. String Without AAA or BBB
Given two integers A and B, return any string S such that:

  S has length A + B and contains exactly A 'a' letters, and exactly B 'b'
letters;
  The substring 'aaa' does not occur in S;
  The substring 'bbb' does not occur in S.

Example 1:

Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.

Example 2:

Input: A = 4, B = 1
Output: "aabaa"

Note:

  0 <= A <= 100
  0 <= B <= 100
  It is guaranteed such an S exists for the given A and B.
/*
  Submission Date: 2019-02-05
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  always write the most abundant character (greedy) unless last two letters are
  the same
  */
  string strWithout3a3b(int A, int B) {
    string S = "";
    while (A || B) {
      int n = S.size();
      bool same_last_letter = n >= 2 && S[n - 1] == S[n - 2];
      bool write_A = (same_last_letter && S[n - 1] == 'b') ||
                     (!same_last_letter && A >= B);
      if (write_A) {
        A--;
        S.push_back('a');
      } else {
        B--;
        S.push_back('b');
      }
    }

    return S;
  }
};

int main() { return 0; }
