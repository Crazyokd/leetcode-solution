#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<string>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        // pre process
        path += '/';

        int pre = 1;
        stack<string> sta;
        for (int i = 1; i < path.size(); i++) {
            if (path[i] == '/') {
                if (path[i-1] != '/') {
                    string s =  path.substr(pre, i-pre);
                    sta.push(s);
                }
                pre = i + 1;
            }
        }

        string res = "";
        // construct result
        int back_cnt  = 0;  // 回退次数
        while (!sta.empty()) {
            string top = sta.top();
            sta.pop();

            if (top == ".") continue;
            if (top == "..") {
                back_cnt++;
                continue;
            } 
            if (back_cnt > 0) {
                back_cnt--;
                continue;
            }
            res = "/" + top + res;
        }
        return res == "" ? "/" : res;
    }

    int minDistance(string word1, string word2) {
        // init
        vector<int> initRes(word1.size()+1, 0);
        vector<vector<int>> res(word2.size()+1, initRes);
        
        for (int i = 0; i < res[0].size(); i++) {
            res[0][i] = i;
        }
        for (int i = 0; i < res.size(); i++) {
            res[i][0] = i;
        }
        
        // dp
        for (int i = 1; i <= word2.size(); i++) {
            for (int j = 1; j <= word1.size(); j++) {
                res[i][j] = res[i-1][j-1] + (word1[j-1] == word2[i-1] ? 0 : 1);
                res[i][j] = min(res[i][j], min(res[i-1][j], res[i][j-1])+1);
    }
        }
        return res[word2.size()][word1.size()];
    }

    void setZeroes(vector<vector<int>>& matrix) {
        int row_size = matrix.size();
        int col_size = matrix[0].size();
        vector<bool> row(row_size, false), col(col_size, false);
        for (int i = 0; i < row_size; i++) {
            for (int j = 0; j < col_size; j++) {
                if (!matrix[i][j]) {
                    row[i] = true;
                    col[j] = true;
                }
            }
        }
        
        for (int i = 0; i < row_size; i++) {
            for (int j = 0; j < col_size; j++) {
                if (row[i] || col[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // binary search last column
        int low = 0, high = matrix.size() - 1, lastColIndex = matrix[0].size() - 1;
        while (high > low) {
            int mid = low + ((high-low) >> 1);
            if (matrix[mid][lastColIndex] >= target) {
                high = mid;
            }else {
                low = mid+1;
            }
        }
        int row = low;
        low = 0, high = lastColIndex;
        // binary search one row
        while (high >= low) {
            int mid = low + ((high-low) >> 1);
            if (matrix[row][mid] == target) return true;
            if (matrix[row][mid] > target) {
                high = mid - 1;
            }else {
                low = mid + 1;
            }
        }
        return false;
    }

    void sortColors(vector<int>& nums) {
        sort(nums.begin(), nums.end());
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur;
        combineHelper(1, 0, cur, res, n, k);
        return res;
    }
    void combineHelper(int deepth, int pre, vector<int> &cur, vector<vector<int>>& res, int n, int k) {
        if (deepth > k){
            res.push_back(cur);
            return;
        }
        for (int i = pre+1; i <= n-(k-deepth) ; i++){
            cur.push_back(i);
            combineHelper(deepth+1, i, cur, res, n, k);
            cur.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i <= len; i++) {
            vector<int> cur;
            subsetsHelper(1, 0, nums, cur, res, i);
        }    
        return res;
    }
    void subsetsHelper(int deepth, int index, vector<int> nums, vector<int> &cur, vector<vector<int>>& res, int k) {
        if (deepth > k){
            res.push_back(cur);
            return;
        }
        for (int i = index; i < nums.size(); i++){
            cur.push_back(nums[i]);
            vector<int> tmp(nums);
            tmp.erase(tmp.begin()+i);
            subsetsHelper(deepth+1, i, tmp, cur, res, k);
            cur.pop_back();
        }
    }

    int removeDuplicates(vector<int>& nums) {
        int freq = 1, res = nums.size();
        for (int i = 1; i < res; i++) {
            if (nums[i] == nums[i-1]) {
                if (freq+1 > 2) {
                    nums.erase(nums.begin()+i);
                    res--;
                    i--;
                    
                }
                freq = 2;
            }else {
                freq = 1;
            }
            
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,2,3};
    s.subsets(nums);
    
    // cout << s.simplifyPath("/../") << endl;
    // cout << s.simplifyPath("/home/") << endl;
    cout << s.simplifyPath("/home//foo") << endl;
    cout << s.simplifyPath("/a/./b/../../c/") << endl;
    return 0;
}