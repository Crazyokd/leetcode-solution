#include<iostream>
#include<cmath>

using namespace std;
class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) return 9;
        int upper = pow(10, n);
        for (int i = upper; i >= 0; i--) {
            // 构造右半边
            int left = i;
            long long res = left;
            while (left) {
                res = res*10 + left%10;
                left /= 10;
            }

            for (int j = upper; j >= res/j; j--) {
                if (res % j == 0) {
                    return res % 1337;
                }
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}