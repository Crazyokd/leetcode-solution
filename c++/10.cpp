#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        vector<int> res;
        res.emplace_back(1);
        res.emplace_back(1);
        for (int i = 1; i < s.size(); i++) {
            int t = 0;
            // 存在两种情况
            if (s[i-1] != '0' && atoi(s.substr(i-1, 2).c_str()) <= 26) {
                t += res[i-1];
            }
            if (s[i] != '0') {
                t += res[i];
            }
            res.emplace_back(t);
        }
        return res.back();
    }
};

int main() {
    return 0;
}