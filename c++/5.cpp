#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>
#include<unordered_map>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0;i < n;i++)if (nums[i] <= 0)nums[i] = n + 1;
        for (int i = 0;i < n;i++)
            if (abs(nums[i]) <= n && nums[abs(nums[i])-1] > 0)nums[abs(nums[i])-1] *= -1;
        for (int i = 0;i < n;i++)if (nums[i] > 0)return i+1;
        return n+1;
    }

    int trap(vector<int>& height) {
        int len = height.size();
        vector<int> leftMaxHeight(len), rightMaxHeight(len);
        // init 
        leftMaxHeight[0] = height[0];
        rightMaxHeight[len-1] = height[len-1];

        for (int i = 1; i < len; i++) {
            leftMaxHeight[i] = max(leftMaxHeight[i-1], height[i]);
        }
        for (int i = len-2; i >= 0; i--) {
            rightMaxHeight[i] = max(rightMaxHeight[i+1], height[i]);
        }

        // get result
        int res = 0;
        for (int i = 1; i < len-1; i++) {
            res += min(rightMaxHeight[i], leftMaxHeight[i]) - height[i];
        }
        return res;
    }
    
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")return "0";
        vector<int> res(num1.size()+num2.size(), 0);
 
        for (int i = num1.size()-1; i >= 0; i--){
            for (int j = num2.size()-1; j >= 0; j--){
                res[i+j+1] += (num1[i]-'0')*(num2[j]-'0');
                res[i+j] += res[i+j+1]/10;
                res[i+j+1] %= 10;
            }
        }
        int i = 0;
        string ans = "";
        while (res[i] == 0) i++;
        while (i < res.size()) ans += to_string(res[i++]);
        
        return ans;
    }

    // 不够好
    // bool isMatch(string s, string p) {
    //     return matchHelper(s, 0, p, 0);
    // }
    // bool matchHelper(string s, int index_s, string p, int index_p) {
    //     if (index_s == s.size()) {
    //         if (index_p == p.size() || p[index_p] == '*'){
    //             for (int i = index_p+1; i < p.size(); i++) {
    //                 if (p[index_p] != '*') return false;
    //             }
    //             return true;
    //         }
    //         return false;
    //     }
    //     if (index_p < p.size()) {
    //         if (p[index_p] == '*')
    //             // 可以选择匹配或不匹配
    //             return matchHelper(s, index_s+1, p, index_p) || matchHelper(s, index_s, p, index_p+1);

    //         if (s[index_s] == p[index_p] || p[index_p] == '?') 
    //             return matchHelper(s, index_s+1, p, index_p+1);
    //     }
        
    //     return false;
    // }

    int jump(vector<int>& nums) {
        if (nums.size() == 1)return 0;
        // 初始化
        vector<int> res(nums.size(), 10005);
        res[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for(int j = i+1; j <= i+nums[i]; j++){
                res[j] = min(res[j], res[i]+1);
                if (j == nums.size()-1)return res[j];
            }
        }
        return -1;
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> tmp;
        vector<vector<int>> res;
        permuteHelper(nums, tmp, res);
        return res;
    }
    void permuteHelper(vector<int> nums, vector<int> tmp, vector<vector<int>> &res) {  
        if (nums.empty()) {
            res.push_back(tmp);
            return;
        }
        // dfs
        for (int i = 0; i < nums.size(); i++) {
            tmp.push_back(nums[i]);
            // through copy to store origin data
            vector<int> numsCopy(nums);
            numsCopy.erase(numsCopy.begin()+i);
            permuteHelper(numsCopy, tmp, res);
            // reduct
            tmp.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> tmp;
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        permuteUniqueHelper(nums, tmp, res);
        return res;
    }
    void permuteUniqueHelper(vector<int> nums, vector<int> tmp, vector<vector<int>> &res) {  
        if (nums.empty()) {
            res.push_back(tmp);
            return;
        }
        // dfs
        int flag = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == flag)continue;
            flag = nums[i];
            tmp.push_back(nums[i]);
            // through copy to store origin data
            vector<int> numsCopy(nums);
            numsCopy.erase(numsCopy.begin()+i);
            permuteUniqueHelper(numsCopy, tmp, res);
            // reduct
            tmp.pop_back();
        }
    }

    void rotate(vector<vector<int>>& matrix) {
        vector<vector<int>> matrixCopy(matrix);
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int  j = 0; j < n; j++) {
                matrix[i][j] = matrixCopy[n-j-1][i];
            }
        }
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;

    }

    double myPow(double x, int n) {
        return pow(x,n);
    }
};

int main() {
    Solution s;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    s.permuteUnique(nums);
    // cout << s.isMatch("abcabczzzde", "*abc???de*") << endl;
    // cout << s.isMatch("acdcb", "a*c?b") << endl;
    // cout << s.isMatch("ab", "?*") << endl;
    cout << s.isMatch("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*ab***ba**b*b*aaab*b") << endl;;
    return 0;
}
