/*
341. Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be
integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements
returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements
returned by next should be: [1,4,6].
/*
    Submission Date: 2018-05-02
    Runtime: 19 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

class NestedInteger {
 public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const;

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const;
};

class NestedIterator {
 public:
  stack<pair<int, const vector<NestedInteger>*>> stk;
  vector<NestedInteger> cp;
  NestedIterator(vector<NestedInteger>& nestedList) {
    cp = nestedList;
    stk.emplace(0, &cp);
  }

  void traverse() {
    while (!stk.empty()) {
      int ind;
      const vector<NestedInteger>* v;
      tie(ind, v) = stk.top();
      stk.pop();
      if (ind < v->size()) {
        if (v->at(ind).isInteger()) {
          stk.emplace(ind, v);
          return;
        } else {
          stk.emplace(ind + 1, v);
          stk.emplace(0, &(v->at(ind).getList()));
        }
      }
    }
  }

  int next() {
    traverse();

    int ind;
    const vector<NestedInteger>* v;
    tie(ind, v) = stk.top();
    stk.pop();
    stk.emplace(ind + 1, v);

    return v->at(ind).getInteger();
  }

  bool hasNext() {
    traverse();
    return !stk.empty();
  }
};

int main() { return 0; }