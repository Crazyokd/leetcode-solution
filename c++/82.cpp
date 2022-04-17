#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
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