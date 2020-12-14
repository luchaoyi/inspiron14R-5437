#coding:utf8
#配置了gpu的tf默认使用gpu计算
#allow_soft_placement 指定gpu不能计算时放到cpu执行
import tensorflow as tf
sess=tf.Session(config=tf.ConfigProto(log_device_placement=True,allow_soft_placement=True))

with tf.device('/cpu:0'):
    a=tf.constant(1)
    b=tf.constant(2)
    c=a+b
print sess.run(c)

with tf.device('/gpu:0'):
    a=tf.constant([0,0,0])
    b=tf.constant([1,2,3])
    c=a+b
    d=tf.Variable(0,dtype=tf.int32)

print sess.run(c)

#多设备并行
#同步梯度下降，稳
#异步梯度下降,随机性大,不稳
#先异步粗搜，后同步精搜，根据||梯度||判定何时开始精搜

