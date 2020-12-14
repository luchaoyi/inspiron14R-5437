package classfile
import "fmt"

type ClassFile struct {
//	magic uint32 不用存储
	minorVersion uint16
	majorVersion uint16
	constantPool ConstantPool
	accessFlags uint16
	thisClass  uint16
	superClass uint16 //不支持多重继承，只有一个父类
	interfaces []uint16 //支持多个接口
	fields []*MemberInfo //成员
	methods []*MemberInfo //方法
	attributes []AttributeInfo
}

//go语言访问控制只有公开和私有
//大写字母开始为公开，可供其它包访问
//小写字母开始为私有，在包内部使用

//解析数据到ClassFile结构中
//对于有命名的结果，可以按命名变量使用，返回时只使用return就可以
func Parse(classData []byte)(cf *ClassFile,err error){




	defer func(){
		if r:=recover();r!=nil{
			var ok bool
			err,ok=r.(error)
			if !ok{
				err = fmt.Errorf("%v",r)
			}
		}
	}()

	cr:=&ClassReader{classData}
	cf=&ClassFile{}
	cf.read(cr)
	return
}

//解析字节序列到ClassFile结构
func (self *ClassFile) read(reader *ClassReader){
	self.readAndCheckMagic(reader)
	self.readAndCheckVersion(reader)
	self.constantPool=readConstantPool(reader)
	self.accessFlags=reader.readUint16()
	self.thisClass=reader.readUint16()
	self.superClass=reader.readUint16()
	self.interfaces=reader.readUint16s()
	self.fields=readMembers(reader,self.constantPool)
	self.methods=readMembers(reader,self.constantPool)
	self.attributes=readAttributes(reader,self.constantPool)
}


//Getter方法，提供结构体字段访问方法

func (self *ClassFile)MinorVersion() uint16{
	return self.minorVersion
}

func (self *ClassFile)MajorVersion() uint16{
	return self.majorVersion
}

func (self *ClassFile) ConstantPool() ConstantPool{
	return self.constantPool
}

func (self *ClassFile) AccessFlags() uint16 {
	return self.accessFlags
}

func (self *ClassFile) Fields() []*MemberInfo{
	return self.fields
}

func (self *ClassFile) Methods() []*MemberInfo{
	return self.methods
}


//类and接口的名称在常量池

//从常量池查找类名
//self.thisClass 是在常量池的下标
func (self *ClassFile) ClassName() string{
	return self.constantPool.getClassName(self.thisClass)
}

//从常量池查找类名
func (self *ClassFile) SuperClassName() string{
	if self.superClass>0{
		return self.constantPool.getClassName(self.superClass)
	}
	return "" //若类是java.lang.Object，则没有超类。其它类都有超类，默认为java.la.Object
}
//从常量池查找接口名
func (self *ClassFile) InterfaceNames() [] string{
	interfacesNames:=make([]string,len(self.interfaces))
	for i,cpIndex:=range self.interfaces{
		interfacesNames[i] = self.constantPool.getClassName(cpIndex)
	}
	return interfacesNames
}

//magic
func (self *ClassFile) readAndCheckMagic(reader *ClassReader){
	//class文件以0xCA 0xFE 0xBA 0xBE 开始
	magic :=reader.readUint32()
	if magic != 0xCAFEBABE{
		panic("java.lang.ClassFormatError:magic!")
	}
}

//java版本号 M.m 主.次,javaSE从1.2后次版本号都为0 
func (self *ClassFile) readAndCheckVersion(reader *ClassReader){
	self.minorVersion = reader.readUint16()
	self.majorVersion=reader.readUint16()
	
	switch self.majorVersion{
	case 45:
		return 
	//46 is 1.2
	case 46,47,48,49,50,51,52:
		if self.minorVersion==0{
			return 
		}
	}
	panic("java.lang.UnsupportedClassVersionError!")
}

//fields and methods 表大致结构相同,差别仅在于属性表，因此用同一个结构体表示
