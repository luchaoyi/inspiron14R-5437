package main

import "fmt"

//go install jvmgo/ch01
//./ch01  -cp /foo/bar MyApp arg1 arg2

func main(){
	version:="0.0.1"
	cmd:=parseCmd()
	if cmd.versionFlag{
		fmt.Printf("version %s",version)
	}else if cmd.helpFlag || cmd.class == "" {
		printUsage()
	}else{
		startJVM(cmd)
	}
}

//变量 类型
func startJVM(cmd *Cmd){
	fmt.Printf("classpath:%s,class:%s,args:%v\n",cmd.cpOption,cmd.class,cmd.args)
}
