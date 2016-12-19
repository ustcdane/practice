// 利用flag处理命令行参数

package main
import (
	"fmt"
	"flag"
)

func main() {
	flagT()
}

func flagT() {
	// 第一个参数是“参数名”，第二个是“默认值”，第三个是“说明”。
	// 返回的是指针.
	ip := flag.String("ip", "127.0.0.1", "It's a ip.")
	port := flag.Int("port", 80, "a port number.")

	// parse command
	flag.Parse()

	fmt.Println("ip:", *ip)
	fmt.Println("port:", *port)
}
