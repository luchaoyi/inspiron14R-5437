package main

import (
"os/exec"
"syscall"
"os"
"log"
)


func main(){
	cmd:=exec.Command("sh") //执行sh 

/*
	cmd.SysProcAttr=&syscall.SysProcAttr{
		Cloneflags:syscall.CLONE_NEWUTS,  //CLONE_NEWUTS标志创建uts namespace
	}//创建SysProcAttr类型变量
*/
	cmd.SysProcAttr=&syscall.SysProcAttr{
		Cloneflags:syscall.CLONE_NEWUTS|syscall.CLONE_NEWIPC|syscall.CLONE_NEWPID|
		syscall.CLONE_NEWNS|
		syscall.CLONE_NEWUSER|syscall.CLONE_NEWNET,
	}//创建SysProcAttr类型变量 


	cmd.SysProcAttr.Credential=&syscall.Credential{Uid:uint32(1),Gid:uint32(1)}

	cmd.Stdin=os.Stdin
	cmd.Stdout=os.Stdout
	cmd.Stderr=os.Stderr

	//cmd.Run正式运行命令
	//Run封装了clone调用
	//clone函数创建新进程，并根据参数来创建namespace，它的子进程也被包含到这些namespace中
	if err:=cmd.Run();err!=nil{
		log.Fatal(err)

	}

	os.Exit(-1)
}


/*创建不同的namespace,标志位不同*/
