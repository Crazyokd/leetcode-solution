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
}
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

func findSubstring(s string, words []string) []int {
    if len(words) == 0 {
        return []int{}
    }
    res := []int{}
    counter := map[string]int{}
    for _, w := range words {
        counter[w]++
    }
    length, totalLen, tmpCounter := len(words[0]), len(words[0])*len(words), copyMap(counter)
    for i, start := 0, 0; i < len(s)-length+1 && start < len(s) - length+1; i++ {
        if tmpCounter[s[i:i+length]] > 0 {
            tmpCounter[s[i:i+length]]--
            if checkWords(tmpCounter) && (i+length-start == totalLen) {
                res = append(res, start)
                continue
            }
            i = i+length-1
        }else {
            start++
            i = start - 1
            tmpCounter = copyMap(counter)
        }
    }
    return res
}

func checkWords(s map[string]int) bool {
    flag := true
    for _, v := range s {
        if v > 0 {
            flag = false
            break
        }
    }
    return flag
}
func copyMap(s map[string]int) map[string]int {
    c := map[string]int{}
    for k, v := range s {
        c[k] = v
    }
    return c
}
