package classfile

//tag常量定义，tag用于区分常量类型
const(
	CONSTANT_Class=7
	CONSTANT_Fieldref=9
	CONSTANT_Methodref=10
	CONSTANT_InterfaceMethodref=11
	
	CONSTANT_String=8
	CONSTANT_Integer=3
	CONSTANT_Float=4
	CONSTANT_Long=5
	CONSTANT_Double=6
	CONSTANT_NameAndType=12
	CONSTANT_Utf8=1
	CONSTANT_MethodHandle=15
	CONSTANT_MethodType=16
	CONSTANT_InvokeDynamic=18
)

//readInfo读取常量信息，不同类型读法不同
type ConstantInfo interface{
	readInfo(reader *ClassReader)
}

func readConstantInfo(reader *ClassReader,cp *ConstantPool) ConstantInfo{
	tag:=reader.readUint8() //u1 tag
	c:=newConstantInfo(tag,cp)
	c.readInfo(reader)
	return c
}
//工厂模式，根据tag生成不同的类型

func newConstantInfo(tag uint8,cp *ConstantPool) ConstantInfo{
	switch tag{
	case CONSTANT_Integer:
		return &ConstantIntegerInfo{}
	case CONSTANT_Float:
		return &ConstantFloatInfo{}
	case CONSTANT_Long:
		return &ConstantLongInfo{}
	case CONSTANT_Utf8:
		return &ConstantUtf8Info{}
	case CONSTANT_String:
		return &ConstantStringInfo{cp: cp}
	case CONSTANT_Class:
		return &ConstantClassInfo{cp: cp}
	//ref代表了对别的类的字符，方法，接口的引用信息，不是本类自定义
	case CONSTANT_Fieldref:
		return &ConstantFieldrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_Methodref:
		return &ConstantMethodrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_InterfaceMethodref:
		return &ConstantInterfaceMethodrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_NameAndType:
		return &ConstantNameAndTypeInfo{}

		/*
	case CONSTANT_MethodType:
		return &ConstantMethodTypeInfo{}
	case CONSTANT_MethodHandle:
		return &ConstantMethodHandleInfo{}
	case CONSTANT_InvokeDynamic:
		return &ConstantInvokeDynamicInfo{}
		*/
	default:
		panic("java.lang.ClassFormatError:constant pool tag")
	}

}


