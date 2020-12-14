#!-*-coding:utf8-*-
from PIL import Image
from pylab import *

photo_path="../yzby.jpg"
pil_im=Image.open(photo_path) #open image

pil_im.show()

box=(100,100,400,400)
region=pil_im.crop(box) #裁剪指定区域

region=region.transpose(Image.ROTATE_180) #旋转180
pil_im.paste(region,box) #将region粘贴到box指定区域

pil_im.show()

out=pil_im.resize((128,128))
out.show()
out=pil_im.rotate(45)
out.show()


pil_im.thumbnail((128,128)) #创建缩略图，缩略图原地存储在pil_im
pil_im.show()

#---#
figure()

pil_im=Image.open(photo_path) #open Image 
g_pil_im=array(pil_im.convert('L')) #convert gray image

contour(g_pil_im,origin='image') #图像轮廓
show()
