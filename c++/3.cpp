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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* res = new ListNode();
        ListNode* head = res;
        while(!lists.empty()){
            int min=10001,index = 0;
        	for(int i=0;i < lists.size(); i++){
            	if(lists[i] == NULL){
                	lists.erase(lists.begin() + i);
               	 	i--;
                    continue;
            	}
                if(min > lists[i]->val){
                    min =lists[i]->val;
                    index = i;
                }
            }

            res->next = lists[index];
            res = res->next;
            if (lists[index] != NULL)
            lists[index] = lists[index]->next;
    	}
        return head->next;
    }
    ListNode* swapPairs(ListNode* head) {
        ListNode* pre = head;
        while(pre != NULL){
            if(pre->next != NULL){
                // swap
                int t = pre->val;
                pre->val = pre->next->val;
                pre->next->val = t;
                pre = pre->next->next;
            }else break;
        }
    	return head;
    }
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *node = head;
        int cnt = k;
        while (cnt--){
            if (node == NULL)return head;
            node = node->next;
        }
        ListNode *newHead = reverse(head, node);
        head->next = reverseKGroup(node, k);
        return newHead;
    }

    ListNode* reverse(ListNode *first, ListNode *last){
        ListNode *pre = last;
        while(first != last){
            ListNode *tmp = first->next;
            first->next = pre;
            pre = first;
            first = tmp;
        }
        return pre;
    }

    int removeDuplicates(vector<int>& nums) {
        int len = nums.size(), res = 0;
        for(int i=1;i < len-res;i++){
            if(nums[i] == nums[i-1]){
                res++;
                nums.erase(nums.begin()+i);
                nums.push_back(nums[--i]);
            }
    	}
        return len-res;
    }
    int removeElement(vector<int>& nums, int val) {
        int res = 0;
        for(int i=0; i < nums.size(); i++){
            if(nums[i] == val){
                nums.erase(nums.begin()+i);
                i--;
                res++;
            }
        }
        for(int i=0; i < res ; i++){
            nums.push_back(val);
        }
        return nums.size() - res;
    }
};
int main(){
    printf("run success!");
    return 0;
}
