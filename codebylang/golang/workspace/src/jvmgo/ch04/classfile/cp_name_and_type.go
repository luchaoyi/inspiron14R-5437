package classfile

//字段(变量)和方法在class文件中同时包含名字和描述符
//描述符以字符串形式编码，描述了它们的类型信息(字段类型，方法的参数类型，返回类型等信息)
type ConstantNameAndTypeInfo struct {
	nameIndex uint16
	descriptorIndex uint16
}

func (self *ConstantNameAndTypeInfo) readInfo(reader *ClassReader){
	self.nameIndex=reader.readUint16()
	self.descriptorIndex=reader.readUint16()
}
