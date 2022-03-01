package leetcode

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
