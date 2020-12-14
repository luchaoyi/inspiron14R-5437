package references

type NEW struct{base.Index16Instruction}


//new 指令通过索引从常量池找到一个类符号引用，解析类符号引用，拿到类数据，在堆中创建对象,并将对象引用压入栈顶
func (self *NEW) Execute(frame *rtda.Frame){
	cp:=frame.Method().Class().ConstantPool()
	classRef:=cp.GetConstant(self.Index).(*heap.ClassRef)
	class:=classRef.ResolvedClass()

	//接口和抽象类不能new
	if class.IsInterface() || class.IsAbstract(){
		panic("java.lang.InstantiationError")
	}

	ref:=class.NewObject()
	frame.OperandStack().PushRef(ref)
}

func (self *Class) NewObject() *Object{
	return newObject(self)
}

func newObject(class *Class) *Object{
	return &Object{
		class:class,
		fields:newSlots(class.instanceSlotCount)
	}
}

//S类型引用的值可以赋值给T类型:
//1.S和T同类型，2.S是T子类 3.T是接口，S实现了接口
