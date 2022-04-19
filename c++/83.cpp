#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        vector<int> pos;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                pos.emplace_back(i);
            }
        }
        int index = 0;
        vector<int> res(s.size());
        for (int i = 0; i < s.size(); i++) {
            if (index+1 < pos.size() && abs(pos[index]-i) > abs(pos[index+1]-i)) index++;
            res[i] = abs(pos[index] - i);
        }
        return res;
    }
};

int main() {
    return 0;
}