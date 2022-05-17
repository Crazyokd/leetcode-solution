#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>

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
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int minn = prices[0];
        for (int i = 0; i < prices.size(); i++) {
            minn = min(minn, prices[i]);
            res = max(res, prices[i]-minn);
        }
        return res;
    }

    int maxProfitII(vector<int>& prices) {
        int minn = prices[0];
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > minn) {
                res += prices[i] - minn;
                minn = prices[i];
            } else {
                minn = min(prices[i], minn);
            }
        }
        return res;
    }

    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/solution/mai-mai-gu-piao-de-zui-jia-shi-ji-iii-by-wrnt/
    int maxProfitIII(vector<int>& prices) {
        int n = prices.size();
        int buy1 = -prices[0], sell1 = 0;
        int buy2 = -prices[0], sell2 = 0;
        for (int i = 1; i < n; ++i) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }

    int res = -30000000;
    int maxPathSum(TreeNode* root) {
        maxPathSumHelper(root);
        return res;
    }
    int maxPathSumHelper(TreeNode* root) {
        if (root == NULL) return 0;

        int leftVal = maxPathSumHelper(root->left);
        int rightVal = maxPathSumHelper(root->right);

        int retVal = root->val + max(max(leftVal, rightVal), 0);
        res = max(res, max(retVal, root->val+leftVal+rightVal));
        return max(0, retVal);
    }

    bool isPalindrome(string s) {
        string newS = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9' || s[i] >= 'a' && s[i] <= 'z')
                newS += s[i];
            if (s[i] >= 'A' && s[i] <= 'Z')
                newS += s[i]+32;
        }
        int len = newS.size();
        for (int i = 0; i < len/2; i++) {
            if (newS[i] != newS[len-i-1])
                return false;
        }
        return true;
    }

// private:
//     vector<vector<string>> res = vector<vector<string>>();
//     vector<bool> flags;
// public:
//     vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//         sort(wordList.begin(), wordList.end());
//         wordList.resize(unique(wordList.begin(), wordList.end()) - wordList.begin());
//         int size = wordList.size();
//         flags = vector<bool>(size, false);

//         vector<string> cur_res = vector<string>();
//         BFS(beginWord, endWord, 1, size, cur_res, wordList);
//         return res;
//     }
//     void BFS(string cur, string &endWord, int depth, int &maxDepth, vector<string> cur_res, vector<string> & wordList) {
//         int pre_size = (!res.empty() ? res[0].size() : maxDepth);

//         if (depth > pre_size) {
//             return;
//         }

//         cur_res.emplace_back(cur);
//         // 找到一个答案
//         if (cur == endWord) {
//             // 当前答案更优
//             if (pre_size > cur_res.size()) {
//                 res.clear();
//             } 
//             res.emplace_back(cur_res);
//             return;
//         }

//         // main algorithm 
//         for (int i = 0; i < maxDepth; i++) {
//             string next = wordList[i];
//             if (!flags[i] && check(cur, next)) {
//                 flags[i] = true;
//                 BFS(next, endWord, depth + 1, maxDepth, cur_res, wordList);
//                 flags[i] = false;
//             }
//         } 
//     }
//     bool check(string str1, string str2) {
//         int cnt = 0;
//         for(int i = 0; i < str1.size(); i++) {
//             if (str1[i] != str2[i] && cnt++) {
//                 return false;
//             }
//         }
//         return true;
//     }

    int longestConsecutive(vector<int>& nums) {
        // 去重
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;           
    }

    
};

int main() {
    Solution s;
    vector<int> prices = {3,3,5,0,0,3,1,4};
    s.maxProfitIII(prices);
    
    return 0;
}