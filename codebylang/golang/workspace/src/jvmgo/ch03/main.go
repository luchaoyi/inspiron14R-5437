package main

import "fmt"
import "strings"

import "jvmgo/ch03/classpath" 
import "jvmgo/ch03/classfile"



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
	className:=strings.Replace(cmd.class,".","/",-1)

	//ch03
	cf:=loadClass(className,cp)
	fmt.Println(cmd.class)
	printClassInfo(cf)
}


func loadClass(className string,*classpath.ClassPath) *classfile.ClassFile{
	classData,_,err := cp.ReadClass(className)
	if err != nil{
		panic(err)
	}
	return cf
}

func printClassInfo(cf *classfile.ClassFile){
	fmt.Printf("version:%v.%v\n",cf.MajorVersion(),cf.MinorVersion())
	fmt.Printf("constants count:%v\n",len(cf.Constantpool()))
	fmt.Printf("access flags:0x%x\n"cf.AccessFlags())
	fmt.Printf("this class:%v\n",cf.ClassName())
	fmt.Printf("super class:%v\n",cf.SuperClassName())
	fmt.Printf("interfaces:%v\n",cf.InterfaceNames())

	fmt.Printf("fields count:%v\n",len(cf.Fields()))
	for _,f:=range cf.Fields(){
		fmt.Printf("  %s\n",f.Name())
	}

	fmt.Printf("methods count:%v\n",len(cf.Methods()))
	for _,m:=range cf.Methods(){
		fmt.Printf("  %s\n",m.Name())
	}

}
