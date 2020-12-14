# -*- coding: utf-8 -*-
#
# Implmenting an LSTM RNN Model
#------------------------------
#  Here we implement an LSTM model on all a data set of Shakespeare works.
#

import os
import re
import string
import requests
import numpy as np
import collections
import random
import pickle
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.python.framework import ops
ops.reset_default_graph()

# Start a session
sess = tf.Session()

# Set RNN Parameters
min_word_freq = 5 # Trim the less frequent words off
rnn_size = 128 # RNN Model size, has to equal embedding size
epochs = 10 # Number of epochs to cycle through data
batch_size = 100 # Train on this many examples at once
learning_rate = 0.001 # Learning rate

training_seq_len = 50 # how long of a word group to consider 

embedding_size = rnn_size
save_every = 500 # How often to save model checkpoints
eval_every = 50 # How often to evaluate the test sentences

prime_texts = ['thou art more', 'to be or not to', 'wherefore art thou']

# Download/store Shakespeare data
data_dir = 'temp'
data_file = 'shakespeare.txt'
model_path = 'shakespeare_model'
full_model_dir = os.path.join(data_dir, model_path)

# Declare punctuation to remove, everything except hyphens and apostrophes
#string.punctuation
#Out[12]: '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
punctuation = string.punctuation
punctuation = ''.join([x for x in punctuation if x not in ['-', "'"]]) #标点符号的列表去掉-和'
# Make Model Directory
if not os.path.exists(full_model_dir):
    os.makedirs(full_model_dir)

# Make data directory
if not os.path.exists(data_dir):
    os.makedirs(data_dir)

print('Loading Shakespeare Data')
# Check if file is downloaded.
if not os.path.isfile(os.path.join(data_dir, data_file)):
    print('Not found, downloading Shakespeare texts from www.gutenberg.org')
    shakespeare_url = 'http://www.gutenberg.org/cache/epub/100/pg100.txt'
    # Get Shakespeare text
    response = requests.get(shakespeare_url)
    shakespeare_file = response.content
    # Decode binary into string
    s_text = shakespeare_file.decode('utf-8')
    # Drop first few descriptive paragraphs.
    s_text = s_text[7675:]
    # Remove newlines
    s_text = s_text.replace('\r\n', '')
    s_text = s_text.replace('\n', '')
    
    # Write to file
    with open(os.path.join(data_dir, data_file), 'w') as out_conn:
        out_conn.write(s_text)
else:
    # If file has been saved, load from that file
    with open(os.path.join(data_dir, data_file), 'r') as file_conn:
        s_text = file_conn.read().replace('\n', '')

# Clean text
print('Cleaning Text')
s_text = re.sub(r'[{}]'.format(punctuation), ' ', s_text)
s_text = re.sub('\s+', ' ', s_text ).strip().lower()


#index->word,word->index
# Build word vocabulary function
def build_vocab(text, min_word_freq):
    word_counts = collections.Counter(text.split(' '))
    # limit word counts to those more frequent than cutoff
    word_counts = {key:val for key, val in word_counts.items() if val>min_word_freq}
    # Create vocab --> index mapping
    words = word_counts.keys()
    vocab_to_ix_dict = {key:(ix+1) for ix, key in enumerate(words)}
    # Add unknown key --> 0 index
    vocab_to_ix_dict['unknown']=0
    # Create index --> vocab mapping
    ix_to_vocab_dict = {val:key for key,val in vocab_to_ix_dict.items()}
    
    return(ix_to_vocab_dict, vocab_to_ix_dict)

# Build Shakespeare vocabulary
print('Building Shakespeare Vocab')
ix2vocab, vocab2ix = build_vocab(s_text, min_word_freq)
vocab_size = len(ix2vocab) + 1
print('Vocabulary Length = {}'.format(vocab_size))
# Sanity Check
assert(len(ix2vocab) == len(vocab2ix))

# Convert text to word vectors
#转换句子为index vector
s_text_words = s_text.split(' ')
s_text_ix = []
for ix, x in enumerate(s_text_words):
    try:
        s_text_ix.append(vocab2ix[x])
    except:
        s_text_ix.append(0)
s_text_ix = np.array(s_text_ix)


# Define LSTM RNN Model
class LSTM_Model():
    def __init__(self, rnn_size, batch_size, learning_rate,
                 training_seq_len, vocab_size, infer_sample=False):
        self.rnn_size = rnn_size
        self.vocab_size = vocab_size
        self.infer_sample = infer_sample
        self.learning_rate = learning_rate
        
        if infer_sample:
            self.batch_size = 1
            self.training_seq_len = 1
        else:
            self.batch_size = batch_size
            self.training_seq_len = training_seq_len
        
        self.lstm_cell = tf.nn.rnn_cell.BasicLSTMCell(rnn_size)
        self.initial_state = self.lstm_cell.zero_state(self.batch_size, tf.float32)#初始状态为0
        
        self.x_data = tf.placeholder(tf.int32, [self.batch_size, self.training_seq_len])
        self.y_output = tf.placeholder(tf.int32, [self.batch_size, self.training_seq_len])
        
        with tf.variable_scope('lstm_vars'):
            # Softmax Output Weights
            W = tf.get_variable('W', [self.rnn_size, self.vocab_size], tf.float32, tf.random_normal_initializer())
            b = tf.get_variable('b', [self.vocab_size], tf.float32, tf.constant_initializer(0.0))
        
            # Define Embedding
            embedding_mat = tf.get_variable('embedding_mat', [self.vocab_size, self.rnn_size],
                                            tf.float32, tf.random_normal_initializer())
                                            
            embedding_output = tf.nn.embedding_lookup(embedding_mat, self.x_data)
            rnn_inputs = tf.split(embedding_output, self.training_seq_len, 1)
            rnn_inputs_trimmed = [tf.squeeze(x, [1]) for x in rnn_inputs]
        
        # If we are inferring (generating text), we add a 'loop' function
        # Define how to get the i+1 th input from the i th output
        def inferred_loop(prev, count):
            # Apply hidden layer
            #选择W*output+b最大的得到下标即为此步骤预测的词
            #通过index索引得到嵌入向量返回
            prev_transformed = tf.matmul(prev, W) + b
            # Get the index of the output (also don't run the gradient)
            prev_symbol = tf.stop_gradient(tf.argmax(prev_transformed, 1))
            # Get embedded vector
            output = tf.nn.embedding_lookup(embedding_mat, prev_symbol)
            return(output)
        
        
        
        #decoder = tf.nn.seq2seq.rnn_decoder
        decoder=tf.contrib.legacy_seq2seq.rnn_decoder
        
        #infer_sample为True时使用inferred_loop
        outputs, last_state = decoder(rnn_inputs_trimmed, #输入数据
                                      self.initial_state, 
                                      self.lstm_cell,
                                      loop_function=inferred_loop if infer_sample else None) 
        
        
        # Non inferred outputs
        #output = tf.reshape(tf.concat(1, outputs), [-1, self.rnn_size]),tensorflow1.0以后,数字在后,tensors在前
        output = tf.reshape(tf.concat(outputs,1), [-1, self.rnn_size])
        
        # Logits and output
        self.logit_output = tf.matmul(output, W) + b
        self.model_output = tf.nn.softmax(self.logit_output)
        
        #计算所有examples的加权交叉熵损失
        #一个句子有n个单词，每个单词及单词所对应的label就是一个example,所有examples就是句子的所有单词
        #loss = seq2seq.sequence_loss_by_example([logits_1, ..., logits_n],
        #                                        [targets_1, ..., targets_n],
        #                                        weights,
        #                                        vocab_size_all)        
        #[tf.ones([self.batch_size * self.training_seq_len])] 是加权的权重，全一代表每一个step的贡献一致
        #每一个example(xi,yi)都有一个交叉熵loss,一个句子由[(x0,y0),(x1,y1),...]构成，可以根据权重计算加权求和得到每个句子的加权loss
        #logits 的shape = [batch_size*numsteps, vocab_size], vocab_size是（分类）类别的个数 
        #targets 的shape = [batch_size*num_steps]         
        
        
        
        #loss_fun = tf.nn.seq2seq.sequence_loss_by_example
        loss_fun=tf.contrib.legacy_seq2seq.sequence_loss_by_example
        loss = loss_fun([self.logit_output],[tf.reshape(self.y_output, [-1])],
                [tf.ones([self.batch_size * self.training_seq_len])],
                self.vocab_size)
        
        #self.loss=loss
        
        self.cost = tf.reduce_sum(loss) / (self.batch_size * self.training_seq_len)
        self.final_state = last_state
        
        
        #优化器施加梯度截断，防止梯度爆炸
        gradients, _ = tf.clip_by_global_norm(tf.gradients(self.cost, tf.trainable_variables()), 4.5)
        optimizer = tf.train.AdamOptimizer(self.learning_rate)
        self.train_op = optimizer.apply_gradients(zip(gradients, tf.trainable_variables()))
        
    def sample(self, sess, words=ix2vocab, vocab=vocab2ix, num=10, prime_text='thou art'):
        #batch_size=1
        state = sess.run(self.lstm_cell.zero_state(1, tf.float32))
        word_list = prime_text.split() #['thou', 'art']
        for word in word_list[:-1]: #到句子最后一个词之前,这里为thou
            x = np.zeros((1, 1))
            x[0, 0] = vocab[word]
            feed_dict = {self.x_data: x, self.initial_state:state}
            [state] = sess.run([self.final_state], feed_dict=feed_dict)
        
        #上个循环先输入了thou得到一个state
        #然后下面的循环以得到的state和'art'为h0和x0，开始推测
        #这里训练时将序列长度设置为1,没有使用tf的函数展开推测，而是使用一个for循环自己控制将最后一个状态输入到下一个状态
        out_sentence = prime_text
        word = word_list[-1]
        for n in range(num):
            x = np.zeros((1, 1))
            x[0, 0] = vocab[word]
            feed_dict = {self.x_data: x, self.initial_state:state}
            [model_output, state] = sess.run([self.model_output, self.final_state], feed_dict=feed_dict)
            sample = np.argmax(model_output[0])
            if sample == 0:
                break
            word = words[sample]
            out_sentence = out_sentence + ' ' + word
        return(out_sentence)

with tf.variable_scope('lstm_model') as scope:
    # Define LSTM Model
    lstm_model = LSTM_Model(rnn_size, batch_size, learning_rate,training_seq_len, vocab_size)

with tf.variable_scope('lstm_model') as scope:
    scope.reuse_variables()
    test_lstm_model = LSTM_Model(rnn_size, batch_size, learning_rate,training_seq_len, vocab_size, infer_sample=True)


# Create model saver
saver = tf.train.Saver(tf.all_variables())

# Create batches for each epoch
num_batches = int(len(s_text_ix)/(batch_size * training_seq_len)) + 1
# Split up text indices into subarrays, of equal size
batches = np.array_split(s_text_ix, num_batches)
# Reshape each split into [batch_size, training_seq_len]
batches = [np.resize(x, [batch_size, training_seq_len]) for x in batches]

# Initialize all variables
init = tf.global_variables_initializer()
sess.run(init)

# Train model
train_loss = []
iteration_count = 1


#一个batch是在相同的参数下运行的，一个batch更新一次参数
for epoch in range(epochs):
    # Shuffle word indices
    random.shuffle(batches)
    # Create targets from shuffled batches
    targets = [np.roll(x, -1, axis=1) for x in batches]
    # Run a through one epoch
    print('Starting Epoch #{} of {}.'.format(epoch+1, epochs))
    # Reset initial LSTM state every epoch
    state = sess.run(lstm_model.initial_state)
    for ix, batch in enumerate(batches):
        training_dict = {lstm_model.x_data: batch, lstm_model.y_output: targets[ix]}
        c, h = lstm_model.initial_state
        training_dict[c] = state.c
        training_dict[h] = state.h
        
        
        #shape为(5000,) batch_size*training_seq_len=100*50=5000
        #100个句子50个词产生5000个loss
        #LOSS=sess.run(lstm_model.loss,feed_dict=training_dict)
        #print LOSS.shape #-> (5000,)
        #temp_loss=LOSS求和/(100*50)
        temp_loss, state, _ = sess.run([lstm_model.cost, lstm_model.final_state, lstm_model.train_op],
                                       feed_dict=training_dict)
        
        train_loss.append(temp_loss)
        
        # Print status every 10 gens
        if iteration_count % 10 == 0:
            summary_nums = (iteration_count, epoch+1, ix+1, num_batches+1, temp_loss)
            print('Iteration: {}, Epoch: {}, Batch: {} out of {}, Loss: {:.2f}'.format(*summary_nums))
        
        # Save the model and the vocab
        if iteration_count % save_every == 0:
            # Save model
            model_file_name = os.path.join(full_model_dir, 'model')
            saver.save(sess, model_file_name, global_step = iteration_count)
            print('Model Saved To: {}'.format(model_file_name))
            # Save vocabulary
            dictionary_file = os.path.join(full_model_dir, 'vocab.pkl')
            with open(dictionary_file, 'wb') as dict_file_conn:
                pickle.dump([vocab2ix, ix2vocab], dict_file_conn)
        
        if iteration_count % eval_every == 0:
            for sample in prime_texts:
                print(test_lstm_model.sample(sess, ix2vocab, vocab2ix, num=10, prime_text=sample))
                
        iteration_count += 1


# Plot loss over time
plt.plot(train_loss, 'k-')
plt.title('Sequence to Sequence Loss')
plt.xlabel('Generation')
plt.ylabel('Loss')
plt.show()
