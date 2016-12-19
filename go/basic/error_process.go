// go 内建的错误处理-Error接口
// 内建接口
// http://coolshell.cn/articles/8460.html
/*
type error interface {
	Error() string
}
*/

package main

import (
	"fmt"
	"errors"
)
// 自定义出错接口
type myError struct {
	arg int
	errMsg string
}

// 实现Error接口
func (e *myError) Error() string {
	return fmt.Sprintf("%d - %s", e.arg, e.errMsg)
}

// 调用错误接口
func isPostiveAndLess256(arg int) (int, error) {
	if arg < 0 {
		return -1, errors.New("Bad Arg - negtive!")
	} else if arg > 255 {
		return -1, &myError{arg, "Bad Arg - too large!"}
	}
	return arg, nil
}

func main() {
	for _, i := range []int{-1, 200, 1000} {
		if r, err := isPostiveAndLess256(i); err != nil {
			fmt.Printf("Failed: %v\n", err)
		} else {
			fmt.Printf("success: %v\n", r)
		}
	}
}
