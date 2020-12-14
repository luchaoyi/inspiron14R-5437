#!-*-coding:utf8-*-

#返回自身的最简单装饰器，没有对函数装饰
def identity(f):
    print "decorator identity"
    return f


#注册装饰器，以后可以根据名字提取函数
_functions={}
def register(f):
    print "register identity"
    global _functions
    _functions[f.__name__]=f
    return f


@register
@identity  #类似于foo=register(identity(foo))
def foo():
    print "foo"
    return '^*^'


if __name__=='__main__':
    print foo()
