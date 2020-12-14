#-*-coding:utf8-*-



#读入utf8文本转为unicode
print "loading..."
f1=open(sampfn)
try:
    f1_text=f1.read()
    f1_text=unicode(f1_text,'uft-8')
finally:
    f1.close()
f1_seg_list=jieba.cut(f1_text)

f_stop=open("stopwords.txt")
try:
    f_stop_text=f_stop.read()
    f_stop_text=unicode(f_stop_text)
finally:
    f_stop.close()

f_stop_seg_list=f_stop_text.split('\n')
test_words={}
all_words={}

#去除停用词语
for myword in f1_seg_list:
    print "."
    if not(myword.strip()) in f_stop_seg_list:
        test_words.setdefault(myword,0)
        all_words.setdefault(myword,0)
        all_words[myword]+=1
    
