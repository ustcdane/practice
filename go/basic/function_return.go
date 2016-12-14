// 将函数作为返回值
// https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/06.9.md
package main

import (
	"fmt"
	"time"
)

func main() {
	p := Add2()
	fmt.Printf("Call Add2 for 3 gives: %v\n", p(3))

	f := Adder()
	fmt.Printf("Call Adder return func: %v\n", f(1))
	fmt.Printf("Call Adder return func: %v\n", f(10))
	fmt.Printf("Call Adder return func: %v\n", f(100))
	
	fmt.Printf("Call closeTest: %v\n", closeTest())
}

func Add2() func(a int) int {
	return func (a int) int {
		return a + 2
	}
}
/*
闭包函数保存并积累其中的变量的值，不管外部函数退出与否，
它都能够继续操作外部函数中的局部变量
*/
func Adder() func(int) int {
	var x int
	return func(delta int) int {
		x += delta
		return x
	}
}

// 在闭包中使用到的变量可以是在闭包函数体内声明的，也可以是在外部函数声明的
// http://coolshell.cn/articles/8489.html
func closeTest() int {
	var g int
	go func(i int) {// goroutine
		s :=0
		for j :=0; j < i; j++ {
			s += j
		}
		g = s
		fmt.Printf("g: %v\n", g)
	}(10)
	
	// 让主进程停住，不然主进程退了，goroutine也就退了
	time.Sleep(time.Second)

	return g
}
