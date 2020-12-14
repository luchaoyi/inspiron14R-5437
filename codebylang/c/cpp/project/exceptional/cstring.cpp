// 异常安全copy
cstring& cstring::operator=(const cstring& cstr) {
	if(this != &str) {
		//利用复制构造实现operator= 
		cstring temp(str); //if空间不足异常不影响cstr和this
		//和临时对象swap来实现自动析构this本身的pData
		char* pTemp = this.pData;
		this.pData = temp.pData;
		temp.pData = pTemp;
	}
//离开作用域temp析构
	return this;
}




