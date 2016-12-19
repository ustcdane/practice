// 多个channel的select
// http://coolshell.cn/articles/8489.html

package main

import (
	"fmt"
	"time"
)

// 创建两个channel
func make2Chans() (C1,C2 chan string) {
	c1 := make(chan string)
	c2 := make(chan string)
	return c1, c2
}

// 创建两个goruntine来分别向两个channel发送数据
// 有阻塞利用for
func twoChanWithSelect() {
	
	c1, c2 := make2Chans()
	send := func(times int, msg string, c chan string) {
		time.Sleep(time.Duration(times)*time.Second)
		c <- msg
	}
	go send(1, "first chan", c1)
	go send(1, "second chan", c2)

	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-c1:
			fmt.Printf("receve %s from c1.\n", msg1)
		case msg2 := <-c2:
			fmt.Printf("receve %s from c2.\n", msg2)
		}
	}
}

// 创建两个goruntine来分别向两个channel发送数据
// 阻塞但有timeout
func twoChanWithSelectWithTimeout() {
	
	c1, c2 := make2Chans()
	send := func(times int, msg string, c chan string) {
		time.Sleep(time.Duration(times)*time.Second)
		c <- msg
	}
	go send(2, "first chan", c1)
	go send(2, "second chan", c2)

	timeout_cnt := 0
	for {
		select {
		case msg1 := <-c1:
			fmt.Printf("receve %s from c1.\n", msg1)
		case msg2 := <-c2:
			fmt.Printf("receve %s from c2.\n", msg2)
		case <-time.After(time.Second * 1):
			timeout_cnt++
			fmt.Printf("Time out %d seconds\n", 1 * timeout_cnt)
		}
		if timeout_cnt > 3 {
			break
		}
	}
}

// 创建两个goruntine来分别向两个channel发送数据
// 无阻塞的channel
func twoChanWithSelectDefault() {
	
	c1, c2 := make2Chans()
	send := func(times int, msg string, c chan string) {
		time.Sleep(time.Duration(times)*time.Second)
		c <- msg
		
		close(c)
	}
	go send(1, "first chan", c1)
	go send(1, "second chan", c2)
	
	var more bool = true
	var msg1, msg2 string
	for more {
		select {
		case msg1, more = <-c1:
			fmt.Printf("receve %s from c1.\n", msg1)
		case msg2, more = <-c2:
			fmt.Printf("receve %s from c2.\n", msg2)
		default: //default会导致无阻塞
			fmt.Printf("nothing reveived...\n")
			time.Sleep(time.Second)
		}
	}
}

func main() {
	fmt.Printf("2 channel by using for.. .\n")
	twoChanWithSelect()
	
	fmt.Printf("\n2 channel by using for time out.\n")
	twoChanWithSelectWithTimeout()

	fmt.Printf("\n2 channel by using default.\n")
	twoChanWithSelectDefault()
}


