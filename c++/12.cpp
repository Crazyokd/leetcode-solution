#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int minDepth = ~(1 << 31);
        getMinDepth(root, 1, minDepth);
        return minDepth;
    }
    void getMinDepth(TreeNode* root, int curDepth, int& minDepth) {
        if (root == NULL || curDepth >= minDepth) return;
        if (root -> left == NULL && root->right == NULL) {
            minDepth = min(minDepth, curDepth);
        }

        getMinDepth(root->left, curDepth+1, minDepth);
        getMinDepth(root->right, curDepth+1, minDepth);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return checkHasPathSum(root, 0, targetSum);
    }
    bool checkHasPathSum(TreeNode* root, int curSum, int& targetSum) {
        if (root == NULL) return false;

        curSum += root->val;
        if (root->left == NULL && root->right == NULL) {
            if (curSum == targetSum) 
                return true;
            return false;
        }

        return checkHasPathSum(root->left, curSum, targetSum) || checkHasPathSum(root->right, curSum, targetSum);
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        vector<int> curPath;
        getAllPathSum(root, 0, targetSum, curPath, res);
        return res;
    }
    void getAllPathSum(TreeNode* root, int curSum, int& targetSum, vector<int> curPath, vector<vector<int>>& res) {
        if (root == NULL) return;

        curSum += root->val;
        curPath.emplace_back(root->val);

        if (root->left == NULL && root->right == NULL) {
            if (curSum == targetSum) 
                res.emplace_back(curPath);
            return;
        }

        getAllPathSum(root->left, curSum, targetSum, curPath, res);
        getAllPathSum(root->right, curSum, targetSum, curPath, res);
    }
};

int main() {
    return 0;
}