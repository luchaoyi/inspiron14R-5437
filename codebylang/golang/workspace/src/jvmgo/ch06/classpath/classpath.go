package classpath
import(
	"os"
	"path/filepath"
)


//结构体的数据结构
type Classpath struct{
	bootClasspath Entry
	extClasspath Entry 
	userClasspath Entry
}

//-Xjre 启动类和扩展类路径
//-cp/-classpath 用户类路径
func Parse(jreOption,cpOption string) *Classpath{
	cp:=&Classpath{}
	cp.parseBootAndExtClassPath(jreOption)
	cp.parseUserClasspath(cpOption)
	return cp
}

func getJreDir(jreOption string) string{
	//有指定Xjre则使用Xjre指定路径
	//其次当前路径是否有./jre子目录
	//最后搜索$JAVA_HOME

	if jreOption !="" && exists(jreOption){
		return jreOption
	}

	if exists("./jre"){
		return "./jre"
	}

	if jh:=os.Getenv("JAVA_HOME");jh!=""{
		return filepath.Join(jh,"jre")
	}

	panic("Can not find jre folder!")
}


func exists(path string) bool{
	if _,err:=os.Stat(path);err!=nil{
		if os.IsNotExist(err){
		return false
		}
	}
	return true
}


//结构体的方法
func (self *Classpath) parseBootAndExtClassPath(jreOption string){
	jreDir:=getJreDir(jreOption)

	//jre/lib
	jreLibPath:=filepath.Join(jreDir,"lib","*")
	self.bootClasspath = newWildcardEntry(jreLibPath)

	//jre/lib/ext
	jreExtPath:=filepath.Join(jreDir,"lib","ext","*")
	self.extClasspath=newWildcardEntry(jreExtPath)

}
func (self *Classpath) parseUserClasspath(cpOption string){
	if cpOption==""{
		cpOption="."
	}
	self.userClasspath=newEntry(cpOption)
}

func (self *Classpath) ReadClass(className string) ([]byte,Entry,error){
	className=className+".class"
	if data,entry,err:=self.bootClasspath.readClass(className); err==nil{
		return data,entry,err 
	}

	if data ,entry,err:=self.extClasspath.readClass(className);err==nil{
		return data,entry,err 
	}
	return self.userClasspath.readClass(className)
}

func (self *Classpath) String() string{
	return self.userClasspath.String()
}
