#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int minn = prices[0];
        for (int i = 0; i < prices.size(); i++) {
            minn = min(minn, prices[i]);
            res = max(res, prices[i]-minn);
        }
        return res;
    }
};

int mian() {
    return 0;
}