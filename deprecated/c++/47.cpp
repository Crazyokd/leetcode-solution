#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;
class Solution {
public:
    int minMoves21(vector<int>& nums) {
        // 将数组排序
        sort(nums.begin(), nums.end());
        // 取中位数
        int average = nums[nums.size()/2];
        int res = 0;
        for (const int &num : nums) {
            res += abs(average - num);
        }
        return res;
    }
        int minMoves22(vector<int>& nums) {
        // 将数组排序
        sort(nums.begin(), nums.end());
        int size = nums.size();
        // 取中位数
        int average = nums[size/2];
        int res = 0;
        // for (const int &num : nums) {
        //     res += abs(average - num);
        // }
        for (int i = 0; i < size/2; i++) {
            res += nums[size-i-1] - nums[i];
        }
        return res;
    }

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