#!-*-coding:utf8-*-
#将图像读入numpy数组，则可以对图像进行任意数学操作

# Image.fromarray 可以将数组读入返回一个PIL.Image对象
# pylab.array 可以将图像读入，返回一个numpy数组

from PIL import Image
from pylab import array
import matplotlib.pyplot as plt  

import imtool

photo_path="../yzby.jpg"
pil_im=Image.open(photo_path) #open image

im=imtool.imresize(array(pil_im),(128,128))

#将数组绘制
plt.imshow(im)
plt.show()

