#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

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

    void flatten(TreeNode* root) {
        if (root == NULL) return;
        flattenHelper(root);
    }
    TreeNode* flattenHelper(TreeNode* root) {
        TreeNode *right = root->right;
        root->right = root->left;
        root->left = NULL;

        if (root->right != NULL) {
            root = flattenHelper(root->right);
        }
        root->right = right;
        if (right != NULL) {
            root = flattenHelper(root->right);
        }
        return root;
    }

    // // 使用递归 时间复杂度过不去
    // int len_s;
    // int len_t;
    // int numDistinct(string s, string t) {
    //     len_s = s.size();
    //     len_t = t.size();
    //     return numDistinctHelper(0, 0, s, t);
    // }
    // int numDistinctHelper(int index_s, int index_t, string& s, string& t) {
    //     if (index_t >= len_t) return 1;
    //     if (index_s >= len_s) return 0;
        
    //     return numDistinctHelper(index_s+1, index_t, s, t) + 
    //         (s[index_s] == t[index_t] ? numDistinctHelper(index_s+1, index_t+1, s, t) : 0);
    // }

    int numDistinct(string s, string t) {
        if (t == "") return 1;
        int len_s = s.size();
        int len_t = t.size();

        vector<vector<long>> dp(len_t+1, vector<long>(len_s+1, 0));
        int res = 0;
        for (int i = 0; i < len_t; i++) {
            long cnt = 0, k = 0;
            for (int j = i; j <= len_s - (len_t - i); j++) {
                // t[i] 与 s[j] 匹配
                if (t[i] == s[j]) {
                    if (i == 0) {
                        dp[i][j] = 1;
                    } else {
                        for (; k < j; k++) {
                            cnt += dp[i-1][k];
                        }
                        dp[i][j] = cnt;
                    }
                }
            }
        }
        for (int i = len_t-1; i < len_s; i++) {
            res += dp[len_t-1][i];
        }
        return res;
    }      
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    root->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    Solution s;
    s.flatten(root);

    s.numDistinct( "babgbag", "");

    return 0;
}