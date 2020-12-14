#!coding:utf8

import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets 

#创建session
sess=tf.Session()
#读取数据转换为28*28
data_dir = 'temp'
mnist = read_data_sets(data_dir)
train_xdata = np.array([np.reshape(x, (28,28)) for x in mnist.
train.images])
test_xdata = np.array([np.reshape(x, (28,28)) for x in mnist.test.
images])

train_labels = mnist.train.labels
test_labels = mnist.test.labels

#different batch sizes for training and evaluation(验证) sizes.
batch_size = 100
evaluation_size = 500

learning_rate = 0.005
image_width = train_xdata[0].shape[0]
image_height = train_xdata[0].shape[1]
target_size = max(train_labels) + 1 #最共10类最后一个FC层使用10个神经元
num_channels = 1#灰度图，单通道
generations = 150
eval_every = 5
conv1_features = 25
conv2_features = 50
max_pool_size1 = 2
max_pool_size2 = 2
fully_connected_size1 = 100
#                           x横          y纵
x_input_shape=(batch_size,image_width,image_height,num_channels)
x_input=tf.placeholder(tf.float32,shape=x_input_shape)
#0-9
y_target=tf.placeholder(tf.int32,shape=batch_size)
eval_input_shape = (evaluation_size, image_width, image_height,
num_channels)
eval_input = tf.placeholder(tf.float32, shape=eval_input_shape)
eval_target = tf.placeholder(tf.int32, shape=(evaluation_size))



#原图片是w*h*nc 单个conv filter 是fw*fh*nc,需要多个filter,因此为fw*fc*nc*numf
#卷积层使用4*4大小的过滤器
conv1_weight=tf.Variable(tf.truncated_normal([4,4,num_channels,conv1_features],stddev=0.1,dtype=tf.float32))
conv1_bias=tf.Variable(tf.zeros([conv1_features],dtype=tf.float32))
conv2_weight=tf.Variable(tf.truncated_normal([4,4,conv1_features,conv2_features],stddev=0.1,dtype=tf.float32))
conv2_bias=tf.Variable(tf.zeros([conv2_features],dtype=tf.float32))

# // 表示floor除法

#全连接层
#当执行的卷积运算结果和原图片的w和h一样时，每层w和h变化只在池化时缩小
#因此这里直接使用池化缩小的倍数来计算全连接层前矩阵的w和h
resulting_width=image_width//(max_pool_size1*max_pool_size2)
resulting_height=image_height//(max_pool_size1*max_pool_size2)
full1_input_size=resulting_width*resulting_height*conv2_features
full1_weight=tf.Variable(tf.truncated_normal([full1_input_size,fully_connected_size1],stddev=0.1,dtype=tf.float32))
full1_bias = tf.Variable(tf.truncated_normal([fully_connected_size1], stddev=0.1, dtype=tf.float32))
full2_weight = tf.Variable(tf.truncated_normal([fully_connected_size1, target_size], stddev=0.1, dtype=tf.float32))
full2_bias = tf.Variable(tf.truncated_normal([target_size],
stddev=0.1, dtype=tf.float32))

keep_prob=tf.placeholder(tf.float32)
def my_conv_net(input_data):
    # First Conv-ReLU-MaxPool Layer
    #步长为1，padding='SAME'表示卷积运算后大小保持不变和原图像一致
    conv1=tf.nn.conv2d(input_data,conv1_weight,strides=[1,1,1,1],padding='SAME')
    relu1=tf.nn.relu(tf.nn.bias_add(conv1,conv1_bias))
    #dropout
    relu1=tf.nn.dropout(relu1,keep_prob)
    max_pool1=tf.nn.max_pool(relu1,ksize=[1,max_pool_size1,max_pool_size1,1],
                             strides=[1,max_pool_size1,max_pool_size1,1],padding='SAME')
    # Second Conv-ReLU-MaxPool Layer
    conv2 = tf.nn.conv2d(max_pool1, conv2_weight, strides=[1, 1,1, 1], padding='SAME')
    relu2 = tf.nn.relu(tf.nn.bias_add(conv2, conv2_bias))
    #dropout
    relu2=tf.nn.dropout(relu2,keep_prob)
    max_pool2 = tf.nn.max_pool(relu2, ksize=[1, max_pool_size2,max_pool_size2, 1], 
                               strides=[1, max_pool_size2, max_pool_size2,1], padding='SAME')    
    
    #max_pool2输出的维度为batch_size*w*h*nf,将其展开为一维方便与FC层相连
    final_conv_shape=max_pool2.get_shape().as_list()
    final_shape=final_conv_shape[1]*final_conv_shape[2]*final_conv_shape[3]
    #batch_size个一维向量
    flat_output=tf.reshape(max_pool2,[final_conv_shape[0],final_shape])
    #FC1
    fully_connected1=tf.nn.relu(tf.add(tf.matmul(flat_output,full1_weight),full1_bias))
    #dropout
    fully_connected1=tf.nn.dropout(fully_connected1,keep_prob)
    #FC2
    final_model_output=tf.nn.relu(tf.add(tf.matmul(fully_connected1,full2_weight),full2_bias))
    return (final_model_output)


model_output=my_conv_net(x_input)
test_model_output = my_conv_net(eval_input)

#根据model_output计算softmax概率分布，然后根据target标签来计算cross entropy loss
#sparse_softmax_cross_entropy_with_logits的标签是整数
#softmax_cross_entropy_with_logits标签是one-hot编码
loss=tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=model_output,labels=y_target))

prediction=tf.nn.softmax(model_output) #输出对应类别概率
test_prediction=tf.nn.softmax(test_model_output)

def get_accuracy(logits,targets):
    batch_predictions=np.argmax(logits,axis=1) #得到最大的下标
    num_correct=np.sum(np.equal(batch_predictions,targets))
    return(100. * num_correct/batch_predictions.shape[0])
    
my_optimizer = tf.train.MomentumOptimizer(learning_rate, 0.9)
train_step = my_optimizer.minimize(loss)
# Initialize Variables
init = tf.global_variables_initializer()
sess.run(init)

# Start training loop
train_loss = []
train_acc = []
test_acc = []
for i in range(generations):
    rand_index = np.random.choice(len(train_xdata), size=batch_size)
    rand_x = train_xdata[rand_index]
    rand_x = np.expand_dims(rand_x, 3)
    rand_y = train_labels[rand_index]
    train_dict = {x_input: rand_x, y_target: rand_y,keep_prob:0.85}
    
    sess.run(train_step, feed_dict=train_dict)
    temp_train_loss, temp_train_preds = sess.run([loss, prediction], feed_dict=train_dict)
    temp_train_acc = get_accuracy(temp_train_preds, rand_y)
    
    if (i+1) % eval_every == 0:
        eval_index = np.random.choice(len(test_xdata), size=evaluation_size)
        eval_x = test_xdata[eval_index]
        eval_x = np.expand_dims(eval_x, 3)
        eval_y = test_labels[eval_index]
        test_dict = {eval_input: eval_x, eval_target: eval_y,keep_prob:1}
        test_preds = sess.run(test_prediction, feed_dict=test_dict)
        temp_test_acc = get_accuracy(test_preds, eval_y)
        
        # Record and print results
        train_loss.append(temp_train_loss)
        train_acc.append(temp_train_acc)
        test_acc.append(temp_test_acc)
        acc_and_loss = [(i+1), temp_train_loss, temp_train_acc, temp_test_acc]
        acc_and_loss = [np.round(x,2) for x in acc_and_loss]
        print('Generation # {}. Train Loss: {:.2f}. Train Acc (Test Acc): {:.2f} ({:.2f})'.format(*acc_and_loss))
    
    
# Matlotlib code to plot the loss and accuracies
eval_indices = range(0, generations, eval_every)
# Plot loss over time
plt.plot(eval_indices, train_loss, 'k-')
plt.title('Softmax Loss per Generation')
plt.xlabel('Generation')
plt.ylabel('Softmax Loss')
plt.show()

# Plot train and test accuracy
plt.plot(eval_indices, train_acc, 'k-', label='Train Set Accuracy')
plt.plot(eval_indices, test_acc, 'r--', label='Test Set Accuracy')
plt.title('Train and Test Accuracy')
plt.xlabel('Generation')
plt.ylabel('Accuracy')
plt.legend(loc='lower right')
plt.show()

# Plot some samples
# Plot the 6 of the last batch results:
actuals = rand_y[0:6]
predictions = np.argmax(temp_train_preds,axis=1)[0:6]
images = np.squeeze(rand_x[0:6])

Nrows = 2
Ncols = 3
for i in range(6):
    plt.subplot(Nrows, Ncols, i+1)
    plt.imshow(np.reshape(images[i], [28,28]), cmap='Greys_r')
    plt.title('Actual: ' + str(actuals[i]) + ' Pred: ' + str(predictions[i]),
                               fontsize=10)
    frame = plt.gca()
    frame.axes.get_xaxis().set_visible(False)
    frame.axes.get_yaxis().set_visible(False)     

plt.show()





