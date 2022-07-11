package main

import "fmt"
import "rekord/leetcode"

func main() {
    fmt.Println("Hello, World!")
    array := []int{2,7,11,15}
    fmt.Println(leetcode.TwoSum(array,9))
    //初始化为false
    var bitSet [256]bool
    fmt.Println(bitSet[1],bitSet[2])
    arr1 := []int{1,3}
    arr2 := []int{2,7}
    fmt.Println(leetcode.FindMedianSortedArrays(arr1,arr2))
    fmt.Println(leetcode.MyAtoi("    0000000000000   "))
}