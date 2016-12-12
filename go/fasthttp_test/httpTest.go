// test fasthttp

package main

import (
	//module "$PROJNAME/module"
	"fmt"
//	fasthttp "github.com/valyala/fasthttp"
	"github.com/valyala/fasthttp"
	"log"
	"os"
)


var (
	ip string
	port string
)
// requestHandler, RequestCtx 传递HTTP数据
func httpHandler(ctx *fasthttp.RequestCtx) {
	fmt.Fprintf(ctx, "\t\thello fasthttp, have fun!\n")// use *RequestCtx io.Writer
	log.Printf("uri:%s", string(ctx.Path()))
}

// main ip port
func main() {
	if len(os.Args) != 3 {
		fmt.Printf("args error!\n\tuse:%s ip port\n", os.Args[0])
		return
	}
	ip = os.Args[1]
	port = os.Args[2]
	addr := ip + ":" + port
	if err := fasthttp.ListenAndServe(addr, httpHandler); err != nil {
		fmt.Printf("start fasthttp fial:%v", err)
	}
}

