package main

import (
"fmt"
"os"
"math"
"learn_go/c1/test"  //从此导入路径导入了一个包，包名字叫word
"log"
)




type Color struct{
	r uint8
	g uint8
	b uint8
}

type Point struct{
	x int32 
	y int32
	Color   //结构体嵌入
}


func main(){
	fmt.Printf("hello,world!\n")
	//fmt.Println("hello,world!")

	var s string
	sep:=" "

	for i:=1;i<len(os.Args);i++{
		s+=os.Args[i]+sep
	}

	fmt.Println(s)
	var a int
	var i int
	i++
	a=i


	fmt.Println(word.IsPalindrome("abba"))  //learn_go/c1/test 路径下文件声明为 package word, import 是导入路径不是包名

	fmt.Println(a)
	fmt.Println(math.MaxFloat32)
	fmt.Println(math.MaxFloat64)
	fmt.Println(5^2) //^ is /xor go 没有幂运算符


log.Println("message")
// Fatalln 在调用 Println()之后会接着调用 os.Exit(1)
//log.Fatalln("fatal message")
// Panicln 在调用 Println()之后会接着调用 panic()
//log.Panicln("panic message")


//-------------
	var p Point
	p.x=1
	p.y=2
	p.r=0xff
	p.g=0x0f
	p.b=0xf0

	fmt.Printf("x:%d,y:%d,color:%d,%d,%d\n",p.x,p.y,p.r,p.g,p.b)

}












