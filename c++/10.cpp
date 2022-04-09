#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        vector<int> res;
        res.emplace_back(1);
        res.emplace_back(1);
        for (int i = 1; i < s.size(); i++) {
            int t = 0;
            // 存在两种情况
            if (s[i-1] != '0' && atoi(s.substr(i-1, 2).c_str()) <= 26) {
                t += res[i-1];
            }
            if (s[i] != '0') {
                t += res[i];
            }
            res.emplace_back(t);
        }
        return res.back();
    }

    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head -> next == NULL || left == right) return head;
        int cnt = 0;
        ListNode *node_left = new ListNode();
        node_left -> next = head;
        while (++cnt < left) {
            node_left = node_left->next;
        }

        ListNode *node_right = node_left->next;
        while (cnt++ <= right) {
            node_right = node_right->next;
        }

        ListNode *pre = node_right;
        ListNode *next = node_left->next;
        while (next != node_right) {
            ListNode *tmp = next->next;
            next -> next = pre;
            pre = next;
            next = tmp;
        }

        bool flag = node_left->next == head; // 判断head节点是否反转
        node_left->next = pre;

        return flag ? node_left->next : head;
    }
};

int main() {
    return 0;
}