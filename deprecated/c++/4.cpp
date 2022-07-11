#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<string>

using namespace std;

class Solution {
public:
    // https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/
    void nextPermutation(vector<int>& nums) {
        int swapPoint = -1;
        for (int i = nums.size()-1; i > 0; i--){
            if (nums[i] > nums[i-1]) {
                swapPoint = i-1;
                break;
            }
        }
        if (swapPoint >= 0) {
            for (int i = nums.size()-1; i > swapPoint; i--) {
                if (nums[i] > nums[swapPoint]) {
                    int t = nums[i];
                    nums[i] = nums[swapPoint];
                    nums[swapPoint] = t;
                    break;
                }
            }
        }
        sort(nums.begin()+swapPoint+1, nums.end());
        
    }

    int longestValidParentheses(string s) {
        int res = 0;
        vector<int> dp(s.size() + 1, 0);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ')' && i > 0) {
                if (s[i-1] == '(') {
                    dp[i+1] = dp[i-1] + 2;
                } else if (i-dp[i]-1 >= 0 && s[i-dp[i]-1] == '('){
                    dp[i+1] = dp[i] + dp[i-dp[i]-1] + 2;
                }
                res = max(res, dp[i+1]);
            }
        }
        return res;
    }
    int longestValidParentheses2(string s) {
        stack<int> sta;
        int res = 0;
        // init
        sta.push(-1);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                sta.push(i);
            } else {
                sta.pop();
                if (sta.empty()) {
                    sta.push(i); // 放入最后一个未被匹配的索引
                } else {
                    res = max(res, i - sta.top());
                }
            }
        }
        return res;
    }

    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target)return mid;
            printf("%d %d %d\n",low, mid, high);
            // exist pivot
            if (nums[mid] > nums[low]) {
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                }else {
                    low = mid + 1;
                }
            }else if (nums[mid] < nums[high]) {
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                }else {
                    high = mid - 1;
                }
            }else {
                if (nums[low] == nums[mid]) {
                    low++;
                }
                if (nums[high] == nums[mid]) {
                    high--;
                }
            }
        }
        return -1;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        // 使用二分找到target
        int index = getIndex(nums, target);
        // 对第一个index查找得到结果
        if (index < 0) {
            res.push_back(-1);
            res.push_back(-1);
        }else {
            int low = index - 1, high = index + 1;
            while (low >= 0 && nums[low] == target) low--;
            while (high < nums.size() && nums[high] == target) high++;
            res.push_back(low+1);
            res.push_back(high-1);
        }
        return res;
    }
    int getIndex(vector<int>& nums, int target) {
        // 使用二分找到target
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) {
                high = mid - 1;
            }else {
                low = mid + 1;
            }
        }
        return -1;
    }
    int searchInsert(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while(high > low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                low = mid + 1;
            }else {
                high = mid;
            }
        }
        return nums[high] < target ? high + 1 : high;
    }
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<bool> initVec(10, false);
        vector<vector<bool>> rowbuf(9, initVec);
        vector<vector<bool>> colbuf(9, initVec);
        vector<vector<bool>> boxbuf(9, initVec);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                if (rowbuf[i][num] || colbuf[j][num] || boxbuf[i/3*3+j/3][num]) return false;
                rowbuf[i][num] = true;
                colbuf[j][num] = true;
                boxbuf[i/3*3+j/3][num] = true;
            }
        }
        return true;
    }

    bool row[9][9];
    bool col[9][9];
    bool block[9][9];

    void solveSudoku(vector<vector<char>>& board) {
       vector<pair<int, int>> spaces;
       // init
       for (int i = 0; i < board.size(); i++) {
           for (int j = 0; j < board[i].size(); j++) {
               if (board[i][j] == '.') {
                   spaces.emplace_back(i,j);
               } else {
                   int value = board[i][j] - '0' - 1; // 因为索引以0开始
                   row[i][value] = true;
                   col[j][value] = true;
                   block[i/3*3 + j/3][value] = true;
               }
           }
       } 
       SudokuDFS(board, spaces, 0);
    }
    bool SudokuDFS(vector<vector<char>>& board, vector<pair<int, int>>& spaces, int deepth) {
        if (deepth == spaces.size()) {
            return true;
        }
        auto [i, j] = spaces[deepth];
        for (int digit = 0; digit < 9; digit++) {
            if (!row[i][digit] && !col[j][digit] && !block[i/3*3 + j/3][digit]) {
                row[i][digit] = true;
                col[j][digit] = true;
                block[i/3*3+j/3][digit] = true;
                board[i][j] = (char)(digit + '0' + 1);
                if (SudokuDFS(board, spaces, deepth+1)) return true;
                row[i][digit] = false;
                col[j][digit] = false;
                block[i/3*3+j/3][digit] = false;
            }
        }
        return false;
    }

    string countAndSay(int n) {
        string res = "1";
        countAndSayHelper(res, 1, n);
        return res;
    }
    void countAndSayHelper(string& source, int deepth, int boundary) {
        if (deepth == boundary) return;
        string res = "";
        int cnt = 0;
        for (int i = 0; i < source.size(); i++) {
            if (i > 0 && source[i] == source[i-1]) {
                cnt++;
            } else {
                if (cnt > 0) {
                    res += to_string(cnt) + source[i-1];
                }
                cnt = 1;
            }
        }
        res += to_string(cnt) + source[source.size()-1];
        source = res;
        countAndSayHelper(source, deepth+1, boundary);
    }
    string countAndSay2(int n) {
        string source = "1";
        int index = 1;
        while (n > index) {
            string res = "";
            int cnt = 0;
            for (int i = 0; i < source.size(); i++) {
                if (i > 0 && source[i] == source[i-1]) {
                    cnt++;
                } else {
                    if (cnt > 0) {
                        res += to_string(cnt) + source[i-1];
                    }
                    cnt = 1;
                }
            }
            res += to_string(cnt) + source[source.size()-1];
            source = res;
            index++;
        }
        return source;
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.begin()+candidates.size());
        
        vector<int> tmp;
        findCombinationSum(0, candidates, target, tmp, res);
        return res;
    }
    
    void findCombinationSum(int index, vector<int> &candidates, int target, vector<int> tmp, vector<vector<int>> &res){
        if (target == 0){
            res.push_back(tmp);
            return;
        }
        for (int i = index;i < candidates.size();i++){
            if (candidates[i] > target)break;
            tmp.push_back(candidates[i]);
            findCombinationSum(i, candidates, target - candidates[i], tmp, res);
            tmp.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.begin()+candidates.size());
        
        vector<int> tmp;
        findCombinationSum2(0, candidates, target, tmp, res);
        // sort(res.begin(), res.end());
        // res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    
    void findCombinationSum2(int index, vector<int> &candidates, int target, vector<int> tmp, vector<vector<int>> &res){
        if (target == 0){
            res.push_back(tmp);
            return;
        }
        int flag = 0;
        for (int i = index;i < candidates.size();i++){
            if (candidates[i] > target)break;
            if (flag == candidates[i])continue;
            tmp.push_back(candidates[i]);
            flag = candidates[i];
            findCombinationSum(i+1, candidates, target - candidates[i], tmp, res);
            tmp.pop_back();
        }
    }
};

int main() {
    vector<int> candidates;
    candidates.push_back(2);
    candidates.push_back(3);
    candidates.push_back(6);
    candidates.push_back(7);

    Solution s;
    s.combinationSum(candidates, 7);

    vector<int> nums = {1,3,2};
    s.nextPermutation(nums);

    s.longestValidParentheses("()(())");

    return 0;
}
