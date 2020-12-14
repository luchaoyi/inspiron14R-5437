package classfile


// ConstantStringInfo 表示java.lang.String的字面量，ConstantStringInfo位置只存储到常量池的索引，具体的字符串以MUTF8编码存储在常量池
type ConstantStringInfo struct {
	cp ConstantPool
	stringIndex uint16
}

func (self *ConstantStringInfo) readInfo(reader *ClassReader){
	self.stringIndex=reader.readUint16()
}

func (self *ConstantStringInfo) String() string{
	return self.cp.getUtf8(self.stringIndex)
}
