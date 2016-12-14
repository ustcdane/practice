// https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/06.9.md
// 返回值为函数的函数 工厂函数

package main

import (
	"fmt"
	"strings"
)

func main() {
	addBmp := MakeAddSuffix(".bmp")
	addJpg := MakeAddSuffix(".jpg")

	fmt.Println(addBmp("file")) // returns: file.bmp
	fmt.Println(addJpg("file")) // returns: file.jpg
}

func MakeAddSuffix(suffix string) func(string) string {
	return func(name string) string {
		if !strings.HasSuffix(name, suffix) {
			return name + suffix
		}
		return name
	}
}
