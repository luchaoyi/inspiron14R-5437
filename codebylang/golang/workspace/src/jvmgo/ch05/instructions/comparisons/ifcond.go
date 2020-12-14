package comparisons

//... import
type  IFEQ struct {base.BranchInstruction} //if x==0
//... IFNE IFLT IFLE 与0比较

func (self *IFEQ) Execute(frame,*rdta.Frame) {
	val:=frame.OprandStack().PopInt()
	if val == 0{ //== jump
		base.Branch(frame,self.offset)
	}
}


//数字比较的跳转
func (self *IF_ICMPNE) Execute(frame *rtda.Frame){
	stack:=frame.OprandStack()
	val2:=stack.PopInt()
	val1:=stack.PopInt()
	if val1!=val2 {
		base.Branch(frame,self.Offset)
	}
}

