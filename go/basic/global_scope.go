// test global local var scope

package main

var a = "G"
// a := "G" or a = "G" are error

func main() {
	m()
	n()
	m()
}

func m() {
	print(a)
}

func n() {
	a := "O" // := 只能用在函数体内
	print(a)
}
