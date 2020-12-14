#coding:utf8
# Using Tensorflow for Stylenet/NeuralStyle
#---------------------------------------
#
# We use two images, an original image and a style image
# and try to make the original image in the style of the style image.
#
# Reference paper:
# https://arxiv.org/abs/1508.06576
#
# Need to download the model 'imagenet-vgg-verydee-19.mat' from:
#   http://www.vlfeat.org/matconvnet/models/beta16/imagenet-vgg-verydeep-19.mat

import os
import scipy.io as sio
import scipy.misc
import numpy as np
import tensorflow as tf
from tensorflow.python.framework import ops
ops.reset_default_graph()

# Start a graph session
sess = tf.Session()

#os.chdir('/home/nick/OneDrive/Documents/tensor_flow_book/Code/8_Convolutional_Neural_Networks')

# Image Files
original_image_file = './cnt.jpg'
style_image_file = './stl.jpg'

# Saved VGG Network path
vgg_path = './imagenet-vgg-verydeep-19.mat'

# Default Arguments
#将图片初始化为内容图片，刚开始迭代的时候是否可以去除风格最小化来加快训练

original_image_weight = 5.0
style_image_weight = 200.0
regularization_weight = 50.0
learning_rate = 0.1
generations = 10000
output_generations = generations/200

# Read in images
original_image = scipy.misc.imread(original_image_file)
style_image = scipy.misc.imread(style_image_file)


# Get shape of target and make the style image the same
target_shape = original_image.shape
style_image = scipy.misc.imresize(style_image, target_shape[1] / style_image.shape[1])

# VGG-19 Layer Setup
# From paper
vgg_layers = ['conv1_1', 'relu1_1',
              'conv1_2', 'relu1_2', 'pool1',
              'conv2_1', 'relu2_1',
              'conv2_2', 'relu2_2', 'pool2',
              'conv3_1', 'relu3_1',
              'conv3_2', 'relu3_2',
              'conv3_3', 'relu3_3',
              'conv3_4', 'relu3_4', 'pool3',
              'conv4_1', 'relu4_1',
              'conv4_2', 'relu4_2',
              'conv4_3', 'relu4_3',
              'conv4_4', 'relu4_4', 'pool4',
              'conv5_1', 'relu5_1',
              'conv5_2', 'relu5_2',
              'conv5_3', 'relu5_3',
              'conv5_4', 'relu5_4']

# Extract weights and matrix means
def extract_net_info(path_to_params):
    vgg_data = sio.loadmat(path_to_params)
    normalization_matrix = vgg_data['normalization'][0][0][0]
    mat_mean = np.mean(normalization_matrix, axis=(0,1))
    network_weights = vgg_data['layers'][0]
    return(mat_mean, network_weights)
    

#根据数据重构训练完成的vgg-19
# Create the VGG-19 Network
def vgg_network(network_weights, init_image):
    network = {}
    image = init_image

    for i, layer in enumerate(vgg_layers):
        if layer[1] == 'c':
            weights, bias = network_weights[i][0][0][0][0]
            weights = np.transpose(weights, (1, 0, 2, 3))
            bias = bias.reshape(-1)
            conv_layer = tf.nn.conv2d(image, tf.constant(weights), (1, 1, 1, 1), 'SAME')
            image = tf.nn.bias_add(conv_layer, bias)
        elif layer[1] == 'r':
            image = tf.nn.relu(image)
        else:
            image = tf.nn.max_pool(image, (1, 2, 2, 1), (1, 2, 2, 1), 'SAME')
        network[layer] = image
    return(network)

# Here we define which layers apply to the original or style image
original_layer = 'relu4_2'
style_layers = ['relu1_1', 'relu2_1', 'relu3_1', 'relu4_1', 'relu5_1']

# Get network parameters
normalization_mean, network_weights = extract_net_info(vgg_path)

shape = (1,) + original_image.shape
style_shape = (1,) + style_image.shape
original_features = {}
style_features = {}

# Get network parameters
image = tf.placeholder('float', shape=shape)
vgg_net = vgg_network(network_weights, image)


# Normalize original image
original_minus_mean = original_image - normalization_mean
original_norm = np.array([original_minus_mean])
#内容图像输入vgg的某层输出
original_features[original_layer] = sess.run(vgg_net[original_layer],
                                             feed_dict={image: original_norm})



# Get style image network
image = tf.placeholder('float', shape=style_shape)
vgg_net = vgg_network(network_weights, image)
style_minus_mean = style_image - normalization_mean
style_norm = np.array([style_minus_mean])

for layer in style_layers:
    layer_output = sess.run(vgg_net[layer], feed_dict={image: style_norm})
    layer_output = np.reshape(layer_output, (-1, layer_output.shape[3]))
    style_gram_matrix = np.matmul(layer_output.T, layer_output) / layer_output.size
    #a.T*a/size
    #风格图片输入vgg的某几层输出的gram矩阵
    style_features[layer] = style_gram_matrix


#生成随机图片,输入到vgg net中
# Make Combined Image
#initial = tf.random_normal(shape)


initial = tf.cast(tf.expand_dims(original_image, axis=0),tf.float32)
image = tf.Variable(initial)
vgg_net = vgg_network(network_weights, image)

#根据选择的层计算内容损失
# Loss
original_loss = original_image_weight * (2 * tf.nn.l2_loss(vgg_net[original_layer] - original_features[original_layer]) /
                original_features[original_layer].size)
                
# Loss from Style Image
style_loss = 0
style_losses = []
for style_layer in style_layers:
    layer = vgg_net[style_layer]
    feats, height, width, channels = [x.value for x in layer.get_shape()]
    size = height * width * channels
    features = tf.reshape(layer, (-1, channels))
    style_gram_matrix = tf.matmul(tf.transpose(features), features) / size
    style_expected = style_features[style_layer]
    style_losses.append(2 * tf.nn.l2_loss(style_gram_matrix - style_expected) / style_expected.size)
style_loss += style_image_weight * tf.reduce_sum(style_losses)
        
# To Smooth the resuts, we add in total variation loss       
#总变差,使图像变得更平滑
total_var_x = sess.run(tf.reduce_prod(image[:,1:,:,:].get_shape()))
total_var_y = sess.run(tf.reduce_prod(image[:,:,1:,:].get_shape()))
first_term = regularization_weight * 2
second_term_numerator = tf.nn.l2_loss(image[:,1:,:,:] - image[:,:shape[1]-1,:,:])
second_term = second_term_numerator / total_var_y
third_term = (tf.nn.l2_loss(image[:,:,1:,:] - image[:,:,:shape[2]-1,:]) / total_var_x)
total_variation_loss = first_term * (second_term + third_term)
    
# Combined Loss
#loss = original_loss + style_loss + total_variation_loss
#引入总变差损失是图像光滑?渐变是否只是使图片变得模糊了??(相当于均值滤波)
loss = original_loss + style_loss 

# Declare Optimization Algorithm
optimizer = tf.train.AdamOptimizer(learning_rate)
train_step = optimizer.minimize(loss)

init=tf.global_variables_initializer()

# Initialize Variables and start Training
sess.run(init)
for i in range(generations):
    
    sess.run(train_step)
    # Print update and save temporary output
    if (i+1) % output_generations == 0:
        print('Generation {} out of {}'.format(i + 1, generations))
        print sess.run(loss)
        image_eval = sess.run(image)
        best_image_add_mean = image_eval.reshape(shape[1:]) + normalization_mean
        output_file = 'temp_output_{}.jpg'.format(i)
        scipy.misc.imsave(output_file, best_image_add_mean)
        
        
# Save final image
image_eval = sess.run(image)
best_image_add_mean = image_eval.reshape(shape[1:]) + normalization_mean
output_file = 'final_output.jpg'
scipy.misc.imsave(output_file, best_image_add_mean)
