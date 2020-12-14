import tensorflow as tf
sess=tf.Session()

#数据
x_val=5


#模型f(x)=ax+b
a=tf.Variable(tf.constant(1.))
b=tf.Variable(tf.constant(1.))
x=tf.placeholder(tf.float32)
output=tf.add(tf.multiply(a,x),b)


init=tf.global_variables_initializer()
sess.run(init)

loss=tf.square(tf.subtract(output,50.))
opt=tf.train.GradientDescentOptimizer(0.01) #定义优化器
train_step=opt.minimize(loss)#传入loss

for i in range(10):
    sess.run(train_step,feed_dict={x:x_val})
    a_val=sess.run(a)
    b_val=sess.run(b)
    predict_output=sess.run(output,feed_dict={x:x_val})
    
    print "%s*%s+%s=%s" %(a_val,x_val,b_val,predict_output)
    
    

























