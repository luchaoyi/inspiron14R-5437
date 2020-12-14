package main

import (
"fmt"
"time"
)


func main(){
	tick:=time.Tick(1*time.Second) //一个返回时间戳的定时器,tick是一个管道，启动后每秒可以接受一个时间戳


	//倒计时10s发射火箭
	for countdown:=10;countdown>0;countdown--{
		fmt.Println(countdown)
		<-tick //这样可以阻塞程序1s
		//fmt.Println(<-tick)
	}

	launch()
}



func launch(){
	fmt.Println("->")
}
