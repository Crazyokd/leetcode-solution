#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        vector<int> res;
        res.emplace_back(1);
        res.emplace_back(1);
        for (int i = 1; i < s.size(); i++) {
            int t = 0;
            // 存在两种情况
            if (s[i-1] != '0' && atoi(s.substr(i-1, 2).c_str()) <= 26) {
                t += res[i-1];
            }
            if (s[i] != '0') {
                t += res[i];
            }
            res.emplace_back(t);
        }
        return res.back();
    }

    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head -> next == NULL || left == right) return head;
        int cnt = 0;
        ListNode *node_left = new ListNode();
        node_left -> next = head;
        while (++cnt < left) {
            node_left = node_left->next;
        }

        ListNode *node_right = node_left->next;
        while (cnt++ <= right) {
            node_right = node_right->next;
        }

        ListNode *pre = node_right;
        ListNode *next = node_left->next;
        while (next != node_right) {
            ListNode *tmp = next->next;
            next -> next = pre;
            pre = next;
            next = tmp;
        }

        bool flag = node_left->next == head; // 判断head节点是否反转
        node_left->next = pre;

        return flag ? node_left->next : head;
    }

    bool check(string ip) {
        if (!ip.size() || ip.size() > 3) return false;
        if (ip[0] == '0') {
            if (ip.size() == 1) return true;
            else return false;
        }
        int ip_value = atoi(ip.c_str());

        if (ip_value < 256) return true;
        return false;
    }
    void DFS(int deepth, string cur_ip, string t_ans, vector<string>& ans) {
        if (deepth == 4) {
            if (check(cur_ip)) {
                ans.push_back((t_ans+"."+cur_ip).substr(1));
            } 
            return ;
        }

        int len = cur_ip.size();
        if (len > 0 && check(cur_ip.substr(0, 1))) {
            DFS(deepth+1, cur_ip.substr(1), t_ans+"."+cur_ip.substr(0, 1), ans);
        }
        if (len > 1 && check(cur_ip.substr(0, 2))) {
            DFS(deepth+1, cur_ip.substr(2), t_ans+"."+cur_ip.substr(0, 2), ans);
        }
        if (len > 2 && check(cur_ip.substr(0, 3))) {
            DFS(deepth+1, cur_ip.substr(3), t_ans+"."+cur_ip.substr(0, 3), ans);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        DFS(1, s, "", ans);
        return ans;
    }

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inorderTraversalDFS(root, ans);
        return ans;
    }

    void inorderTraversalDFS(TreeNode* root, vector<int>& ans) {
        if (root == NULL) return;

        inorderTraversalDFS(root->left, ans);
        ans.push_back(root->val);
        inorderTraversalDFS(root->right, ans);
    }

    vector<TreeNode*> generateTrees(int n) {
        return generateTreesHelper(1, n);
    }
    vector<TreeNode*> generateTreesHelper(int start, int end) {
        if (start > end) {
            return {NULL};
        }

        vector<TreeNode*> res;
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> left = generateTreesHelper(start,i-1);
            vector<TreeNode*> right = generateTreesHelper(i+1, end);


            for (auto left_tree : left) {
                for (auto right_tree : right) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left_tree;
                    root->right = right_tree;
                    res.emplace_back(root);
                }
            }
        }    
        return res;
    }

    int numTrees(int n) {
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        return calculateTreesNum(1, n, dp);
    }

    int calculateTreesNum(int start, int end, vector<vector<int>>& dp) {
        if (start > end) {
            return 1;
        }
        if (dp[start][end]) {
            return dp[start][end];
        }
        
        int res = 0;
        for (int i = start; i <= end; i++) {
            res += calculateTreesNum(start, i-1, dp) * calculateTreesNum(i+1, end, dp);
        }
        return dp[start][end] = res;
    }

    bool isInterleave(string s1, string s2, string s3) {
        int o = s1.size(), p = s2.size(), q = s3.size();
        if (o+p != q) return false;

        const int N = 105;
        bool dp[N][N] = {0};

        dp[0][0] = true;
        for (int i = 0; i <= o; i++) {
            for (int j = 0; j <= p; j++) {
                // dp[i][j] 表示 s1 的前i个 和 s2 的前j个与 s3 的前 i+j 个交错匹配。
                int k = i+j-1;
                dp[i][j] |= (i > 0 && s3[k] == s1[i-1] && dp[i-1][j]);
                dp[i][j] |= (j > 0 && s3[k] == s2[j-1] && dp[i][j-1]);
            }
        }
        return dp[o][p];
    }

    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        long MAXX = 0x7FFFFFFF;
        return checkIsValidBST(root, ~(MAXX+2)+1, MAXX+1);    
    }
    bool checkIsValidBST(TreeNode* root, long minn, long maxx) {
        return (root->left == NULL || (root->left->val < root->val && root->left->val > minn && checkIsValidBST(root->left, minn, root->val))) && 
            (root->right == NULL || (root->right->val > root->val && root->right->val < maxx && checkIsValidBST(root->right, root->val, maxx)));
    }

    // 行不通
    // void recoverTree(TreeNode* root) {
    //     traverse(root);
    // }
    // bool traverse(TreeNode* root) {
    //     while (root != NULL){
    //         return !recoverTreeHelper(root->left, root, true) || !recoverTreeHelper(root->right, root, false) || traverse(root->left) || traverse(root->right);
    //     }
    //     return true;
    // }
    // bool recoverTreeHelper(TreeNode* root, TreeNode* rRoot, bool flag) {
    //     if (root == NULL) return true;
    //     if (flag && root->val >= rRoot->val || !flag && root->val <= rRoot->val){
    //         int t = root->val;
    //         root->val = rRoot->val;
    //         rRoot->val = t;
    //         return false;
    //     }
        
    //     return recoverTreeHelper(root->left, rRoot, flag) && recoverTreeHelper(root->right, rRoot, flag); 
    // }
    
    // 考察二叉搜索树与中序遍历的关系
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nums;
        // get the result of inorderTraversal
        inorderTraversal(root, nums);

        int swap_1 = -1, swap_2 = -1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i]->val <= nums[i-1]->val) {
                if (swap_1 < 0) {
                    swap_1 = i-1;
                } else {
                    swap_2 = i;
                }
            }
        }
        if (swap_2 < 0) 
            // 交换点相邻
            swap_2 = swap_1 + 1;
        // 交换
        int t = nums[swap_1]->val;
        nums[swap_1]->val = nums[swap_2]->val;
        nums[swap_2]->val = t;
    }
    void inorderTraversal(TreeNode *root, vector<TreeNode*>& nums) {
        if (root == NULL) return;
        
        inorderTraversal(root->left, nums);
        nums.emplace_back(root);
        inorderTraversal(root->right, nums);
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p != NULL || q != NULL) {
            if (p == NULL || q == NULL) return false;

            if (p->val != q->val) return false;
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right); 
        }
        return true;
    }
};

int main() {
    Solution s = Solution();
    s.numTrees(10);
    return 0;
}