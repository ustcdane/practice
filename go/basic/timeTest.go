// 定时器
// http://coolshell.cn/articles/8489.html

package main

import (
	"time"
	"fmt"
)

func timerNotify() {
	timer := time.NewTimer(1*time.Second)

	<- timer.C // 通过channel的阻塞通知机器来通知
	// 只通知了一次
	fmt.Printf("time expired!\n")
}

func timerContinueNotify() {
	ticker := time.NewTicker(1*time.Second)

	go func () {
		for t:= range ticker.C {
			fmt.Printf("Tick at %v\n", t)
		}
	}()

	//设置timer 10s stop ticker

	timer := time.NewTimer(10*time.Second)
	<-timer.C

	ticker.Stop()
	fmt.Printf("timer expired.")
}

func main() {
	fmt.Printf("one time.\n")
	timerNotify()
	fmt.Printf("mulicate times...\n")
	timerContinueNotify()
}



