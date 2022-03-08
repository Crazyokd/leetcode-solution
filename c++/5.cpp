#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0;i < n;i++)if (nums[i] <= 0)nums[i] = n + 1;
        for (int i = 0;i < n;i++)
            if (abs(nums[i]) <= n && nums[abs(nums[i])-1] > 0)nums[abs(nums[i])-1] *= -1;
        for (int i = 0;i < n;i++)if (nums[i] > 0)return i+1;
        return n+1;
    }

    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")return "0";
        vector<int> res(num1.size()+num2.size(), 0);
 
        for (int i = num1.size()-1; i >= 0; i--){
            for (int j = num2.size()-1; j >= 0; j--){
                res[i+j+1] += (num1[i]-'0')*(num2[j]-'0');
                res[i+j] += res[i+j+1]/10;
                res[i+j+1] %= 10;
            }
        }
        int i = 0;
        string ans = "";
        while (res[i] == 0) i++;
        while (i < res.size()) ans += to_string(res[i++]);
        
        return ans;
    }

    int jump(vector<int>& nums) {
        if (nums.size() == 1)return 0;
        // 初始化
        vector<int> res(nums.size(), 10005);
        res[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for(int j = i+1; j <= i+nums[i]; j++){
                res[j] = min(res[j], res[i]+1);
                if (j == nums.size()-1)return res[j];
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}