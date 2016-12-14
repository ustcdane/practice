// http://coolshell.cn/articles/8489.html

package main

import (
	"fmt"
//	"time"
)

func main() {
	fmt.Printf("Call closeTest: %v\n", closeTest())
}

// https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/06.9.md
// 在闭包中使用到的变量可以是在闭包函数体内声明的，也可以是在外部函数声明的
// http://coolshell.cn/articles/8489.html
func closeTest() int {
	var g int
	channel := make(chan int)
	go func(i int) {// goroutine
		s :=0
		for j :=0; j < i; j++ {
			s += j
		}
		g = s
		//fmt.Printf("g: %v\n", g)
		channel <- s
	}(10)
	
	// //让主进程停住，不然主进程退了，goroutine也就退了
	// time.Sleep(time.Second)
	// channel默认上是阻塞的 如果Channel满了，就阻塞写，如果Channel空了，就阻塞读
	// 我们就可以使用这种特性来同步我们的发送和接收端
	chanG := <- channel // channel默认上是阻塞的

	if chanG == g {
		fmt.Printf("yes, use channel success!!\n")
	}

	return g
}
