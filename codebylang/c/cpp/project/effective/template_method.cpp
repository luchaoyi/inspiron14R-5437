//一种设计模式，lcy将其称为骨架模式

class APP{
public:
	virtual ~APP();
	//...
	void startup(){ //template Method 设计骨架，推迟实现
		init();
		if(!validate())
			altInit();
	}
protected:
	virtual bool validate() const = 0 ;//抽象方法，留待以后实现
	virtual void altInit();

private:
	void init();
	//...
}



//应用时实现

class MyApp:public App{
	//...
}
