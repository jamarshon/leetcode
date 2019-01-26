
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
819. Most Common Word
Given a paragraph and a list of banned words, return the most frequent word that
is not in the list of banned words. It is guaranteed there is at least one word
that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of
punctuation.  Words in the paragraph are not case sensitive. The answer is in
lowercase.

Example:
Input:
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
Output: "ball"
Explanation:
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent
non-banned word in the paragraph. Note that words in the paragraph are not case
sensitive, that punctuation is ignored (even if adjacent to words, such as
"ball,"), and that "hit" isn't the answer even though it occurs more because it
is banned.
 

Note:

1 <= paragraph.length <= 1000.
1 <= banned.length <= 100.
1 <= banned[i].length <= 10.
The answer is unique, and written in lowercase (even if its occurrences in
paragraph may have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
Different words in paragraph are always separated by a space.
There are no hyphens or hyphenated words.
Words only consist of letters, never apostrophes or other punctuation symbols.
/*
    Submission Date: 2018-06-04
    Runtime:  ms
    Difficulty:
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  string mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_set<string> banned_set(banned.begin(), banned.end());
    unordered_map<string, int> freq;

    stringstream ss(paragraph);
    string temp;

    string res = "";
    while (getline(ss, temp, ' ')) {
      for (int i = 0; i < temp.size(); i++) temp[i] = tolower(temp[i]);
      while (!temp.empty() && !isalpha(temp.back())) temp.pop_back();
      if (banned_set.count(temp)) continue;
      freq[temp]++;
      if (res.empty() || freq[res] < freq[temp]) res = temp;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
821. Shortest Distance to a Character
Given a string S and a character C, return an array of integers representing the
shortest distance from the character C in the string.

Example 1:

Input: S = "loveleetcode", C = 'e'
Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

Note:

S string length is in [1, 10000].
C is a single character, and guaranteed to be in string S.
All letters in S and C are lowercase.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  keep track of last seen C and use that as the distance
  then do it from the back and take the min of this value with the previous
  value
  */
  vector<int> shortestToChar(string S, char C) {
    int N = S.size();
    vector<int> res(N, INT_MAX);

    int last_C_forward = -1;
    int last_C_backward = -1;
    for (int i = 0; i < N; i++) {
      if (S[i] == C) last_C_forward = i;
      if (S[N - i - 1] == C) last_C_backward = N - i - 1;

      if (last_C_forward >= 0) {
        res[i] = min(res[i], i - last_C_forward);
      }

      if (last_C_backward >= 0) {
        res[N - i - 1] = min(res[N - i - 1], last_C_backward - (N - i - 1));
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
824. Goat Latin
A sentence S is given, composed of words separated by spaces. Each word consists
of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language
similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the
word. For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter
and append it to the end, then add "ma". For example, the word "goat" becomes
"oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence,
starting with 1. For example, the first word gets "a" added to the end, the
second word gets "aa" added to the end and so on. Return the final sentence
representing the conversion from S to Goat Latin.

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa
hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each
word. 1 <= S.length <= 150.
/*
    Submission Date: 2018-05-31
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

class Solution {
  unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

 public:
  string toGoatLatin(string S) {
    stringstream ss(S);
    string token;
    string res = "";
    int i = 1;
    while (getline(ss, token, ' ')) {
      if (!res.empty()) res += ' ';
      if (vowels.count(tolower(token[0]))) {
        res += token;
      } else {
        res += token.substr(1) + string(1, token[0]);
      }

      res += "ma" + string(i, 'a');
      i++;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
825. Friends Of Appropriate Ages
Some people will make friend requests. The list of their ages is given
and ages[i] is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following
conditions are true:


    age[B] <= 0.5 * age[A] + 7
    age[B] > age[A]
    age[B] > 100 && age[A] < 100


Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will
not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.


Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.

Example 3:

Input: [20,30,100,110,120]
Output:
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.


 

Notes:


    1 <= ages.length <= 20000.
    1 <= ages[i] <= 120.

/*
    Submission Date: 2018-06-29
    Runtime: 39 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  1 <= ages[i] <= 120
  so have a[i] be the frequency of age i
  for an age i, there should be an age j <= i which can be friends with
  j > 0.5*i + 7     ie. j = 0.5*i + 8
  j must be !(j > 100 && i < 100) note this will never occur as j <= i
  
  so for every person of age i (a[i]) and every person of age j (a[j])
  there can be a[j] * a[i] friend requests made as for a person in j
  can make friend with every person in i (a[i] times) and there are a[j] of
  these people
  
  if j == i, then it is a[i] * (a[i] - 1) as every person in i
  can make friends with a[i] - 1 people as they cannot make friends with
  themself
  */
  int numFriendRequests(vector<int>& ages) {
    vector<int> a(121, 0);

    for (const auto& e : ages) a[e]++;

    int res = 0;
    for (int i = 1; i < 121; i++) {
      for (int j = 0.5 * i + 8; j <= i; j++) res += a[j] * (a[i] - (i == j));
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
830. Positions of Large Groups
In a string S of lowercase letters, these letters form consecutive groups of the
same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx",
"z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting
and ending positions of every large group.

The final answer should be in lexicographic order.

 

Example 1:

Input: "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the single large group with starting  3 and ending
positions 6. Example 2:

Input: "abc"
Output: []
Explanation: We have "a","b" and "c" but no large group.
Example 3:

Input: "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
 

Note:  1 <= S.length <= 1000
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> largeGroupPositions(string S) {
    vector<vector<int>> res;
    for (int i = 0; i < S.size();) {
      int j = i;
      while (j < S.size() && S[i] == S[j]) j++;
      if (j - i >= 3) {
        res.push_back({i, j - 1});
      }
      i = j;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
832. Flipping an Image
Given a binary matrix A, we want to flip the image horizontally, then invert it,
and return the resulting image.

To flip an image horizontally means that each row of the image is reversed.  For
example, flipping [1, 1, 0] horizontally results in [0, 1, 1].

To invert an image means that each 0 is replaced by 1, and each 1 is replaced by
0. For example, inverting [0, 1, 1] results in [1, 0, 0].

Example 1:

Input: [[1,1,0],[1,0,1],[0,0,0]]
Output: [[1,0,0],[0,1,0],[1,1,1]]
Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
Example 2:

Input: [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Notes:

1 <= A.length = A[0].length <= 20
0 <= A[i][j] <= 1
/*
    Submission Date: 2018-05-31
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
    for (auto& row : A) {
      reverse(row.begin(), row.end());
      for (auto& el : row) el ^= 1;
    }

    return A;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
836. Rectangle Overlap
A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the
coordinates of its bottom-left corner, and (x2, y2) are the coordinates of its
top-right corner.

Two rectangles overlap if the area of their intersection is positive.  To be
clear, two rectangles that only touch at the corner or edges do not overlap.

Given two rectangles, return whether they overlap.

Example 1:

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
Example 2:

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
Notes:

Both rectangles rec1 and rec2 are lists of 4 integers.
All coordinates in rectangles will be between -10^9 and 10^9.
/*
    Submission Date: 2018-05-24
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool intersects(int a1, int a2, int b1, int b2) {
    return !(b1 >= a2 || a1 >= b2);
  }

  // Check if x intervals intersect and y intervals intersect
  bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    return intersects(rec1[0], rec1[2], rec2[0], rec2[2]) &&
           intersects(rec1[1], rec1[3], rec2[1], rec2[3]);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
838. Push Dominoes
There are N dominoes in a line, and we place each domino vertically upright.

In the beginning, we simultaneously push some of the dominoes either to the left
or to the right.

After each second, each domino that is falling to the left pushes the adjacent
domino on the left.

Similarly, the dominoes falling to the right push their adjacent dominoes
standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays
still due to the balance of the forces.

For the purposes of this question, we will consider that a falling
domino expends no additional force to a falling or already fallen domino.

Given a string "S" representing the initial state. S[i] = 'L', if the i-th
domino has been pushed to the left; S[i] = 'R', if the i-th domino has been
pushed to the right; S[i] = '.', if the i-th domino has not been pushed.

Return a string representing the final state. 

Example 1:

Input: ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."

Example 2:

Input: "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.

Note:

  0 <= N <= 10^5
  String dominoes contains only 'L', 'R' and '.'
/*
  Submission Date: 2019-01-26
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string pushDominoes(string s) {
    int last_ind = -1;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '.') continue;
      if (s[i] == 'L') {
        if (last_ind == -1 || s[last_ind] == 'L') {
          fill(s.begin() + max(0, last_ind), s.begin() + i, 'L');
        } else {
          int j = 0;
          while (last_ind + j < i - j) {
            s[last_ind + j] = 'R';
            s[i - j] = 'L';
            j++;
          }
        }
      } else if (last_ind != -1 && s[last_ind] != 'L') {
        fill(s.begin() + last_ind, s.begin() + i, 'R');
      }
      last_ind = i;
    }

    if (last_ind != -1 && s[last_ind] == 'R') {
      fill(s.begin() + last_ind, s.end(), 'R');
    }

    return s;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
840. Magic Squares In Grid
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9
such that each row, column, and both diagonals all have the same sum.

Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?
(Each subgrid is contiguous). Example 1:

Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation:
The following subgrid is a 3 x 3 magic square:
438
951
276

while this one is not:
384
519
762

In total, there is only one magic square inside the given grid.
Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
0 <= grid[i][j] <= 15
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool IsMagicSquare(const vector<vector<int>>& grid, int i, int j) {
    unordered_set<int> st;
    vector<int> row_sum(3, 0), col_sum(3, 0);
    int diag1 = 0, diag2 = 0;
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        int e = grid[i + y][j + x];
        if (e < 1 || e > 9 || st.count(e)) return false;
        row_sum[y] += e;
        col_sum[x] += e;
        if (y == x) diag1 += e;
        if (x + y == 2) diag2 += e;
      }
    }

    for (int x = 1; x < 3; x++) {
      if (row_sum[x] != row_sum[x - 1]) return false;
      if (col_sum[x] != col_sum[x - 1]) return false;
    }

    return diag1 == diag2;
  }
  int numMagicSquaresInside(vector<vector<int>>& grid) {
    int N = grid.size();
    int M = grid[0].size();
    int res = 0;
    for (int i = 0; i < N - 2; i++) {
      for (int j = 0; j < M - 2; j++) {
        res += IsMagicSquare(grid, i, j);
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
841. Keys and Rooms
There are N rooms and you start in room 0.  Each room has a distinct number in
0, 1, 2, ..., N-1, and each room may have some keys to access the next room.

Formally, each room i has a list of keys rooms[i], and each key rooms[i][j] is
an integer in [0, 1, ..., N-1] where N = rooms.length.  A key rooms[i][j] = v
opens the room with number v.

Initially, all the rooms start locked (except for room 0).

You can walk back and forth between rooms freely.

Return true if and only if you can enter every room.

Example 1:

Input: [[1],[2],[3],[]]
Output: true
Explanation:
We start in room 0, and pick up key 1.
We then go to room 1, and pick up key 2.
We then go to room 2, and pick up key 3.
We then go to room 3.  Since we were able to go to every room, we return true.
Example 2:

Input: [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can't enter the room with number 2.
Note:

1 <= rooms.length <= 1000
0 <= rooms[i].length <= 1000
The number of keys in all rooms combined is at most 3000.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canVisitAllRooms(vector<vector<int>>& rooms) {
    queue<int> q;
    unordered_set<int> visited;

    q.push(0);
    visited.insert(0);
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      for (auto e : rooms[curr]) {
        if (!visited.count(e)) {
          q.push(e);
          visited.insert(e);
        }
      }
    }

    return visited.size() == rooms.size();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
844. Backspace String Compare
Given two strings S and T, return if they are equal when both are typed into
empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string eval(string s) {
    string res = "";
    for (const auto& c : s) {
      if (c == '#') {
        if (!res.empty()) res.pop_back();
      } else {
        res.push_back(c);
      }
    }
    return res;
  }
  bool backspaceCompare(string S, string T) { return eval(S) == eval(T); }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
846. Hand of Straights
Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W,
and consists of W consecutive cards.

Return true if and only if she can.

 




Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].

Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.

 

Note:


    1 <= hand.length <= 10000
    0 <= hand[i] <= 10^9
    1 <= W <= hand.length

/*
    Submission Date: 2018-07-11
    Runtime: 44 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Solution {
 public:
  /*
  create a frequency map. have a sorted queue of ends and loop through freq map
  if the ends isn't empty (meaning it is a part of some interval) and previous
  value in freq map doesn't equal current value - 1, it means a jump occured
  without interval ending so return false
  
  if the frequency is less than the number of intervals (ends.size()), return
  false as more of this number is needed
  
  if the frequency is greater than the number of intervals, then add this number
  + W - 1 as the end interval and do this freq - number of intervals times.
  
  remove all the ends that equal the current value
  
  finally return if ends is empty meaning all the intervals have been completed.
  */
  bool isNStraightHand(vector<int>& hand, int W) {
    map<int, int> freq;
    for (const auto& h : hand) freq[h]++;
    queue<int> ends;

    pair<int, int> prev = {-1, -1};
    for (const auto& kv : freq) {
      if (prev.first != -1 && kv.first != prev.first + 1 && !ends.empty())
        return false;
      prev = kv;
      int diff = kv.second - ends.size();
      if (diff < 0) return false;  // too many numbers needed
      if (diff > 0) {
        // new ends
        for (int i = 0; i < diff; i++) ends.push(kv.first + W - 1);
      }

      while (!ends.empty() && kv.first == ends.front()) ends.pop();
    }

    return ends.empty();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
849. Maximize Distance to Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents
that the seat is empty.

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest
person to him is maximized.

Return that maximum distance to closest person.

Example 1:

Input: [1,0,0,0,1,0,1]
Output: 2
Explanation:
If Alex sits in the second open seat (seats[2]), then the closest person has
distance 2. If Alex sits in any other open seat, the closest person has
distance 1. Thus, the maximum distance to the closest person is 2. Example 2:

Input: [1,0,0,0]
Output: 3
Explanation:
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Note:

1 <= seats.length <= 20000
seats contains only 0s or 1s, at least one 0, and at least one 1.
/*
    Submission Date: 2018-06-24
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxDistToClosest(vector<int>& seats) {
    if (seats.empty()) return INT_MAX;

    int N = seats.size();
    // left[i] indicates the distance to the closest 1 to the left
    vector<int> left(N, INT_MAX);
    for (int i = 0; i < N; i++) {
      if (seats[i] == 1)
        left[i] = 0;
      else if (i > 0 && left[i - 1] < INT_MAX) {
        left[i] = left[i - 1] + 1;
      }
    }

    int right = INT_MAX;
    int res = INT_MIN;
    /*
    if there is at least one 1 and 0
    left[i] will be INT_MAX until the first 1 then some number after it
    
    hence if starting from the back, the number will not be INT_MAX so right
    will be correctly minimized.
    */
    for (int i = N - 1; i >= 0; i--) {
      if (seats[i] == 1)
        right = 0;
      else if (right < INT_MAX)
        right++;

      res = max(res, min(left[i], right));
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
852. Peak Index in a Mountain Array
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i]
> A[i+1] > ... > A[A.length - 1] Given an array that is definitely a mountain,
return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... >
A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
/*
    Submission Date: 2018-06-24
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& A) {
    int low = 0;
    int high = A.size() - 1;
    while (low <= high - 2) {  // at least 3 elements
      int mid = low + (high - low) / 2;
      if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1]) {
        return mid;

        /*
        a number and the next number has only two conditions < and >
        if < then it is before the peak, so go right
        if > then it is after the peak, so go left
        
        need to include mid in the search as it can be either the left
        or right boundary to the peak
        */
      }
      if (A[mid - 1] < A[mid]) {
        low = mid;
      } else {  // A[mid-1] > A[mid]
        high = mid;
      }
    }

    return -1;
  }
};

int main() { return 0; }