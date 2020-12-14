/*
模式匹配
*/
object ExMatch extends App{
	for(i<- 1 to 5)
	{
		i match {
			case 1=>println(1)
			case 2=>println(2)
			case x if(x%2==0) =>println("被2整除") //从上到下匹配，上面匹配了则不会执行到下面
			case _=>println("其它")
		}
	}


	case class Dog(val name:String,val age:Int)  //定义类Dog 
	
	val dog=new Dog("Pet",2) //构造对象
	
		
	//构造函数模式匹配
  //解析对象
	def PMa(x:AnyRef)=x match {
		case Dog(name,age) => println(s"Dog name=$name,age=$age")   
	}

	PMa(dog)  //解析对象dog，提取成员



  //类型匹配时需要列出A所有子类时，使用sealed可以使编译器检查是否有遗漏
	sealed class A  

	class B extends A
	class C extends A
  class D extends A
  class E extends A

	//类型匹配，匹配类及其子类
	val a=new A

	val b=new B
	val c=new C
	val d=new D
	val e=new E


  
	def PMb(x:A)=x match{   
		case x:B=>println("B")
		case x:C=>println("C")
		case x:D=>println("D")
		case x:E=>println("E") //若注释了后两句则出现ExMatch.scala:50: warning: match may not be exhaustive
		case x:A=>println("A")
	}

	PMb(a)
	PMb(b)
	PMb(c)
  PMb(d)
  PMb(e)


  //变量绑定模式，对对象进行匹配
  //可提供对象类型，部分元素信息进行匹配
  def PMc(x:AnyRef)=x match{
    case d@Dog(_,2)=>println(d)  //匹配完成后返回整个对象到d
    case d@Dog(_,3)=>println(d)
    case e1@List(_,e2@List(4,_*)) => println("e1 is "+e1+"\n"+"e2 is "+e2)
  }

  PMc(new Dog("Pet",2))
  PMc(new Dog("Pet",3))
  PMc(List(List(1,2,3,4),List(4,5,6,7)))

  //for循环中可以直接使用模式匹配提取对象

}
