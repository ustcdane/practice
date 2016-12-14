// fetchall fetches urls in parallel and report their times and sizes

package main

import (
	"fmt"
//	"io"
	"io/ioutil"
	"net/http"
	"os"
	"time"
)

func main() {
	start := time.Now()
	ch := make(chan string)
	for _, url := range os.Args[1:] {
		go fetch(url, ch)// start a goroutine
	}
	for range os.Args[1:] {
		fmt.Println(<-ch)// receive from channel ch
	}
	fmt.Printf("%.2fs elapsed\n", time.Since(start).Seconds());
}


func fetch(url string, ch chan<- string) {
	start := time.Now()
	res, err := http.Get(url)
	if err !=nil {
		ch <- fmt.Sprint(err) // send to channel ch
		return
	}
	//nbytes, err := io.Copy(ioutil.Discard, res.Body)
	body, err := ioutil.ReadAll(res.Body)
	res.Body.Close()// don't leak resouces
	if err != nil {
		ch <- fmt.Sprintf("while read %s: %v", url, err)
		return
	}

	secs := time.Since(start).Seconds()
	//ch <- fmt.Sprintf("%.2fs %7d %s", secs, nbytes, url)
	ch <- fmt.Sprintf("%.2fs\n%s:\n%s", secs, url, body)
}
