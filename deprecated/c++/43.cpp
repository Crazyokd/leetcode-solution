#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans;
        queue<Node*> q;
        q.push(root);
        int pre_lay_cnt = 1;
        while (!q.empty()) {
            vector<int> lay_vec(pre_lay_cnt);
            int next_lay_cnt = 0;
            for (int i = 0; i < pre_lay_cnt; i++) {
                Node *v = q.front();
                q.pop();
                lay_vec[i] = v->val;
                for (int j = 0; j < v->children.size(); j++) {
                    q.push(v->children[j]);
                }
                next_lay_cnt += v->children.size();
            }
            ans.emplace_back(lay_vec);
            pre_lay_cnt = next_lay_cnt;
        }
        return ans;
    }
};

int main() {
    return 0;
}