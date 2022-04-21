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

    string toGoatLatin(string sentence) {
        sentence += " ";
        string res = "";
        for (int i = 0, cnt = 0; i < sentence.size(); i++) {
            string::iterator isFindElement = find(sentence.begin()+i, sentence.end(), ' ');
            if (isFindElement != sentence.end()) {
                int len = isFindElement - sentence.begin() - i;
                string word = sentence.substr(i, len);
                char fc = word[0] < 'a' ? word[0]+32 : word[0];
                if (!(fc == 'a' || fc == 'e' || fc == 'i' || fc == 'o' || fc == 'u')) {
                    word = word.substr(1) + word[0];
                }
                res += word + "ma" + string(cnt+1, 'a') + " ";
                i += len;
                cnt++;
            }
        }
        return res.substr(0, res.size()-1);
    }
};

int main() {
    return 0;
}