package classfile


type MemberInfo struct{
	cp ConstantPool
	accessFlags uint16
	nameIndex uint16
	descriptorIndex uint16
	attributes []AttributeInfo
}

//读取fields or methods 的表
func readMembers(reader *ClassReader,cp ConstantPool) []*MemberInfo{
	memberCount:=reader.readUint16()
	members:=make([]*MemberInfo,memberCount)
	for i:=range members{
		members[i]=readMember(reader,cp)
	}
	return members
}

func readMember(reader *ClassReader,cp ConstantPool) *MemberInfo{
	return &MemberInfo{
		cp: cp,
		accessFlags : reader.readUint16(),
		nameIndex : reader.readUint16(),
		descriptorIndex: reader.readUint16(),
		attributes : readAttributes(reader,cp), //解析属性
	}
}




//Getter
//根据nameIndex在常量池寻找字段名和方法名
func (self *MemberInfo) Name() string{
	return self.cp.getUtf8(self.nameIndex)
}

//常量池寻找描述符
func (self *MemberInfo) Descriptor() string{
	return self.cp.getUtf8(self.descriptorIndex)
}


