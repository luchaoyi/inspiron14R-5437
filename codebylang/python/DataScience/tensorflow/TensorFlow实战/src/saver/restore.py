import tensorflow as tf

sess=tf.Session(config=tf.ConfigProto(log_device_placement=True,allow_soft_placement=True))

v1=tf.Variable(tf.constant(0.0,shape=[1]),name='v1')
v2=tf.Variable(tf.constant(0.0,shape=[1]),name='v2')
result=v1+v2

saver=tf.train.Saver()
with tf.device("/cpu:0"):
    saver.restore(sess,"./model/model.ckpt")
    print sess.run(result)
    
