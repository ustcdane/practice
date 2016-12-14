// a mini echo server
package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/",handler) // each request calls handler
	log.Fatal(http.ListenAndServe("localhost:8080", nil))
}

// handler echoes
func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
}
