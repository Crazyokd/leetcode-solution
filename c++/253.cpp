#include<string>
#include<iostream>

using namespace std;
class Solution {
public:
    bool oneEditAway(string first, string second) {
        int size_f = first.size();
        int size_s = second.size();
        int sep = abs(size_f - size_s);
        if (sep > 1) {
            return false;
        } else if (sep) {
            if (size_f > size_s) {
                return oneEditAwayHelper(second, size_s, first);
            } else {
                return oneEditAwayHelper(first, size_f, second);
            }
        } else {
            int err = 0;
            for (int i = 0; i < size_f; i++) {
                if (first[i] != second[i] && ++err > 1) {
                    return false;
                }
            }
            return true;
        }
        
    }
    bool oneEditAwayHelper(string first, int idx_f, string second) {
        bool flag = true;
        for (int i = 0; i < idx_f; i++) {
            if (first[i] != second[flag ? i : i+1]) {
                if (flag) {
                    i--;
                    flag = false;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    return 0;
}