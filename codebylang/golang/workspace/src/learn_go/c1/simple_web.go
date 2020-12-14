package main

import (
"fmt"
"net/http"
"log"
"sync"
)



var count int
var mu sync.Mutex

func main(){
	http.HandleFunc("/",handler)
	http.HandleFunc("/counter",counter)
	log.Fatal(http.ListenAndServe("localhost:8000",nil))
}

func handler(w http.ResponseWriter,r *http.Request){
	//Request对象包装了前端的请求
	//服务器应答写入到w对象，则会展示在前端
	fmt.Fprintf(w,"URL.Path=%q\n",r.URL.Path)
	mu.Lock()
	count++
	mu.Unlock()
}


func counter(w http.ResponseWriter,r *http.Request){
	mu.Lock()
	fmt.Fprintf(w,"Count %d\n",count)
	mu.Unlock()
}

