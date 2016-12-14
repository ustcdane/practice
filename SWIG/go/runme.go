// c++ can be used from GO using SWIG
package main

import (
	sayHi "$PROJNAME/module"
	"fmt"
	"strconv"
)

func main() {
	fmt.Printf("Creating Test object.\n")
	test := sayHi.NewTest()

	fmt.Printf("test size:%d\n", test.GetSize())

	for i := 0; i < 10; i++ {
		test.Push(strconv.Itoa(i))
	}
	
	fmt.Printf("test size:%d\n", test.GetSize())
	for i := 0; i < 10; i++ {
		fmt.Printf("index = %d \t%s\n", i, test.Get(i))
	}

}
