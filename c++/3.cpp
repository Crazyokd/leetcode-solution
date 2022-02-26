#include<iostream>
#include<vector>
#include<string>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    struct ListNode{
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    	if (list1 == NULL) return list2;
        if (list2 == NULL) return list1;
        ListNode *ans = new ListNode(), *res;
        res = ans;
        while(list1 != NULL && list2 != NULL){
        	if (list1->val > list2->val){
                ans->next = list2;
                list2 = list2->next;
            }
        	else{
                ans->next = list1;
                list1 = list1->next;
            }
            ans = ans->next;
        }
        if (list1 == NULL)ans->next = list2;
        else ans->next = list1;
        return res->next;
    }
    vector<string> generateParenthesis(int n) {
    	vector<string> ans;
        return helper(ans, "(", "(", n-1, 2*n);
    }
    vector<string> helper(vector<string> &ans, string real, string res, int n, int len){
        if (res.size() == len){
            ans.push_back(res);
        }
    	if (n){
            helper(ans, real+"(", res+"(", n-1, len);
        }
        if (real.size()){
            helper(ans, real.substr(0,real.size()-1), res+")", n, len);
        }
        return ans;

    }
};
int main(){
    printf("run success!");
    return 0;
}
