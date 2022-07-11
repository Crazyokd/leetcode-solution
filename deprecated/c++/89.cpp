#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        // 顶部 元素数量
        // 前面 每一个vector的最大值
        // 侧面 每一列的最大值
        int topArea = grid.size()*grid.size();
        int frontArea = 0;
        for (int i = 0; i < grid.size(); i++) {
            int maxCol = 0;
            for (int j = 0; j < grid[i].size(); j++) {
                if (!grid[i][j]) topArea--;
                maxCol = max(maxCol, grid[i][j]);
            }
            frontArea += maxCol;
        }
        int sideArea = 0;
        for (int i = 0; i < grid.size(); i++) {
            int maxRow = 0;
            for (int j = 0; j < grid[i].size(); j++) {
                maxRow = max(maxRow, grid[j][i]);
            }
            sideArea += maxRow;
        }
        return topArea + frontArea + sideArea;
    }
};

int main() {
    return 0;
}