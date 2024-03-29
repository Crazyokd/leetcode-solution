#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        nums.resize(unique(nums.begin(), nums.end())-nums.begin());
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target)return true;

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
        return false;    
    }

    bool searchII(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while (high >= low) {
            int mid = low + ((high-low)>>1);
            if (nums[mid] == target)return true;

            if (nums[mid] == nums[low] && nums[mid] == nums[high]) {
                low ++;
                high --;
                continue;
            }
            // exist pivot
            if (nums[mid] >= nums[low]) {
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                }else {
                    low = mid + 1;
                }
            }else if (nums[mid] <= nums[high]) {
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                }else {
                    high = mid - 1;
                }
            }
        }
        return false;    
    }

    ListNode* deleteDuplicatesII(ListNode* head) {
        ListNode *newHead = new ListNode(), *pre = newHead, *next = head;
        newHead -> next = head;

        while (next != NULL && next->next != NULL) {
            ListNode *tmp = next->next;
            bool flag = false;
            if (tmp->val == next->val)flag = true;
            while (tmp != NULL && tmp->val == next->val) {
                tmp = tmp ->next; 
            }
            next = tmp;
            if (flag) {
                pre->next = next;
            } else {
                pre = pre->next;
            }
            
        }
        return newHead->next;
    }

    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL)return head;
        ListNode *pre = head, *next = head->next;

        while (next != NULL) {
            if (next->val != pre->val) {
                pre->next = next;
                pre = next;
            }
            next = next->next;
        }
        pre->next = next;
        return head;
    }

    int largestRectangleArea(vector<int>& heights) {
        int h_size = heights.size();
        vector<int> left, right;
        stack<int> sta;
        for (int i = 0; i < h_size; i++) {
            while (!sta.empty() && heights[sta.top()] >= heights[i]) {
                sta.pop();
            }
            left.emplace_back(sta.empty() ? -1 : sta.top());
            sta.push(i);
        }

        sta = stack<int>();
        for (int i = h_size-1; i >= 0; i--) {
            while (!sta.empty() && heights[sta.top()] >= heights[i]) {
                sta.pop();
            }
            right.emplace_back(sta.empty() ? h_size : sta.top());
            sta.push(i);
        }

        int ans = 0;
        for (int i = 0; i < h_size; i++) {
            ans = max(ans, (right[h_size-i-1]-left[i]-1)*heights[i]);
        }
        return ans;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<int> left_init(matrix[0].size(), 0);
        vector<vector<int>> left_dp(matrix.size(), left_init);

        // dp
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                left_dp[i][j] = matrix[i][j] == '0' || j == 0 ? int(matrix[i][j]-'0') : left_dp[i][j-1] + 1;
            }
        }
        
        // 单调栈
        int ans = 0;
        for (int j = 0; j < matrix[0].size(); j++) {
            int h_size = matrix.size();
            vector<int> left, right;
            stack<int> sta;
            for (int i = 0; i < h_size; i++) {
                while (!sta.empty() && left_dp[sta.top()][j] >= left_dp[i][j]) {
                    sta.pop();
                }
                left.emplace_back(sta.empty() ? -1 : sta.top());
                sta.push(i);
            }

            sta = stack<int>();
            for (int i = h_size-1; i >= 0; i--) {
                while (!sta.empty() && left_dp[sta.top()][j] >= left_dp[i][j]) {
                    sta.pop();
                }
                right.emplace_back(sta.empty() ? h_size : sta.top());
                sta.push(i);
            }

            for (int i = 0; i < h_size; i++) {
                ans = max(ans, (right[h_size-i-1]-left[i]-1)*left_dp[i][j]);
            }
        }
        
        return ans;
    }

    ListNode* partition(ListNode* head, int x) {
        // if (head == NULL || head->next == NULL)return head;
        ListNode *before = new ListNode(0), *after = new ListNode(0);
        ListNode *res = before, *tmp = after;
        while (head != NULL) {
            if (head->val < x) {
                before->next = head;
                before = before->next;
            }else {
                after->next = head;
                after = after->next;
            }
            head = head->next;
        } 
        // 连接before 和 after
        before->next = tmp->next;
        // 断开 after
        after->next = NULL;
        return res->next;
    }

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int insertPoint = 0;
        for (int i = 0; i < m+insertPoint && insertPoint < n; i++) {
            if (nums2[insertPoint] < nums1[i]) {
                int begin = insertPoint;
                insertPoint++;
                while(insertPoint < n && nums2[insertPoint] < nums1[i]) {
                    insertPoint++;
                }
                nums1.insert(nums1.begin()+i, nums2.begin()+begin, nums2.begin()+insertPoint);
            }
        }
        if (insertPoint < n) {
            nums1.insert(nums1.begin()+m+insertPoint, nums2.begin()+insertPoint, nums2.end());
        }
        // trim vector
        nums1.resize(m+n);
    }

    vector<int> grayCode(int n) {
        vector<int> res;
        int cnt = 1 << n;
        for (int i = 0; i < cnt; i++) {
            res.emplace_back((i>>1)^i);
        }
        return res;
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        // res.emplace_back(vector<int>());
        sort(nums.begin(), nums.end());

        for (int i = 0; i <= nums.size(); i++) {
            vector<int> cur;
            subsetsWithDupHelper(1, 0, nums, cur, res, i);
        } 
        return res;
    }
    void subsetsWithDupHelper(int deepth, int index, vector<int> nums, vector<int> &cur, vector<vector<int>>& res, int k) {
        if (deepth > k){
            res.push_back(cur);
            return;
        }
        for (int i = index; i < nums.size(); i++){
            // 重复元素相同位置不重复使用
            if (i != index && nums[i] == nums[i-1]) continue;

            cur.push_back(nums[i]);
            vector<int> tmp(nums);
            tmp.erase(tmp.begin()+i);
            subsetsWithDupHelper(deepth+1, i, tmp, cur, res, k);
            cur.pop_back();
        }
    }
};

int main() {
    Solution s;
    ListNode *head = new ListNode(1, new ListNode(4, new ListNode(3, new ListNode(2, new ListNode(5, new ListNode(2))))));

    ListNode *res = s.partition(head, 3);
    while(res != NULL) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;

    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    
    // nums1.insert(nums1.begin(), 3);

    s.merge(nums1, 3, nums2, 3);

    for (auto i : nums1) {
        cout << i << " ";
    }

    vector<int> heights = {2,1,5,6,2,3};
    s.largestRectangleArea(heights);

    vector<int> nums = {2,5,6,0,0,1,2};
    s.searchII(nums, 3);

    vector<vector<char>> matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    s.maximalRectangle(matrix);
    return 0;
}