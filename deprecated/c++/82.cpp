#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    double triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
        return 0.5 * abs(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2);
    }

    double largestTriangleArea(vector<vector<int>> & points) {
        int n = points.size();
        double ret = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    ret = max(ret, triangleArea(points[i][0], points[i][1], points[j][0], points[j][1], points[k][0], points[k][1]));
                }
            }
        }
        return ret;
    }
    
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string, int> mp;
        string res;
        int max_cnt = 0;
        for(int i = 0; i < paragraph.size(); i++) {
            string word = "";
            while(paragraph[i] >= 'a' && paragraph[i] <= 'z' || 
                paragraph[i] >= 'A' && paragraph[i] <= 'Z') {
                word += paragraph[i] >= 'a' ? paragraph[i] : paragraph[i] + 32;
                if (i+1 < paragraph.size()) {
                    i++;
                } else {
                    break;
                }
            }
            if (word != "" && find(banned.begin(), banned.end(), word) == banned.end()) {
                if (mp.count(word)) {
                    mp[word]++;
                } else {
                    mp[word] = 1;
                }
                if (mp[word] > max_cnt) {
                    max_cnt = mp[word];
                    res = word;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<string> banned = {"hit"};
    cout << s.mostCommonWord("Bob hit a ball, the hit BALL flew far after it was hit.", banned);
}