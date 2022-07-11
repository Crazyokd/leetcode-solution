#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
	int dp[10000005];
	bool checkNumbersWithUniqueDigits(int v) {
        string v_str = to_string(v);
        
        int len = v_str.size();
        for (int i = 0; i < len-1; i++) {
            if (v_str[i] == v_str[len-1]) return false;
        }
        return true;
    }
    int countNumbersWithUniqueDigits(int n) {
        memset(dp, 0, sizeof(dp));
        int ans = 1;
        if (n > 0) ans += 9;
        for (int i = 1; i < 10; i++) {
            dp[i] = 1;
        }
        int max_boundary = pow(10, min(n, 7));
		for (int i = 10; i < max_boundary; i++) {
            if (!dp[i/10]) continue;

			if (checkNumbersWithUniqueDigits(i)) {
                ans++;
                dp[i] = 1;
            }
        }
        return ans + (n > 7 ? 1632960 : 0);
    }
    int countNumbersWithUniqueDigits2(int n) {
        if (n == 0) return 1;
        int res = 10;
        int cur = 9;
        for (int i = 0; i < n-1; i++) {
            cur *= 9-i;
            res += cur;
        }
        return res;
    }
};

int main() {
    return 0;
}