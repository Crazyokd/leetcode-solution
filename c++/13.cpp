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

    int maxProfitII(vector<int>& prices) {
        int minn = prices[0];
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > minn) {
                res += prices[i] - minn;
                minn = prices[i];
            } else {
                minn = min(prices[i], minn);
            }
        }
        return res;
    }

    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/solution/mai-mai-gu-piao-de-zui-jia-shi-ji-iii-by-wrnt/
    int maxProfitIII(vector<int>& prices) {
        int n = prices.size();
        int buy1 = -prices[0], sell1 = 0;
        int buy2 = -prices[0], sell2 = 0;
        for (int i = 1; i < n; ++i) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }
};

int main() {
    Solution s;
    vector<int> prices = {3,3,5,0,0,3,1,4};
    s.maxProfitIII(prices);
    return 0;
}