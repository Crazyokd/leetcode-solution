#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
using namespace std;

class Solution {
public:
    //从两端向中间扩散
    int maxArea(vector<int>& height) {
        int start=0,end=height.size()-1;
        int ans=0;
        while(end > start){
            ans=max(ans,(end-start)*min(height[start],height[end]));
            if(height[start] > height[end])end--;
            else start++;
        }
        return ans;
    }
    string intToRoman(int num) {
        int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        string symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        string res="";
        int i=0;
        while(num != 0){
            while(values[i] > num){
                i++;
            }
            num -= values[i];
            res += symbols[i];
        } 
        return res;
    }
    int romanToInt(string s) {
        int commonValues[] = {1000,500,100,50,10,5,1};
        int specialValues[] = {900,400,90,40,9,4};
        string commonSymbols[] = {"M","D","C","L","X","V","I"};
        string specialSymbols[] = {"CM","CD","XC","XL","IX","IV"};
        int ans=0;
        for(int i=0;i < s.size();i++){
            int j;
            for(j=0;j < 6;j++){
                if(s.substr(i,2) == specialSymbols[j]){
                    ans+=specialValues[j];
                    i+=1;
                    break;
                }    
            }
            if(j < 6)continue;
            for(j=0;j < 7;j++){
                if(i<s.size() && s.substr(i,1) == commonSymbols[j]){
                    ans+=commonValues[j];
                    break;
                }
            }
        }
        return ans;
    }
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 1)return strs.front();
        string res;
        int cnt=0;
        while(true){
            for(int i=1;i<strs.size();i++){
                if(strs[i].size() == cnt || strs[i][cnt] != strs[i-1][cnt]){
                    res=strs[i].substr(0,cnt);
                    return res;
                }
            }
            cnt++;
        }
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::vector<vector<int>> result;
        if (nums.size() < 3) {
            return result;
        }

        std::size_t n_size = nums.size();
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n_size; ++i) {
            // all numbers from now on will be greater than 0, no point in continuing
            if (nums[i] > 0) break;

            // we have seen this number & combo before; skip
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int left = i+1, right = n_size - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0) {
                    ++left;
                } else if (sum > 0) {
                    --right;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    int last_left = nums[left], last_right = nums[right];
                    // we have seen this number & combo before; skip
                    while (left < right && nums[left] == last_left) ++left;
                    while (left < right && nums[right] == last_right) --right;
                }
            }

        }
        return result;
    }
    int threeSumClosest(vector<int>& nums, int target) {
        int def = 0x7fffffff;

        std::size_t n_size = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < n_size; ++i) {
            // all numbers from now on will be greater than 0, no point in continuing
            if (nums[i] > target / 3) break;

            // we have seen this number & combo before; skip
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int left = i+1, right = n_size - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                int tmp = sum - target;
                //the closest answer
                if(tmp == 0)return target;
                if(abs(tmp) < def){
                    result = sum;
                    def = abs(tmp);
                }
                if (tmp < 0) {
                    ++left;
                } else{
                    --right;
                }
            }
        }
        return result;
    }
    void helper(string digits,int depth,string tmpRes,vector<string>& res){
        if(depth == digits.size()){
            res.push_back(tmpRes);
            return;
        }
        string letters[] = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        string digit = letters[(int)(digits[depth]-'2')]; 
        int len = digit.size();
        for(int i=0;i < len;i++){  
            helper(digits,depth+1,tmpRes+digit[i],res);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if(digits.empty())return res;
        helper(digits,0,"",res);
        return res;
    }
};

int main(){
    Solution solution=Solution();
    // cout<<solution.romanToInt("MCMXCIV");
    vector<string> strs;
    strs.push_back("flower");
    strs.push_back("flow");
    strs.push_back("flight");
    // cout << solution.longestCommonPrefix(strs);
    solution.letterCombinations("23");
    return 0;
}