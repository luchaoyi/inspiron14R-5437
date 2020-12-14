package math

import "math"
import "jvmgo/ch05/instructions/base"
import "jvmgo/ch05/rtda"

//求余指令
type DREM struct {base.NoOperandsInstruction} //double
type FREM struct {base.NoOperandsInstruction} //float 
type IREM struct {base.NoOperandsInstruction} //int 
type LREM struct {base.NoOperandsInstruction} //long

//栈式机器

func (self *IREM) Execute(frame *rtda.Frame){
	stack:=frame.OperandStack()
	v2:=stack.PopInt()
	v1:=stack.PopInt()

	if v2==0{
		panic("java,lang.ArithmeticException: / by zero")
	}

	result :=v1%v2
	stack.PushInt(result)
}

//go 语言的%没有定义浮点数取余，因此使用math.Mod()
func (self *IREM) Execute(frame *rtda.Frame){
	stack:=frame.OperandStack()
	v2:=stack.PopDouble()
	v1:=stack.PopDouble()
	//浮点数无穷大
	result :=math.Mod(v1,v2) 
	stack.PushDouble(result)
}
