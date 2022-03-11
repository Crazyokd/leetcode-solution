class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> res(nums.size(), -10005);
        int ans = res[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res[i] = max(nums[i], nums[i]+res[i-1]);
            ans = max(ans, res[i]);
        }
        return ans;
    }
};
