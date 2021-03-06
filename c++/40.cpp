#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
#include<unordered_map>

using namespace std;

class Solution {
    unordered_map<int, vector<int>> pos;
public:
    Solution(vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i) {
            pos[nums[i]].push_back(i);
        }
    }

    int pick(int target) {
        auto &indices = pos[target];
        return indices[rand() % indices.size()];
    }
};

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