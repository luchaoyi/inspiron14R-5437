package classfile

//仅起标记作用的属性
type DeprecatedAttribute struct{MarkerAttribute}
type SyntheticAttribute struct {MarkerAttribute}

type MarkerAttribute struct{}

func (self *MarkerAttribute) readInfo(reader *ClassReader){
//read nothing
}




