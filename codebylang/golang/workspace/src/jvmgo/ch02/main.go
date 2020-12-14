package main

import "fmt"
import "strings"
import "jvmgo/ch02/classpath"

// go install jvmgo/ch02
//./ch02 -Xjre /usr/local/lib/java/jdk7/jre java.lang.Object


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
	cp:=classpath.Parse(cmd.XjreOption,cmd.cpOption)
	fmt.Printf("classpath:%s,class:%s,args:%v\n",cp,cmd.class,cmd.args)

	className:=strings.Replace(cmd.class,".","/",-1)
	classData,_,err:=cp.ReadClass(className)

	if err!=nil{
		fmt.Printf("Could not find or load main class %s\n",cmd.class)
		return 
	}
	fmt.Printf("class data:%v\n",classData)
}
