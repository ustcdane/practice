// os and 系统调用
// http://coolshell.cn/articles/8489.html

package main

import (
	"fmt"
	"os/exec"
)

func execT() {
	cmd := exec.Command("ping", "-c 1", "127.0.0.1")
	out, err := cmd.Output()
	if err != nil {
		fmt.Printf("Commond Error: %v.\n", err.Error())
		return
	}
	fmt.Printf("%v\n", string(out))
}

func main() {
	execT()
}
