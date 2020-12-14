#coding:utf8
import sys 


print sys.argv #命令行参数

sys.stdout.write("1234")
sys.stdout.write("123\n") #stdout不可读只能写相当于输出到控制台

a=sys.stdin.readline() #遇到\n停止
print a

print "123\n"
print "123"


a=sys.stdin.read(3) #读够数量结束,多余的字符还在stdin流中，若后面有read会接着读
print a

#python3的input就是python2的raw_input，
#python raw_input返回字符串, input=eval(raw_input())即对字符串进行了求值

a=raw_input("raw input: ")
print a
print eval(a)

print input("input: ")




