#include<iostream>
#include<vector>
#include<algorithm>

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

    int uniquePaths(int m, int n) {
        // int res = 0;
        // uniquePathsHelper(1, 1, m, n, res);
        // return res;
        
        // use dp
        int arr[101][101] = {0};
        arr[1][1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                arr[i][j] += arr[i-1][j] + arr[i][j-1];
            }
        }
        return arr[m][n];
        
    }
    
    // 深搜超时，而且答案也不用求出所有具体路径
    // void uniquePathsHelper(int row, int col, int m, int n, int& res){
    //     if (row == m && col == n) {
    //         res++;
    //         return;
    //     }
    //     if (row < m)uniquePathsHelper(row+1, col, m, n, res);
    //     if (col < n)uniquePathsHelper(row, col+1, m, n, res);
    // }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int arr[101][101] = {0};
        arr[1][1] = 1;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (obstacleGrid[i-1][j-1]) {
                    arr[i][j] = 0;
                }else arr[i][j] += arr[i-1][j] + arr[i][j-1];
            }
        }
        return arr[m][n];
    }

    int minPathSum(vector<vector<int>>& grid) {
        // init result
        int m = grid.size(), n = grid[0].size();
        vector<int> initVec(n+1, 0);
        vector<vector<int>> res(m+1, initVec);
        for (int i = 0; i <= m; i++)res[i][0] = 40005;
        for (int i = 0; i <= n; i++)res[0][i] = 40005;
        res[1][1] = grid[0][0];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == 1 && j == 1)continue;
                res[i][j] = grid[i-1][j-1] + min(res[i-1][j], res[i][j-1]);
            }
        }
        return res[m][n];
    }
};


int main() {
    return 0;
}