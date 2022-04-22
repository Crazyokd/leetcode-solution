#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>

using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int numSum = accumulate(nums.begin(), nums.end(), 0);
        int f0 = 0;
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            f0 += nums[i]*i;
        }
        int res = f0;

        for (int i = 1; i < len; i++) {
            f0 += numSum - len*nums[len-i];
            res = max(res, f0);
        }

        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {4, 3, 2, 6};
    s.maxRotateFunction(nums);
    return 0;
}