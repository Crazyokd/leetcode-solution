package leetcode

type ListNode struct {
    Val int
    Next *ListNode
}

// 每相邻k个元素进行反转，而非交换元素
func reverseKGroup(head *ListNode, k int) *ListNode {
    node := head
    for i :=0; i < k; i++ {
        if node == nil {
            return head
        }
        node = node.Next
    }
    newHead := reverse(head, node)
    head.Next = reverseKGroup(node, k)
    return newHead
}
func reverse(first *ListNode, last *ListNode) *ListNode {
    prev := last
    for first != last {
        tmp := first.Next
        first.Next = prev
        prev = first
        first = tmp
    }
    return prev
func strStr(haystack string, needle string) int {
    // j代表needle的索引，i+j代表haystack的索引
    for i := 0; ; i++ {
        for j := 0; ; j++ {
            if j == len(needle) {
                return i
            }
            if i + j == len(haystack) {
                return -1
            }
            if needle[j] != haystack[i+j] {
                break
            }
        }
    }
}
}
