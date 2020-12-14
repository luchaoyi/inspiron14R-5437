import tensorflow as tf

sess=tf.Session(config=tf.ConfigProto(log_device_placement=True,allow_soft_placement=True))
v1=tf.Variable(tf.constant(1.0,shape=[1]),name='v1')
v2=tf.Variable(tf.constant(1.0,shape=[1]),name='v2')
result=v1+v2
saver=tf.train.Saver()
init_op=tf.initialize_all_variables()
with tf.device("/cpu:0"):
    sess.run(init_op)
    saver.save(sess,"./model/model.ckpt")
    
    
