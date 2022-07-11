#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstring>
#include<regex>

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
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        map<int,int> m;
        for(int i=0;i<nums.size();i++){
            int another=target-nums[i];
            if(m[another]){
                ans.push_back(m[another]-1);
                ans.push_back(i);
                break;
            }
            m[nums[i]]=i+1;
        }
        return ans;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode();
        int n1=0,n2=0,carry=0;
        ListNode *current=head;
        while(l1!=nullptr || l2 != nullptr || carry != 0){
            if(l1==nullptr)n1=0;
            else{
                n1=l1->val;
                l1=l1->next;
            }
            if(l2==nullptr)n2=0;
            else{
                n2=l2->val;
                l2=l2->next;
            }
            current->next=new ListNode((n1+n2+carry)%10);
            current=current->next;
            carry=(n1+n2+carry)/10;
        }
        return head->next;
    }
    int lengthOfLongestSubstring(string s) {
        //使用map
        map<int,int> m;
        //cur_sta表示当前子串起点
        int ans=0,cur_sta=0,len=s.size();
        for(int i=0;i<len;i++){
            if(m[(int)s[i]]){
                //如果当前字符已经出现过
                ans=max(i-cur_sta,ans);
                //擦除
                for(int j=cur_sta;j<m[(int)s[i]]-1;j++){
                    m[(int)s[j]]=0;
                }
                cur_sta=m[(int)s[i]];
            }
            m[(int)s[i]]=i+1;
        }
        return max(ans,len-cur_sta);
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1=nums1.size(),len2=nums2.size();
        vector<int> ans;
        int cur1=0,cur2=0;
        while(cur1 < len1 || cur2 < len2){
            while(cur1< len1 && (cur2 ==len2 || nums1[cur1] <= nums2[cur2])){
                ans.push_back(nums1[cur1]);
                cur1++;
            }
            while(cur2 < len2 && (cur1 == len1 || nums1[cur1] > nums2[cur2])){
                ans.push_back(nums2[cur2]);
                cur2++;
            }
        }
        cout<<ans.size()<<endl;
        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<endl;
        }
        if((ans.size())%2==0)return (ans[ans.size()/2-1]+ans[ans.size()/2])/2.0;
        else return ans[ans.size()/2];
    }
    //dp
    string longestPalindrome1(string s) {
        const int N=1005;
        bool a[N][N]={0};
        int sta=0,ans=1;
        for(int i=0;i<s.size();i++){
            for(int j=0;j<s.size()-i;j++){
                if(s[j]==s[j+i] && (j+1 >= j+i-1 || a[j+1][j+i-1])){
                    a[j][j+i]=true;
                    if(i+1>ans){
                        ans=i+1;
                        sta=j;
                    }
                }
            }
        }
        return s.substr(sta,ans);
    }

//马拉车算法
    string longestPalindrome(string s){
        if(s.size() < 2)return s;
        const int N=2005;
        int a[N]={0};
        char cc[N];
        int center=0,maxRight=0,maxLen=1,sta=0;
        //预处理
        cc[0]='#';
        for(int i=0;i<s.size();i++){
            cc[i*2+1]=s[i];
            cc[2*(i+1)]='#';
        }
        for(int i=0;i < s.size()*2+1;i++){
            if(i < maxRight){
                //核心算法
                a[i] = min(a[2*center-i],maxRight-i);
            }
            int left=i-(a[i]+1),right=i+(a[i]+1);
            while(left >= 0 && right < s.size()*2+1 && cc[left] == cc[right]){
                left--;
                right++;
                a[i]++;
            }
            //更新maxRight
            if(a[i] + i > maxRight){
                maxRight =a[i] + i;
                center = i;
            }
            //更新答案
            if(a[i] > maxLen){
                maxLen = a[i];
                sta = (i - a[i])/2;
            }
        }
        return s.substr(sta,maxLen);
    }

//题意
// 将给定的字符串按如下的Z字型排列，并从左至右输出
// |  /  /
// | /| /|
// |/ |/
// |  |
    string convert(string s, int numRows) {
        vector<vector<char>> ans(numRows);
        int down=0,up=numRows-2;
        for(int i=0;i < s.size();i++){
            if(down < numRows){
                ans[down].push_back(s[i]);
                down++;
            }else if(up > 0){
                ans[up].push_back(s[i]);
                up--;
            }else{
                down=0;
                up=numRows-2;
                i--;
            }
        }
        string solution="";
        for(int i=0;i<numRows;i++){
            for(int j=0;j < ans[i].size();j++){
                solution.push_back(ans[i][j]);
            }
        }
        return solution;
    }

//注意最大值和最小值
    int reverse(int x) {
        long long ans=0;
        int maxx=-1*((1<<31)+1),minn=(1<<31);
        while(x != 0){
            ans=ans*10+x%10;
            x/=10;
        }
        if(ans > maxx || ans < minn)return 0;
        return ans;
    }

    int myAtoi(string s) {
        int maxx=-1*((1<<31)+1),minn=1<<31;
        bool allowSign=true,allowSpace=true;
        int sign=1;
        vector<int> ans;
        for(int i=0;i<s.size();i++){
            if(s[i]==' '){
                if(allowSpace)continue;
                else break;
            }else if((s[i] == '+' || s[i] == '-')){
                if(!allowSign)break;
                if(s[i] == '-')sign = -1;
                allowSign=false;
                allowSpace=false;
            }else if(s[i] <= '9' && s[i] >= '0'){
                allowSign=false;
                allowSpace=false;
                ans.push_back((int)(s[i]-'0'));
            }else{
                break;
            }
        }
        long long res=0;
        bool leadingZero=true;
        int substitute = sign > 0 ? maxx : minn;
        for(int i=0;i<ans.size();i++){
            if(!ans[i] && leadingZero)continue;
            if(ans.size() - i > 10)return substitute;
            leadingZero=false;
            res=res*10+ans[i];
        }
        if(res > maxx || res < minn)return substitute;    
        return sign*res;
    }

    bool isPalindrome(int x) {
        if(x < 0)return false;
        vector<int> res;
        while(x){
            res.push_back(x%10);
            x/=10;
        } 
        int len=res.size();
        for(int i=0;i<len/2;i++){
            if(res[i] != res[len-i-1])
                return false;
        }    
        return true;
    }
    //通过分支判断无法实现功能
    // bool isMatch(string s, string p) {
    //     int ps=0,pp=0;
    //     //对p中*前后的字符进行预处理
    //     for(int i=2;i<p.size();){
    //         if(p[i-1] == '*' && (p[i] == '*' || p[i] == p[i-2]))p.erase(p.begin()+i);
    //         else i++;
    //     }
    //     int lens=s.size(),lenp=p.size();
    //     while(ps < lens && pp < lenp){
    //         //直接出现*视为无效
    //         if(p[pp] == '*'){
    //             pp++;
    //             continue;
    //         }
    //         if(pp+1 < lenp && p[pp+1] == '*'){
    //             while(ps < lens && (s[ps] == p[pp] || p[pp] == '.'))ps++;
    //             pp+=2;
    //         }else{
    //             if(s[ps] != p[pp] && p[pp] != '.')return false;
    //             ps++;
    //             pp++;
    //         }
    //     }
    //     if(ps < lens || pp < lenp)return false;
    //     return true;
    // }
    bool isMatch1(string s, string p) {
        return regex_match(s,regex(p));
    }
    // dp[a][b]表示将s[a]与p[b]相匹配，若返回false，表示不能将s[a]与p[b]相匹配
    bool solver(string &s,string &p,int a ,int b,vector<vector<int>> &dp)  {   
        // 递归终止条件
        //若dp[a][b]!=-1,表示已经计算过,return
        if(dp[a][b]!=-1) return dp[a][b];
        //匹配完毕,return true
        if(a>=s.length() && b>=p.length())  return dp[a][b] = true;
        //p已经使用完但s还有未匹配的,return false
        if(b>=p.length())  return dp[a][b] = false;
        
        //s[a]能与p[b]相匹配
        bool match = ( a <s.length() && (s[a]==p[b] || p[b]=='.'));
        //关键算法，若出现*通配符，可选择不匹配或选择匹配
        if( b<p.length()-1 && p[b+1]=='*') return dp[a][b] = solver(s,p,a,b+2,dp) || ( match && solver(s,p,a+1,b,dp));
        //普通匹配
        if(match) return dp[a][b] = solver(s,p,a+1,b+1,dp);
        return dp[a][b] = false;
    }
    bool isMatch(string s, string p) {
        vector<vector<int>> dp( s.length()+1, vector<int>(p.length()+1,-1) );
        return solver(s,p,0,0,dp);
    }
};

int main(){
    vector<int> ans(2);//创建一个size=2的vector
    string s="aacabdkacaa";
    map<int,int> m;
    m[1]=2;
    // cout<<m[1];
    m.erase(1);
    // cout<<m[1];
    // cout<<(int)s[1];
    Solution solution=Solution();
    // cout<<solution.lengthOfLongestSubstring(s);
    vector<int> a,b;
    a.push_back(1),a.push_back(3);
    b.push_back(2);
    // solution.findMedianSortedArrays(a,b);
    // cout<<solution.longestPalindrome1(s);
    // s.append("#");
    // cout<<solution.longestPalindrome(s)<<endl;
    string ss="PAYPALISHIRING";
    // cout<<solution.convert(ss,3);
    // cout<<solution.reverse(-123);
    // cout<<solution.myAtoi("-0042");
    // cout<<solution.isPalindrome(1001);
    cout<<solution.isMatch("aa","a*");
    return 0;
}