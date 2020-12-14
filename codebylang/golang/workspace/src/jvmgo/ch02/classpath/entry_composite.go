package classpath

import (
	"errors"
	"strings"
)


type CompositeEntry []Entry

func newCompositeEntry(pathList string) CompositeEntry{
	compositeEntry:=[]Entry{}

	for _,path:=range strings.Split(pathList,pathListSeparator){
		entry:=newEntry(path)
		compositeEntry=append(compositeEntry,entry)
	}

	return compositeEntry
}


func (self CompositeEntry) readClass(className string) ([]byte,Entry,error){

	for _,entry:=range self{
		data,from,err:=entry.readClass(className)
		if err==nil{
	return data,from,nil
		}
	}
		return nil,nil,errors.New("class not found"+className)
}

func (self CompositeEntry) String() string {
	strs:=make([]string,len(self))
	for i,entry :=range self{
		strs[i]=entry.String()
	}
	return strings.Join(strs,pathListSeparator)
}

s
/*
若注释掉String方法，则在将CompositeEntry类型当作接口Entry类型使用时,编译器会检查出没有完全实现接口
classpath/classpath.go:61: cannot use newWildcardEntry(jreLibPath) (type CompositeEntry) as type Entry in assignment:
	CompositeEntry does not implement Entry (missing String method)
*/
