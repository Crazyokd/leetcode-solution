#include<iostream>
#include<string>

using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        for (int i = 0; i < s.size(); i++) {
            if (s == goal) return true;
            s = s.substr(1) + s[0];
        }
        return false;
    }
};