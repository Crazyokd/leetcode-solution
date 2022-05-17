#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
class Solution {
public:
    static bool cmp(string &str1, string &str2, string &order) {
        int len1 = str1.size();
        int len2 = str2.size();

        int minLen = min(len1, len2);
        for (int i = 0; i < minLen; i++) {
            int cp = find(order.begin(), order.end(), str1[i]) - find(order.begin(), order.end(), str2[i]);
            if (cp > 0) {
                return false;
            } else if (cp < 0) {
                return true;
            }
        }
        return len1 < len2;
    }
    bool isAlienSorted(vector<string>& words, string order) {
        for (int i = 1; i < words.size(); i++) {
            if (cmp(words[i], words[i-1], order)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    return 0;
}