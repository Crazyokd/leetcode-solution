#include<iostream> 
#include<unordered_map> 
#include<cstdlib>
#include<vector>
#include<ctime>

using namespace std;

// https://leetcode-cn.com/problems/insert-delete-getrandom-o1/solution/o1-shi-jian-cha-ru-shan-chu-he-huo-qu-su-rlz2/
class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }
    
    bool insert(int val) {
        // 检查 indices 中是否有 val
        if (indices.count(val)) {
            return false;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        return true;
    }
    
    bool remove(int val) {
        if (!indices.count(val)) {
            return false;
        }
        // 将最后一个元素放入被删除的元素的位置
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        indices[last] = index;
        nums.pop_back();
        indices.erase(val);
        return true;
    }
    
    int getRandom() {
        int randomIndex = rand()%nums.size();
        return nums[randomIndex];
    }
    private:
        vector<int> nums;
        unordered_map<int, int> indices;
};

int main() {
    return 0;
}