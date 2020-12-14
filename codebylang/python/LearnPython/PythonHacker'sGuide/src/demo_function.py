#coding:utf8


import abc

class Testabc:
    @abc.abstractmethod
    def test0(self):
        "do some thing"


class TestClassMethod(Testabc):
    classvalue = 'class value' #类变量
    def __init__(self):
        self.name = 'abc'  #成员变量 

    #实现抽象方法
    def test0(self):
        print "test0"

    #实例方法
    def test1(self):
        print 'test1'
        print self

    #类方法 
    @classmethod
    def test2(cls):
        print cls
        print 'test2'
        print TestClassMethod.classvalue
        print '----------------'

    #静态方法
    @staticmethod
    def test3():
        print TestClassMethod.classvalue
        print 'test3'

if __name__ == '__main__':
    a = TestClassMethod()
    a.test0()
    a.test1()
    a.test2()
    a.test3()
    TestClassMethod.test3()
    TestClassMethod.test2()


  #  test0为抽象方法
  #  test1为实例方法
  #  test2为类方法，第一个参数为类本身,类也是对象
  #  test3为静态方法，可以不接收参数,如果有self参数,接受self作为参数，但不会使用它
  #  类方法和静态方法可以访问类的静态变量(类变量)，但不能访问实例变量,test2、test3不能访问self.name的,而test1则可以
