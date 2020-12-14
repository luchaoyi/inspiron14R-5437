package main

import "flag"
import "fmt"
import "os"

//go包提供，常量，变量，结构体，函数等 
//定义结构体表示命令行参数
type Cmd struct{
	helpFlag bool
	versionFlag bool
	cpOption string 
	XjreOption string //ch02
	class string
	args []string
}



func printUsage(){
	fmt.Printf("Usag:%s [-option] class [args...]\n",os.Args[0])
}


//os.Args提供命令行参数(类似python sys.argv),flag包提供更好的处理命令行

func parseCmd() *Cmd{
	cmd:=&Cmd{}

	flag.Usage=printUsage //设置callback func flag解析失败时调用
	//设置解析信息
	flag.BoolVar(&cmd.helpFlag,"help",false,"print help message")
	flag.BoolVar(&cmd.helpFlag,"?",false,"print help message")
	flag.BoolVar(&cmd.versionFlag,"version",false,"print version and exit")
	flag.StringVar(&cmd.cpOption,"classpath","","classpath")
	flag.StringVar(&cmd.cpOption,"cp","","classpath")

	flag.StringVar(&cmd.XjreOption,"Xjre","","path to jre") //ch02 指定启动类路径

	//按顺序提取，前面参数以指定类型被提取到了指定位置，剩余的参数flag.Args()返回到一个列表中
	flag.Parse() //参数解析
	args:=flag.Args()

	if len(args)>0 {
		cmd.class=args[0]
		cmd.args=args[1:]
	}
	return cmd

}
