#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target)return mid;
            printf("%d %d %d\n",low, mid, high);
            // exist pivot
            if (nums[mid] > nums[low]) {
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                }else {
                    low = mid + 1;
                }
            }else if (nums[mid] < nums[high]) {
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                }else {
                    high = mid - 1;
                }
            }else {
                if (nums[low] == nums[mid]) {
                    low++;
                }
                if (nums[high] == nums[mid]) {
                    high--;
                }
            }
        }
        return -1;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        // 使用二分找到target
        int index = getIndex(nums, target);
        // 对第一个index查找得到结果
        if (index < 0) {
            res.push_back(-1);
            res.push_back(-1);
        }else {
            int low = index - 1, high = index + 1;
            while (low >= 0 && nums[low] == target) low--;
            while (high < nums.size() && nums[high] == target) high++;
            res.push_back(low+1);
            res.push_back(high-1);
        }
        return res;
    }
    int getIndex(vector<int>& nums, int target) {
        // 使用二分找到target
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) {
                high = mid - 1;
            }else {
                low = mid + 1;
            }
        }
        return -1;
    }
    int searchInsert(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while(high > low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                low = mid + 1;
            }else {
                high = mid;
            }
        }
        return nums[high] < target ? high + 1 : high;
    }
};

int main() {
    return 0;
}
