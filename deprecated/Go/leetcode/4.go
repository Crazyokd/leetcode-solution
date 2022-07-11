package leetcode

import "sort"

func search(nums []int, target int) int {
    low, high := 0, len(nums)-1
    for low <= high {
        mid := low + (high-low)>>1
        if nums[mid] == target {
            return mid
        } else if nums[mid] > nums[low] {
            // 在数值⼤的⼀部分区间⾥
            if nums[low] <= target && target < nums[mid] {
                high = mid - 1 
            } else {
                low = mid + 1 
            } 
        } else if nums[mid] < nums[high] {
            // 在数值⼩的⼀部分区间⾥
            if nums[mid] < target && target <= nums[high] {
                low = mid + 1 
            } else {
                high = mid - 1 
            } 
        } else {
            if nums[low] == nums[mid] {
                low++ 
            }
            if nums[high] == nums[mid] {
                high-- 
            } 
        } 
    } 
    return -1
}
func isValidSudoku(board [][]byte) bool {
    rowbuf, colbuf, boxbuf := make([][]bool, 9), make([][]bool, 9), make([][]bool, 9)
    for i := 0; i < 9; i++ {
        rowbuf[i] = make([]bool, 9)
        colbuf[i] = make([]bool, 9)
        boxbuf[i] = make([]bool, 9)
    }
    // 遍历一次，添加缓存
    for r := 0; r < 9; r++ {
        for c:= 0; c < 9; c++ {
            if board[r][c] != '.' {
                num := board[r][c] - '0' - byte(1)
                if rowbuf[r][num] || colbuf[c][num] || boxbuf[r/3*3+c/3][num] {
                    return false
                }
                rowbuf[r][num] = true
                colbuf[c][num] = true
                boxbuf[r/3*3+c/3][num] = true
            }
        }
    }
    return true
}

func combinationSum(candidates []int, target int) [][]int {
    if len(candidates) == 0 {
        return [][]int{}
    }
    c, res := []int{}, [][]int{}
    sort.Ints(candidates)
    findcombinationSum(candidates, target, 0, c, &res)
    return res
}

func findcombinationSum(nums []int, target, index int, c []int, res *[][]int) {
    if target <= 0 {
        if target == 0 {
            b := make([]int, len(c))
            copy(b, c)
            *res = append(*res, b)
        }
        return 
    }
    for i := index;i < len(nums); i++ {
        if nums[i] > target {
            break
        }
        c = append(c, nums[i])
        findcombinationSum(nums, target-nums[i], i, c, res)
        c = c[:len(c)-1]
    }
}