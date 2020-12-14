package main

import (
"fmt"
"time"
"os"
)


func main(){
	abort:=make(chan struct{})

	go func(){
		os.Stdin.Read(make([]byte,1))
		abort<- struct{}{}
	}()

	tick:=time.Tick(1*time.Second) //一个返回时间戳的定时器,tick是一个管道，启动后每秒可以接受一个时间戳


	//倒计时10s发射火箭
	for countdown:=10;countdown>0;countdown--{
		select{
		case <-tick:
			fmt.Println(countdown)
		case <-abort:
			fmt.Println("launch aborted!")
			return 
//		default:
			//fmt.Println("default")
		}

	}
	launch()
}



func launch(){
	fmt.Println("->")
}
