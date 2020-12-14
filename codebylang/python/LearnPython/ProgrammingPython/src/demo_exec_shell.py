#!-*-coding:utf8-*-
import os
#os.system  exec shell command
os.system('ls -al')
#os.popen exec shell command and link to 输入输出流，会得到一个类似文件的对象
rs=os.popen('ls -al')
type(rs)
print rs.readlines()


