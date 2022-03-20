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
            
};
