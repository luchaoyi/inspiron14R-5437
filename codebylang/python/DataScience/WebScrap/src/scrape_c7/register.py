#coding:utf8

#OCR(Optical Character Recognition):光学字符识别,是指对图片文件中的文字进行分析识别，获取的过程。
#Tesseract：开源的OCR识别引擎，初期Tesseract引擎由HP实验室研发，后来贡献给了开源软件业，后经由Google进行改进，消除bug，优化，重新发布。
#pytesseract是tesseract的python接口
#linux command line:>tesseract tesseract_0376.png result



REGISTER_URL='http://example.webscraping.com/user/register'


from login import parse_html as parse_form
import pprint 
import cookielib,urllib,urllib2


import pytesseract
import PIL


from io import BytesIO
import lxml.html

def get_captcha(html):
    tree = lxml.html.fromstring(html)
    img_data=tree.cssselect('div#recaptcha img')[0].get('src') #div id=recaptcha 下的img_data
    #print img_data
    #base64使用ASCII编码二进制数据
    #data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAABgCAIAAAB9kzvfAACX/klEQVR4nOTdZ5Qc1b0o+l25Ouc8...
    img_data=img_data.partition(',')[-1] #得到图片数据，将第一个逗号前的内容去除
    binary_img_data=img_data.decode('base64') #解码
    file_like=BytesIO(binary_img_data) #封装为类似文件接口
    img=PIL.Image.open(file_like)
    return img


#将图片转为2值图像
def bw_image(img):
    gray=img.convert('L')
    bw=gray.point(lambda x:0 if x<1 else 255,'1') #x<1 return 0 ;else return 255
    return bw


def demo_pytesseract(): 
	img=PIL.Image.open('tesseract_0376.png')
	print pytesseract.image_to_string(img)
	#'0376'



def demo0():
    cj=cookielib.CookieJar()
    openr=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    html=openr.open(REGISTER_URL).read()
    form=parse_form(html)
    pprint.pprint(form)
    """
    注册表单
    {'_formkey': 'b3fec06e-8882-45a8-82e8-47da1ff985e9', 
 '_formname': 'register',
 '_next': '/',
 'email': '',
 'first_name': '',
 'last_name': '',
 'password': '',
 'password_two': '',
 'recaptcha_response_field': None}
    """

    img=get_captcha(html)

    img.save('cap_ori.png')
    gray=img.convert('L')
    gray.save('cap_gray.png')
    bw=gray.point(lambda x:0 if x<1 else 255,'1') #x<1 return 0 ;else return 255
    bw.save('cap_bw.png')

    print pytesseract.image_to_string(img)
    print pytesseract.image_to_string(gray)
    print pytesseract.image_to_string(bw)



def register(first_name,last_name,email,password):
    cj=cookielib.CookieJar()
    openr=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    html=openr.open(REGISTER_URL).read()
    form=parse_form(html)
    img=get_captcha(html)
    
    #使用OCR识别引擎之前对图像处理变换为二值图像更有利于识别
    bw=bw_image(img)
    captcha=pytesseract.image_to_string(bw).lower()
    print captcha

    form['first_name']=first_name
    form['last_name']=last_name
    form['email']=email
    form['password']=form['password_two']=password
    form['recaptcha_response_field']=captcha

    encoded_data=urllib.urlencode(form)
    request=urllib2.Request(REGISTER_URL,encoded_data)
    response=openr.open(request)
    success='/user/register' not in response.geturl()
    return success

if __name__=="__main__":
    #demo_pytesseract()
    #demo0()
    print register("qwe","j","edc098@qq.com",'123456')

