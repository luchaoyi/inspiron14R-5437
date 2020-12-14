object Example_11_17 extends App{
  abstract class Food
  class Rice extends Food{
    override def toString="粮食"
  }
  class Meat extends Food{
    override def toString="肉"
  }

  
  class Animal{
    type FoodType //类型也是参数，没有具体赋值
    def eat(f:FoodType)=f
  }

  //在子类对FoodType赋值，将类型确定下来
  class Human extends Animal{
    type FoodType=Food
    override def eat(f:FoodType)=f
  }

  class Tiger extends Animal{
    type FoodType=Meat
    override def eat(f:FoodType)=f
  }

  val human=new Human
  val tiger=new Tiger

}




