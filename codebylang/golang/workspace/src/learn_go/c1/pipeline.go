package main 
//串联chan形成一个pipeline

import (
"fmt"
)


func main(){
	naturals:=make(chan int)  //chan int整体是一个类型,物缓存chan
	squares:=make(chan int)


	//Counter
	go func(){
		for x:=0;x<=100;x++{
			naturals<-x //x写入chan 
		}
		close(naturals)
	}()


	//Squarer
	go func(){
		for x:=range naturals{
			squares<-x*x
		}
		close(squares)
	}()


	/*
	Go语言的range循环可直接在channels上面迭代。使用range循环是下面处理模式的简洁语法,它依次从channel接收数据,当channel被关闭并且没有值可接收时跳出循环
	go func(){
		for{
			x,ok:= <- naturals
			if !ok  //channels已经被关闭并且里面没有值可接收
			{
				break
			}
			squares<- x*x
		}

		close(squares)
	}()
*/

	
	//Printer in main goroutine
	for x:=range squares{
		fmt.Println(x)
	}

}












