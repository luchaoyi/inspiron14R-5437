#coding:utf8

import time


#sunday一种简单有效的字符串匹配算法
#极端坏的情况
#S: bbbbbbbbbbbbbbbbbbbbbbb
#T: bbcb 
#此时相当于在做BF,性能比BF还差


def is_match(S,T,i):
    j=0
    while j<len(T):
        if S[i+j]==T[j]:
            j+=1
        else:
            return False
        
    return True

def sunday(S,T):
    m=len(S)
    n=len(T)
    i=0
    while i+n<=m:
        #从对齐的i位置检查对齐
        if is_match(S,T,i):
            return i
        else:
            #找到S与T对齐后末尾之后的一个字符
            c=S[i+n]
            pos=-1
            for j in range(n-1,-1,-1):
                if c==T[j]:   
                    pos=j
            #在T中寻找是否存在字符c,找出T中最后一个出现c的位置(从后向前匹配)pos
            #下一次匹配中S的字符c的位置与T中pos对齐
            i=i+n-pos
            
    return -1



#代码优化
#寻找c中是否存在T,存在则最后一个位置,则可以事先对T进行处理,产生一个字典
def info_T(T,n):
    T_d={}
    for i in range(n):
        T_d[T[i]]=i
    
    return T_d


def sunday_opt(S,T):
    m=len(S)
    n=len(T)
    i=0
    T_d=info_T(T, n)
    while i+n<=m:
        #从对齐的i位置检查对齐
        if is_match(S,T,i):
            return i
        else:
            #找到S与T对齐后末尾之后的一个字符
            c=S[i+n]
            #在T中寻找是否存在字符c,找出T中最后一个出现c的位置(从后向前匹配)pos
            #下一次匹配中S的字符c的位置与T中pos对齐
            
            #优化->从T_d直接得到最后的index,不存在则返回-1
            pos=T_d.get(c,-1)
            i=i+n-pos
            
    return -1
   




if __name__=="__main__":
    S="codemonkeyconcoconcocdsfsdfsdfsdfasdaasdasvascdsdasdasdfsaddasdfadsfasvsafasdfasdsccdsddfkhjsdbjsbdvjbfdfasafsafdfasdfasdfasdfsdafasdfasdfadsfadsssssssssdfsdfsdfsafsdfadgadsljdh;sHSDHGLJsdhf.HF;HSFsdhgFBFblsdjfgiuggfqqpuiergqivbqlavsqpeinf;shfpileuqrbaivebfvbslidfvliskfdvi"
    T="sdfasdfsdafasdfa"
    
    st=time.time()
    print sunday(S,T)
    print time.time()-st
    
    st=time.time()
    print sunday_opt(S,T)
    print time.time()-st
    
    st=time.time()
    print S.find(T)
    print time.time()-st
    
    
              
