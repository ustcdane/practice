// a mini echo server
package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
)

var mu sync.Mutex
var count int

func main() {
	http.HandleFunc("/", handler) // each request calls handler
	//log.Fatal(http.ListenAndServe("localhost:8080", nil))
	http.HandleFunc("/count", counter) // each request calls handler
	log.Fatal(http.ListenAndServe("10.134.113.223:8111", nil))
}

// handler echoes
func handler(w http.ResponseWriter, r *http.Request) {
	//html_head := "<html><head><meta http-equiv=\"Content-Language\" content=\"zh-cn\"></head><body>"
	//html_tail := "</body></html>"
	//fmt.Fprintf(w, "%s\nURL.Path = %q\n%s", html_head,r.URL.Path, html_tail)
	fmt.Fprintf(w, "\n\tURL.Path = %s", r.URL.Path)
	mu.Lock()
	count++
	mu.Unlock()
}

// counter echoes the number of calls
func counter(w http.ResponseWriter, r *http.Request) {
	mu.Lock()
	fmt.Fprintf(w, "Count: %d\n", count)
	mu.Unlock()
}
