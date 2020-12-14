package base

func Branch(frame *rtda.Frame,offset int){
	pc:=frame.Thread().PC()
	nextPC:=pc+offset
	frame.setNextPC(nextPC)
}
