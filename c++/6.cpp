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
};

int main() {
    Solution s;
    vector<vector<string>> res = s.solveNQueens(4);
    
    return 0;
}