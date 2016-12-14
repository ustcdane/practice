// defer test
package main
// https://tiancaiamao.gitbooks.io/go-internals/content/zh/03.4.html
/*
1. defer是在return之前执行的
2. return xxx这一条语句并不是一条原子指令
3. 函数返回的过程是这样的：先给返回值赋值，然后调用defer表达式，
 最后才是返回到调用函数中.
4. defer表达式可能会在设置函数返回值之后，在返回到调用函数之前，
 修改返回值，使最终的函数返回值与你想象的不一致.
5. 其实使用defer时，用一个简单的转换规则改写一下，就不会迷糊了,
 改写规则是将return语句拆成两句写，return xxx会被改写成:
 返回值 = xxx
 调用defer函数
 空的return
*/
import (
	"fmt"
)

func f1() (res int) {// 命名的返回值
	defer func() {
		res++
	}()
	return 0 //return语句不是一条原子调用，return xxx其实是赋值＋ret指令
}

func f2() (res int) {
	t := 5
	defer func() {
		t += 5
	}()
	return t
}

func f3() (res int) {
	defer func(res int) {
		res += 5
	}(res)
	return 1
}

func main() {
	fmt.Printf("f1:%d\n", f1())// 1
	fmt.Printf("f2:%d\n", f2()) // 5
	fmt.Printf("f3:%d\n", f3()) // 1
}
		
