#coding:utf8


def dog():
    print "我被领养了"
    while True:
        try:
            food=yield
            if food is not None:
                yield "吃了%s" %food
            else:
                yield "我要吃东西"
        except ValueError:
            yield "病了"
        except GeneratorExit:
            print "死了"
            raise StopIteration

d=dog()
d.next()
print d.throw(ValueError) #向协程传递异常
d.next()
print d.send("骨头")
d.close()
d.next()



            
