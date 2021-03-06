#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
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


    static const regex pattern;

    bool isNumber(string str) {
        return regex_match(str, pattern);
    }

    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size(), carry = 1;
        for (int i = len-1; i >= 0 && carry; i--) {
            carry = (digits[i]+1)/10;
            digits[i] = (digits[i]+1)%10;
        }
        vector<int> res;
        if (carry) res.push_back(1);
        res.insert(res.end(), digits.begin(), digits.end());
        return res;
    }

    string addBinary(string a, string b) {
        if (a.size() >= b.size()) return addBinaryHelper(a, b);
        return addBinaryHelper(b, a);
    }
    
    string addBinaryHelper(string a, string b) {
        string res = "";
        int tmp, carry = 0;
        // 此处a总是更长的那个字符串
        for (int i = a.size()-1, j = b.size()-1; i >= 0; i--, j--) {
            int t = j < 0 ? '0' : b[j];
            tmp = a[i]+t+carry-2*'0';
            carry = tmp / 2;
            res = to_string(tmp%2) + res;
        }
        if (carry) res = "1" + res;
        return res;
    }

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int curCnt = 0;
        int minSpace = 0;
        for (int i = 0; i < words.size(); i++) {
            // 当前是第一个单词
            int t = curCnt + words[i].length();
            if (t + minSpace > maxWidth) {
                res.push_back(generateRes(words, i, maxWidth - curCnt, minSpace-1, maxWidth));
                curCnt = 0;
                minSpace = 0;
                i--;
                // 不能将当前单词放入当前行
            } else {
                curCnt = t;
                minSpace += 1;
            }
        }

        // 处理最后一行
        string tmp = words[words.size()-minSpace];
        for (int i = words.size()-minSpace+1; i < words.size(); i++) {
            tmp += " "+words[i];
        }
        tmp += string(maxWidth - tmp.length(), ' ');
        res.push_back(tmp);
        return res;
    }
    string generateRes(vector<string>& words, int endIndex, int space, int spaceCnt, int maxWidth) {
        string res = words[endIndex-spaceCnt-1];
        for (int i = endIndex - spaceCnt; i < endIndex; i++) {
            // 产生空格
            for (int j = 0; j < space/spaceCnt; j++) {
                res += " ";
            }
            if (space % spaceCnt) {
                res += " ";
                space -= 1;
            }

            res += words[i];
            space -= space/spaceCnt;
            spaceCnt--;
        }
        if (res.length() < maxWidth) {
            res += string(maxWidth - res.length(), ' ');
        }
        return res;
    }

    int mySqrt1(int x) {
        return sqrt(x);
    }
    int mySqrt2(int x) {
        if (x == 1)return x;
        int low = 0, high = x > 46341 ? 46341 : x;
        while (high-low > 1) {
            int mid = low + ((high-low) >> 1);
            if (mid*mid == x)return mid;
            if (mid*mid > x) high = mid;
            else low = mid;
        }
        return low;
    }

    int climbStairs(int n) {
        vector<int> res(n+2, 0);
        res[0] = 1;
        for (int i = 0; i < n; i++) {
            res[i+1] += res[i];
            res[i+2] += res[i];
        }
        return res[n];
    }
};

const regex Solution::pattern("[+-]?(?:\\d+\\.?\\d*|\\.\\d+)(?:[Ee][+-]?\\d+)?");


int main() {
    Solution s;
    // cout << s.addBinary("0", "0");
    // cout << s.mySqrt2(8);

    // vector<string> words =  {"This", "is", "an", "example", "of", "text", "justification."}; 
    // vector<string> words = {"What","must","be","acknowledgment","shall","be"};
    vector<string> words = {"ask","not","what","your","country","can","do","for","you","ask","what","you","can","do","for","your","country"};
    s.fullJustify(words, 16);

    for (auto i : s.fullJustify(words, 16)) {
        cout << i << endl;
    }
    return 0;
}