#include<iostream>

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL) return head;
        int len = 1;
        ListNode *tail = head;
        // 得到 tail
        while(tail->next != NULL) {
            tail = tail -> next;
            len++;
        }
        tail->next = head;
        k = len >= k ? k : k%len;
        int cnt = len - k;
        while(cnt--) {
            head = head->next;
            tail = tail->next;
        }
        tail->next = NULL;
        return head;
    }
};


int main() {
    return 0;
}