#coding:utf8
import redis
r=redis.StrictRedis(host="127.0.0.1",port=6379,db=0) #connect

print r.keys() #redis-cli的客户端命令有对应的同名函数，用法一致
print r.type('car')
print r.hget('car', 'name')
print r.hgetall('car')
#r.shutdown() 

#除了支持按命令式操作,还支持一些简便用法，可直接将python字典添加到其中

print r.hmset('dict',{'a':1,'b':2})
print r.hmget('dict',['a','b'])
print r.hgetall('dict')

#pipeline可创建管道和事物

#创建管道
pipe=r.pipeline()
pipe.get('f')
pipe.smembers('REM')
result=pipe.execute()
print result

#支持链式调用
print pipe.get('f').smembers('REM').execute()
print r.pipeline().get('f').smembers('REM').execute()






