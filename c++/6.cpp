#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> res(nums.size(), -10005);
        int ans = res[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res[i] = max(nums[i], nums[i]+res[i-1]);
            ans = max(ans, res[i]);
        }
        return ans;
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // init
        int startRow = 0, endRow = matrix.size(), startCol = 0, endCol = matrix[0].size();
        vector<int> res;
        int len1 = res.size(), len2 = res.size();
        while (spiralOrderHelper(startCol, endCol, startRow, endRow, matrix, res));

        return res;
    }

    bool spiralOrderHelper(int &startCol, int &endCol, int &startRow, int& endRow, vector<vector<int>>& matrix, vector<int> &res) {
        int len = res.size();
        // 从左到右遍历一行
        if (startRow >= endRow) return false;
        for (int i = startCol; i < endCol; i++) {
            res.push_back(matrix[startRow][i]);
        }
        startRow++;
        if (startRow >= endRow) return false;
        // 从上到下遍历一列
        for (int i = startRow; i < endRow; i++) {
            res.push_back(matrix[i][endCol-1]);
        }
        endCol--;
        if (startCol >= endCol) return false;
        // 从右到左遍历一行
        for (int i = endCol-1; i >= startCol; i--) {
            res.push_back(matrix[endRow-1][i]);
        }
        endRow--;
        if (startRow >= endRow) return false;
        // 从下到上遍历一列
        for (int i = endRow-1; i >= startRow; i--) {
            res.push_back(matrix[i][startCol]);
        }
        startCol++;
        if (startCol >= endCol) return false;
    	if (res.size() > len) return true;
        return false;
    }


    vector<vector<string>> solveNQueens(int n) {
        string initStr = "";
        // init string
        for (int i = 0; i < n; i++) {
            initStr += '.';
        }
        vector<string> board(n, initStr);
        vector<vector<string>> res;
        solveHelper(0, n, board, res);
        return res;
    }

    void solveHelper(int row, int n, vector<string> cur, vector<vector<string>> &res) {
        // over condition
        if (row >= n) {
            res.push_back(cur);
            return;
        }
        // row 代表当前行, i 代表当前列
        for (int i = 0; i < n; i++) {
            // 判断是否可放
            if (judge(row, i, n, cur)){
            cur[row][i] = 'Q';
            solveHelper(row+1, n, cur, res);
            // restore
            cur[row][i] = '.';
            }
        }
    }

    bool judge(int row, int col, int n, vector<string> &cur) {      
        for (int i = 0; i < row; i++) {
        // 不能位于同一列
            if (cur[i][col] == 'Q') {
                return false;
            }
        // 不能位于同一斜线
            if (row-i-1 >= 0 && ((col-i-1 >= 0 && cur[row-i-1][col-i-1] == 'Q') || (col+i+1 < n && cur[row-i-1][col+i+1] == 'Q'))) {
                return false;
            }
        }
        return true;
    }

    int totalNQueens(int n) {
        return solveNQueens(n).size();
    }

    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        if (!nums[0]) return 0;
        vector<int> res(nums.size(), 0);
        res[0] = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (!res[i]) continue;
            for (int j = i+1; j <= nums[i]+i; j++) {
                if (j+1 == nums.size())return 1;
                res[j] = 1;
            }
        }
        return 0;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 对数组进行排序
        sort(intervals.begin(), intervals.end(), cmp);
        
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1]= max(res.back()[1], intervals[i][1]);
            }else {
                res.push_back(intervals[i]);
            }
            
        }   
        return res;
    }
    static bool cmp(vector<int> a, vector<int> b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        return merge(intervals);
    }
};



int main() {
    Solution s;
    // vector<vector<string>> res = s.solveNQueens(4);
    vector<vector<int>> intervals = {{2,3},{4,6},{8,10},{1,10}};
    s.merge(intervals);
    cout << "run over!";
    return 0;
}