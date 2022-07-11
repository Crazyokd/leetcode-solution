#include<iostream>

using namespace std;

class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int res = 0;
        for (int i = left; i <= right; i++) {
            if (check(i)) res++;
        }
        return res;

    }

    bool check(int value) {
        int cnt = 0;
        for (int i = 0; pow(2, i) <= value; i++) {
            if ((value >> i) & 1) cnt++;
        }
        if (cnt == 2 || cnt == 3 || cnt == 5 || cnt == 7 || cnt == 11 || cnt == 13 || cnt == 17 || cnt == 19) {
            return true;
        }
        return false;
    }
};

int main() {
    return 0;
}