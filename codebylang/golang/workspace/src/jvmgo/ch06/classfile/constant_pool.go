package classfile

type ConstantPool struct {
	cf      *ClassFile
	cpInfos []ConstantInfo
}


//常量池存储各种常量信息，包括类，接口(类和接口都看作类型字面量)
//常量池是一个表，表头大小为n
//表索引0-n-1,0不使用，不指向任何常量。因此实际是1-n-1
func (self *ConstantPool)readConstantPool(reader *ClassReader) {
	cpCount:=int(reader.readUint16())
	self.cpInfos =make([]ConstantInfo,cpCount)

	for i:=1;i<cpCount;i++{
		self.cpInfos[i]=readConstantInfo(reader,self)
		switch self.cpInfos[i].(type){ //类型switch -> switch v.(type)
			case *ConstantLongInfo,*ConstantDoubleInfo:
				i++ //占两个位置
		}
	}
}

func (self ConstantPool) getConstantInfo(index uint16) ConstantInfo{
	if cpInfo:=self[index];cpInfo!=nil{
		return cpInfo
	}
	panic("Invaild constant pool index!")
}

//查找字段或方法的名字和描述符
func (self ConstantPool) getNameAndType(index uint16) (string,string){
	ntInfo :=self.getConstantInfo(index).(*ConstantNameAndTypeInfo)
	name:=self.getUtf8(ntInfo.nameIndex)
	_type:=self.getUtf8(ntInfo.descriptorIndex)
	return name,_type
}

func (self ConstantPool) getClassName(index uint16) string{
	classInfo:=self.getConstantInfo(index).(*ConstantClassInfo)
	return self.getUtf8(classInfo.nameIndex)
}

func (self ConstantPool) getUtf8(index uint16) string{
	utf8Info :=self.getConstantInfo(index).(*ConstantUtf8Info)
	return utf8Info.str
}
