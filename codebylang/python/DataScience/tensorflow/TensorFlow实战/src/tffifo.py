import tensorflow as tf 

q=tf.FIFOQueue(2,"int32") #cap is 2
init = q.enqueue_many(([0,10],)) #init must
x=q.dequeue()
y=x+1
q_inc=q.enqueue([y])


with tf.Session() as sess:
    init.run()
    for _ in range(5):
        v,_=sess.run([x,q_inc])
        print v          

        
        
        
        

