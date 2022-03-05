#include<iostream>
#include<vector>
#include<algorithm>

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
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<bool> initVec(10, false);
        vector<vector<bool>> rowbuf(9, initVec);
        vector<vector<bool>> colbuf(9, initVec);
        vector<vector<bool>> boxbuf(9, initVec);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                if (rowbuf[i][num] || colbuf[j][num] || boxbuf[i/3*3+j/3][num]) return false;
                rowbuf[i][num] = true;
                colbuf[j][num] = true;
                boxbuf[i/3*3+j/3][num] = true;
            }
        }
        return true;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.begin()+candidates.size());
        
        vector<int> tmp;
        findCombinationSum(0, candidates, target, tmp, res);
        return res;
    }
    
    void findCombinationSum(int index, vector<int> &candidates, int target, vector<int> tmp, vector<vector<int>> &res){
        if (target == 0){
            res.push_back(tmp);
            return;
        }
        for (int i = index;i < candidates.size();i++){
            if (candidates[i] > target)break;
            tmp.push_back(candidates[i]);
            findCombinationSum(i, candidates, target - candidates[i], tmp, res);
            tmp.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.begin()+candidates.size());
        
        vector<int> tmp;
        findCombinationSum2(0, candidates, target, tmp, res);
        // sort(res.begin(), res.end());
        // res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    
    void findCombinationSum2(int index, vector<int> &candidates, int target, vector<int> tmp, vector<vector<int>> &res){
        if (target == 0){
            res.push_back(tmp);
            return;
        }
        int flag = 0;
        for (int i = index;i < candidates.size();i++){
            if (candidates[i] > target)break;
            if (flag == candidates[i])continue;
            tmp.push_back(candidates[i]);
            flag = candidates[i];
            findCombinationSum(i+1, candidates, target - candidates[i], tmp, res);
            tmp.pop_back();
        }
    }
};

int main() {
    vector<int> candidates;
    candidates.push_back(2);
    candidates.push_back(3);
    candidates.push_back(6);
    candidates.push_back(7);

    Solution s;
    s.combinationSum(candidates, 7);
    return 0;
}
