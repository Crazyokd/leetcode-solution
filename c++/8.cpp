class Solution {
public:
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
};