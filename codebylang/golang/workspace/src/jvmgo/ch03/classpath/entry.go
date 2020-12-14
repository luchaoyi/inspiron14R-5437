package classpath

import (
"os"
"strings"
)

const pathListSeparator = string(os.PathListSeparator)


//struct是数据类型集合组成的自定义复合数据类型，
//interface是自定义方法声明集合

//一个类型可以声明式绑定许多方法,方法覆盖了某个接口的所以方法，则这个类型悄无声息的实现了这个接口


//定义接口
type Entry interface{
	readClass(className string) ([]byte ,Entry,error) //read and load class
	String() string //to string
}


func newEntry(path string) Entry{
	//多个路径
	if strings.Contains(path,pathListSeparator){
	return newCompositeEntry(path)
	}

	// *
	if strings.HasSuffix(path,"*"){
		return newWildcardEntry(path)
	} 
	//.zip .jar
	if strings.HasSuffix(path,".jar") || strings.HasSuffix(path,".JAR") || 
	strings.HasSuffix(path,".zip")|| strings.HasSuffix(path,".ZIP") {
		return newZipEntry(path)
	}

	//指定某个目录
	return newDirEntry(path)
}
