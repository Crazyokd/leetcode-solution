#include<iostream>
#include<algorithm>
#include<vector>

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
    ListNode* deleteDuplicates(ListNode* head) {
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
};

int main() {
    return 0;
}