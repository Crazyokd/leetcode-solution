#include<iostream>
#include<vector>
#include<queue>

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

    bool isSymmetric(TreeNode* root) {
        return !root || helper(root->left,root->right);
    }
    bool helper(TreeNode* left,TreeNode* right){
        if(!left && !right)return true;
        if(!left || !right)return false;
        if(left->val != right->val)return false;
        return helper(left->left,right->right)&&helper(left->right,right->left);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) return res;

        queue<TreeNode*> q;
        q.push(root);

        int lay_cnt = 1;
        while(!q.empty()) {
            vector<int> layer_res;
            int new_lay_cnt = 0;
            for (int i = 0; i < lay_cnt; i++) {
                TreeNode* node = q.front();
                q.pop();
                layer_res.emplace_back(node->val);
                if (node->left != NULL) {
                    q.push(node->left);
                    new_lay_cnt++;
                }
                if (node->right != NULL) {
                    q.push(node->right);
                    new_lay_cnt++;
                }
            }
            lay_cnt = new_lay_cnt;
            res.emplace_back(layer_res);
        }
        return res;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) return res;

        queue<TreeNode*> q;
        q.push(root);

        bool traversal_order = false;
        int lay_cnt = 1;
        while(!q.empty()) {
            vector<int> layer_res;
            int new_lay_cnt = 0;
            for (int i = 0; i < lay_cnt; i++) {
                TreeNode* node = q.front();
                q.pop();
                layer_res.emplace_back(node->val);
                if (node->left != NULL) {
                    q.push(node->left);
                    new_lay_cnt++;
                }
                if (node->right != NULL) {
                    q.push(node->right);
                    new_lay_cnt++;
                }
            }
            lay_cnt = new_lay_cnt;
            if (traversal_order) {
                int len = layer_res.size();
                vector<int> reverse_layer_res(len);
                for (int i = 0; i < len; i++) {
                    reverse_layer_res[len-i-1] = layer_res[i];
                }
                res.emplace_back(reverse_layer_res);
            } else {
                res.emplace_back(layer_res);
            }
            traversal_order = traversal_order ? false : true;   
        }
        return res;
    }

    int maxDepth(TreeNode* root) {
        return root?max(maxDepth(root->left),maxDepth(root->right))+1:0;
    }    
};

int main() {
    vector<int> nums;
    return 0;
}