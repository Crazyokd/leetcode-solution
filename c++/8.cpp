#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>

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

    unordered_map <char, int> ori,cnt;
    bool check() {
        for (const auto &p : ori) {
            if (cnt[p.first] < p.second) return false;
        }
        return true;
    }
    string minWindow(string s, string t) {
        // init
        for (const auto &c : t) {
            ori[c]++;
        }

        int left = 0, right = -1;
        int s_size = s.size();
        int ansL = -1, ansLen = INT_MAX;
        while (++right < s_size) {
            if (ori.find(s[right]) != ori.end()) {
                cnt[s[right]]++;
            }
            while (check() && left <= right) {
                if (right - left + 1 < ansLen) {
                    ansLen = right - left + 1;
                    ansL = left;
                }
                if (ori.find(s[left]) != ori.end()) {
                    --cnt[s[left]];
                }
                ++left;
            }
        }
        return ansL == -1 ? "" : s.substr(ansL, ansLen);

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

    vector<vector<bool>> visited;
    bool exist(vector<vector<char>>& board, string word) {
        // 初始化访问vector
        vector<bool> init_visited(board[0].size(), false);
        visited = vector<vector<bool>>(board.size(), init_visited);
        // 遍历加bfs
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == word[0]) {
                    visited[i][j] = true;
                    if (bfs(board, i, j, word, 1))
                        return true;
                    visited[i][j] = false;
                }
            }
        }
        return false;
    }
    bool bfs(vector<vector<char>>& board, int row, int col, string word, int index) {
        if (index == word.size()) return true;
        // 上下左右
        int row_change[] = {-1, 1, 0, 0};
        int col_change[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newRow = row + row_change[i];
            int newCol = col + col_change[i];
            if (check(board, newRow, newCol, board.size(), board[0].size(), word[index])) {
                if (bfs(board, newRow, newCol, word, index+1)) {
                    return true;
                }
                visited[newRow][newCol] = false;
            }
            
        }
        return false;
    }
    bool check(vector<vector<char>>& board, int newRow, int newCol, int maxRow, int maxCol, char c) {
        if (newRow >= 0 && newRow < maxRow && newCol >=0 && newCol < maxCol) {
            if (!visited[newRow][newCol] && board[newRow][newCol] == c) {
                visited[newRow][newCol] = true;
                return true;
            }
        } 
        return false;
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