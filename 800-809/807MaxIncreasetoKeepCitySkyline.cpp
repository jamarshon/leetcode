/*
807. Max Increase to Keep City Skyline
In a 2 dimensional array grid, each value grid[i][j] represents the height of a
building located there. We are allowed to increase the height of any number of
buildings, by any amount (the amounts can be different for different buildings).
Height 0 is considered to be a building as well.

At the end, the "skyline" when viewed from all four directions of the grid, i.e.
top, bottom, left, and right, must be the same as the skyline of the original
grid. A city's skyline is the outer contour of the rectangles formed by all the
buildings when viewed from a distance. See the following example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation:
The grid is:
[ [3, 0, 8, 4],
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

Notes:

1 < grid.length = grid[0].length <= 50.
All heights grid[i][j] are in the range [0, 100].
All buildings in grid[i][j] occupy the entire grid cell: that is, they are a 1 x
1 x grid[i][j] rectangular prism.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int N = grid.size();
    int M = grid[0].size();
    vector<int> max_col(M, 0), max_row(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        max_col[j] = max(max_col[j], grid[i][j]);
        max_row[i] = max(max_row[i], grid[i][j]);
      }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        res += min(max_col[j], max_row[i]) - grid[i][j];
      }
    }

    return res;
  }
};

int main() { return 0; }