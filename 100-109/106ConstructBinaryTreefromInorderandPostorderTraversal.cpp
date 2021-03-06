/*
106. Construct Binary Tree from Inorder and Postorder Traversal
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-24
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <iostream>
#include <unordered_map>
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
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inorder_val_to_ind;

    int N = postorder.size();

    for (int i = 0; i < N; i++) {
      inorder_val_to_ind[inorder[i]] = i;
    }
    return buildTree(inorder, postorder, inorder_val_to_ind, 0, N, 0, N);
  }
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder,
                      unordered_map<int, int>& inorder_val_to_ind, int in_start,
                      int in_end, int post_start, int post_end) {
    assert(in_end >= in_start && post_end >= post_start);
    assert(in_end - in_start == post_end - post_start);

    if (in_end == in_start) return NULL;

    int root_val = postorder[post_end - 1];
    int left_size = inorder_val_to_ind[root_val] - in_start;
    int right_size = in_end - inorder_val_to_ind[root_val] - 1;

    TreeNode* root = new TreeNode(root_val);
    root->left = buildTree(inorder, postorder, inorder_val_to_ind, in_start,
                           inorder_val_to_ind[root_val], post_start,
                           post_start + left_size);
    root->right = buildTree(inorder, postorder, inorder_val_to_ind,
                            inorder_val_to_ind[root_val] + 1, in_end,
                            post_start + left_size, post_end - 1);
    return root;
  }
};

int main() { return 0; }