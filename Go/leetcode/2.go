package leetcode
import (
	"math"
	"sort"
)

func maxArea(height []int) int{
	max,start,end := 0,0,len(height)-1
	for start < end{
		width := end - start
		high := 0
		if height[start] < height[end]{
			high = height[start]
			start++
		}else{
			high = height[end]
			end--
		}

		t := width*high
		if t > max{
			max = t
		}
	}
	return max
}

func intToRoman(num int) string {
    values := []int{1000,900,500,400,100,90,50,40,10,9,5,4,1}
	symbols := []string{"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}
	res,i := "",0
	for num != 0{
		for values[i] > num{
			i++
		}
		num -= values[i]
		res += symbols[i]
	} 
	return res
}

func romanToInt(s string) int {
	if s==""{
		return 0;
	}
	var roman = map[string]int{
		"I":1,
		"V":5,
		"X":10,
		"L":50,
		"C":100,
		"D":500,
		"M":1000,
	}
	num,lastint,total := 0,0,0
	for i:=0;i<len(s);i++{
		char := s[len(s)-(i+1):len(s)-i]
		num = roman[char]
		if num < lastint{
			total = total - num
		}else{
			total = total + num
		}
		lastint = num
	}
	return total
}

//最优解，双指针 + 排序
func threeSum(nums []int) [][]int {
    sort.Ints(nums)
	result,start,end,index,addNum,length := make([][]int,0),0,0,0,0,len(nums)
	for index = 1;index < length - 1;index++{
		start,end = 0,length-1
		if index > 1 && nums[index] == nums[index-1]{
			start = index -1
		}
		for start < index && end > index{
			if start > 0 && nums[start] == nums[start-1]{
				start++
				continue
			} 
			if end < length-1 && nums[end] == nums[end+1]{
				end--
				continue
			}
			addNum = nums[start] + nums[end] + nums[index]
			if addNum == 0{
				result = append(result,[]int{nums[start],nums[index],nums[end]})
				start++
				end--
			}else if addNum > 0{
				end--
			}else{
				start++
			}
		}
	}
	return result
}

//解法二
func threeSum1(nums []int) [][]int{
	res := [][]int{}
	counter := map[int]int{}
	for _,value := range nums{
		counter[value]++
	}

	uniqNums := []int{}
	for key := range counter{
		uniqNums = append(uniqNums,key)
	}
	sort.Ints(uniqNums)

	for i := 0;i < len(uniqNums);i++{
		if (uniqNums[i]*3 == 0) && counter[uniqNums[i]] >= 3{
			res = append(res,[]int{uniqNums[i],uniqNums[i],uniqNums[i]})
		}
		for j := i+1;j < len(uniqNums);j++{
			if (uniqNums[i]*2+uniqNums[j] == 0) && counter[uniqNums[i]] > 1{
				res = append(res,[]int{uniqNums[i],uniqNums[i],uniqNums[j]})
			}
			if (uniqNums[j]*2+uniqNums[i] == 0) && counter[uniqNums[j]] > 1{
				res = append(res,[]int{uniqNums[i],uniqNums[j],uniqNums[j]})
			}
			c := 0-uniqNums[i] - uniqNums[j]
			if c > uniqNums[j] && counter[c] > 0{
				res =  append(res,[]int{uniqNums[i],uniqNums[j],c})
			}
		}
	}
	return res
}

//解法一O(n^2)
func threeSumClosest(nums []int,target int)int{
	n,res,diff := len(nums),0,math.MaxInt32
	if n > 2{
		sort.Ints(nums)
		for i := 0;i < n-2;i++{
			for j,k := i+1,n-1;j<k; {
				sum := nums[i] + nums[j] + nums[k]
				if abs(sum-target) < diff{
					res,diff = sum,abs(sum-target)
				}
				if sum == target{
					return res
				}else if sum > target{
					k--
				}else{
					j++
				}
			}
		}
	}
	return res
}

//解法二 暴力解法O(n^3)
func threeSumClosest1(nums []int,target int)int{
	res,difference := 0,math.MaxInt16
	for i:=0;i<len(nums);i++{
		for j:=i+1;j<len(nums);j++{
			for k:=j+1;k<len(nums);k++{
				if abs(nums[i]+nums[j]+nums[k]-target) < difference{
					difference = abs(nums[i]+nums[j]+nums[k]-target)
					res = nums[i] + nums[j] + nums[k]
				}
			}
		}
	}
	return res
}
func abs(a int)int{
	if a>0{
		return a
	}
	return -a
}


var (
	letterMap = []string{
		" ",
		"",
		"abc",
		"def",
		"ghi",
		"jkl",
		"mno",
		"pqrs",
		"tuv",
		"wxyz",
	}
	res = []string{}
	final = 0
)

//解法一DFS
func letterCombinations(digits string) []string{
	if digits == ""{
		return []string{}
	}
	res = []string{}
	findCombination(&digits,0,"")
	return res
}

func findCombination(digits *string,index int,s string){
	if index == len(*digits){
		res = append(res,s)
		return 
	}
	num := (*digits)[index]
	letter := letterMap[num-'0']
	for i:=0;i<len(letter);i++{
		findCombination(digits,index+1,s+string(letter[i]))
	}
	return 
}

//解法二 非递归
func letterCombinations_(digits string) []string{
	if digits == ""{
		return []string{}
	}
	index := digits[0]-'0'
	letter := letterMap[index]
	tmp := []string{}
	for i:=0;i<len(letter);i++{
		if len(res) == 0{
			res = append(res,"")
		}
		for j:=0;j<len(res);j++{
			tmp = append(tmp,res[j]+string(letter[i]))
		}
	}
	res = tmp
	final++
	letterCombinations_(digits[1:])
	final--
	if final == 0{
		tmp = res
		res = []string{}
	}
	return tmp
}

//解法三 回溯
var result []string
var dict = map[string][]string{
	"2" : []string{"a","b","c"},
	"3" : []string{"d","e","f"},
	"4" : []string{"g","h","i"},
	"5" : []string{"j","k","l"},
	"6" : []string{"m","n","o"},
	"7" : []string{"p","q","r","s"},
	"8" : []string{"t","u","v"},
	"9" : []string{"w","x","y","z"},
}

func letterCombinationsBT(digits string)[]string{
	result = []string{}
	if digits == ""{
		return result
	}
	letterFunc("",digits)
	return result	
}

func letterFunc(res string,digits string){
	if digits == ""{
		result = append(result,res)
		return 
	}
	 
	k := digits[0:1]
	digits = digits[1:]
	for i:=0;i<len(dict[k]);i++{
		res += dict[k][i]
		letterFunc(res,digits)
		res = res[0:len(res)-1]
	}
}