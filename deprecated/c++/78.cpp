#include<iostream>

using namespace std;

class Solution {
public:
    // bool reachingPoints(int sx, int sy, int tx, int ty) {
    //     return dfs(sx, sy, tx, ty);
    // }

    // bool dfs(int x, int y, int tx, int ty) {
    //     if (x == tx && y == ty)
    //         return true;
    //     if (x > tx || y > ty) 
    //         return false;

    //     bool ans1, ans2;
    //     if (tx > x) {
    //         ans1 = dfs(x+y, y, tx, ty);
    //     }
    //     if (ty > y) {
    //         ans2 = dfs(x, x+y, tx, ty);
    //     }
    //     return ans1 || ans2;
    // }

    // 参考链接：https://leetcode-cn.com/problems/reaching-points/solution/dao-da-zhong-dian-by-leetcode-solution-77fo/
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx > sx && ty > sy && tx != ty) {
            if (tx > ty) {
                tx %= ty;
            } else {
                ty %= tx;
            }
        }
        if (tx == sx && ty == sy) {
            return true;
        } else if (tx == sx) {
            return ty > sy && (ty - sy) % tx == 0;
        } else if (ty == sy) {
            return tx > sx && (tx - sx) % ty == 0;
        } else {
            return false;
        }
    }
};

int main() {
    return 0;
}