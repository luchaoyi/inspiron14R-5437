# Implementing an RNN in Tensorflow
#----------------------------------
# We implement an RNN in Tensorflow to predict spam/ham from texts

import os
import re
import io
import requests
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from zipfile import ZipFile
from tensorflow.python.framework import ops


#UnicodeDecodeError: 'ascii' codec can't decode byte 0xc2 in position 571: ordinal not in range(128)
import sys
reload(sys)
sys.setdefaultencoding('utf8')



ops.reset_default_graph()

# Start a graph
sess = tf.Session()

# Set RNN parameters
epochs = 20

batch_size = 250
max_sequence_length = 25

#rnn size不是展开的最大长度，展开最大长度由序列长度决定
#rnn size是隐藏层状态向量的维度
rnn_size =10
embedding_size = 50


min_word_frequency = 10 
learning_rate = 0.0005
dropout_keep_prob = tf.placeholder(tf.float32) #训练时0-1,测试时为1

# Download or open data
data_dir = 'temp'
data_file = 'text_data.txt'
if not os.path.exists(data_dir):
    os.makedirs(data_dir)

if not os.path.isfile(os.path.join(data_dir, data_file)):
    zip_url = 'http://archive.ics.uci.edu/ml/machine-learning-databases/00228/smsspamcollection.zip'
    r = requests.get(zip_url)
    z = ZipFile(io.BytesIO(r.content))
    file = z.read('SMSSpamCollection')
    # Format Data
    text_data = file.decode()
    text_data = text_data.encode('ascii',errors='ignore')
    text_data = text_data.decode().split('\n')

    # Save data to text file
    with open(os.path.join(data_dir, data_file), 'w') as file_conn:
        for text in text_data:
            file_conn.write("{}\n".format(text))
else:
    # Open data from text file
    text_data = []
    with open(os.path.join(data_dir, data_file), 'r') as file_conn:
        for row in file_conn:
            text_data.append(row)
    text_data = text_data[:-1]

text_data = [x.split('\t') for x in text_data if len(x)>=1]

#文本label和文本内容
[text_data_target, text_data_train] = [list(x) for x in zip(*text_data)]



# Create a text cleaning function
#清除特殊字符，转换为小写后使用" "连接为句子
def clean_text(text_string):
    #re.sub(pattern, repl, string, count=0, flags=0)
    text_string = re.sub(r'([^\s\w]|_|[0-9])+', '', text_string) #re.sub正则替换，替换为空即删除
    text_string = " ".join(text_string.split())
    text_string = text_string.lower()
    return(text_string)

# Clean texts
text_data_train = [clean_text(x) for x in text_data_train]


#输入文本，限制文本最大长度和词语最小频度，建立一个词汇表，根据词汇表可以将文本转换为词汇表的索引
#不存在词汇表中的词索引为0
# Change texts into numeric vectors
vocab_processor = tf.contrib.learn.preprocessing.VocabularyProcessor(max_sequence_length,
                                                                     min_frequency=min_word_frequency)
text_processed = np.array(list(vocab_processor.fit_transform(text_data_train)))



# Shuffle and split data
text_processed = np.array(text_processed)
text_data_target = np.array([1 if x=='ham' else 0 for x in text_data_target])

#乱序，打乱索引而不是重排文本，时间和空间更优
shuffled_ix = np.random.permutation(np.arange(len(text_data_target)))

x_shuffled = text_processed[shuffled_ix]
y_shuffled = text_data_target[shuffled_ix]

# Split train/test set
ix_cutoff = int(len(y_shuffled)*0.80)
x_train, x_test = x_shuffled[:ix_cutoff], x_shuffled[ix_cutoff:]
y_train, y_test = y_shuffled[:ix_cutoff], y_shuffled[ix_cutoff:]

#print vocab_processor.vocabulary_.get('in') -> 9 ,通过get可查看word的索引

vocab_size = len(vocab_processor.vocabulary_)
print("Vocabulary Size: {:d}".format(vocab_size))
print("80-20 Train Test split: {:d} -- {:d}".format(len(y_train), len(y_test)))

# Create placeholders
x_data = tf.placeholder(tf.int32, [None, max_sequence_length])
y_output = tf.placeholder(tf.int32, [None])

#这里嵌入矩阵是分类问题的副产品,和CBOW问题不同，词嵌入是一种思想
#每个词都有一个嵌入向量
#通过嵌入矩阵将x_data转换为向量表示
# Create embedding
embedding_mat = tf.Variable(tf.random_uniform([vocab_size, embedding_size], -1.0, 1.0))
embedding_output = tf.nn.embedding_lookup(embedding_mat, x_data)
#embedding_output_expanded = tf.expand_dims(embedding_output, -1)


# Define the RNN cell
#rnn网络展开步长和输入序列长度一致
#rnn_size代表的是state的维度
cell = tf.nn.rnn_cell.BasicRNNCell(num_units = rnn_size)#定义一个cell


output, state = tf.nn.dynamic_rnn(cell, embedding_output, dtype=tf.float32)
output = tf.nn.dropout(output, dropout_keep_prob)

# Get output of RNN sequence
output = tf.transpose(output, [1, 0, 2]) #250*25*10->25*250*10

#last取的是最终25时刻的输出，若不经过dropout则和state是一样的
last = tf.gather(output, int(output.get_shape()[0]) - 1)


weight = tf.Variable(tf.truncated_normal([rnn_size, 2], stddev=0.1))
bias = tf.Variable(tf.constant(0.1, shape=[2]))
logits= tf.matmul(last, weight) + bias

# Loss function

losses = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=y_output) # logits=float32, labels=int32
loss = tf.reduce_mean(losses)

predict= tf.nn.softmax(logits) #类的概率分布，选择大的
accuracy = tf.reduce_mean(tf.cast(tf.equal(tf.argmax(predict, 1), tf.cast(y_output, tf.int64)), tf.float32))

optimizer = tf.train.RMSPropOptimizer(learning_rate)
train_step = optimizer.minimize(loss)

init = tf.initialize_all_variables()
sess.run(init)

train_loss = []
test_loss = []
train_accuracy = []
test_accuracy = []




#epoch 全数据集，一次epoch即跑完一次全数据集
# Start training
for epoch in range(epochs):
    # Shuffle training data
    shuffled_ix = np.random.permutation(np.arange(len(x_train)))
    x_train = x_train[shuffled_ix]
    y_train = y_train[shuffled_ix]
    num_batches = int(len(x_train)/batch_size) + 1
    # TO DO CALCULATE GENERATIONS ExACTLY
    for i in range(num_batches):
        # Select train data
        min_ix = i * batch_size
        max_ix = np.min([len(x_train), ((i+1) * batch_size)])
        x_train_batch = x_train[min_ix:max_ix]
        y_train_batch = y_train[min_ix:max_ix]
        
        # Run train step
        train_dict = {x_data: x_train_batch, y_output: y_train_batch, dropout_keep_prob:0.5}
        sess.run(train_step, feed_dict=train_dict)
        
    # Run loss and accuracy for training
    temp_train_loss, temp_train_acc = sess.run([loss, accuracy], feed_dict=train_dict)
    train_loss.append(temp_train_loss)
    train_accuracy.append(temp_train_acc)
    
    # Run Eval Step
    test_dict = {x_data: x_test, y_output: y_test, dropout_keep_prob:1.0}
    temp_test_loss, temp_test_acc = sess.run([loss, accuracy], feed_dict=test_dict)
    test_loss.append(temp_test_loss)
    test_accuracy.append(temp_test_acc)
    print('Epoch: {}, Test Loss: {:.2}, Test Acc: {:.2}'.format(epoch+1, temp_test_loss, temp_test_acc))
    
# Plot loss over time
epoch_seq = np.arange(1, epochs+1)
plt.plot(epoch_seq, train_loss, 'k--', label='Train Set')
plt.plot(epoch_seq, test_loss, 'r-', label='Test Set')
plt.title('Softmax Loss')
plt.xlabel('Epochs')
plt.ylabel('Softmax Loss')
plt.legend(loc='upper left')
plt.show()

# Plot accuracy over time
plt.plot(epoch_seq, train_accuracy, 'k--', label='Train Set')
plt.plot(epoch_seq, test_accuracy, 'r-', label='Test Set')
plt.title('Test Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend(loc='upper left')
plt.show()
