package rdta

type Frame struct {
	lower *Frame
	localVars LocalVars //保存局部变量表
	operandStack *OperandStack//保存操作数栈
}

func NewFrame(maxLocals,maxStack uint) *Frame{
	return &Frame{
		localVars : newLocalVars(maxLocals),
		operandStack: newOperandStack(maxStack),
	}
}
