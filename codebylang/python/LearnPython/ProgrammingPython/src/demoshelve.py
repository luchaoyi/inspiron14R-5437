#!coding:utf8
# shelve 像存储持久化对象的持久化字典,可以按键访问对象，对象会字典pickle 进 or 出 文件系统
# shelve 自动将对象存储在文件中，可以像字典一样使用

import shelve

bob={"name":"bob","age":18}
kob={"name":"kob","age":28}
cob={"name":":cob","age":25}

db=shelve.open("db")
db['bob']=bob
db['kob']=kob
db['cob']=cob
db.close()

db=shelve.open("db")
print db
db.close()
