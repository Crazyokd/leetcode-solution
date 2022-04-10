#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> mosi = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

        int len = words.size();
        vector<string> words_trans(len);
        for (int i = 0; i < len; i++) {
            string trans = "";
            for (int j = 0; j < words[i].size(); j++) {
                trans += mosi[words[i][j]-'a'];
            }
            words_trans[i] = trans;
        }

        sort(words_trans.begin(), words_trans.end());
        
        for (int i = 1; i < len; i++) {
            if (words_trans[i] == words_trans[i-1]) {
                int j = i+1;
                while(j < len && words_trans[j] == words_trans[i]) {
                    j++;
                } 
                words_trans.erase(words_trans.begin()+i, words_trans.begin()+j);
                len -= j-i;
                i--;
            }
        }

        return words_trans.size();
    }
};

int main() {
    return 0;
}