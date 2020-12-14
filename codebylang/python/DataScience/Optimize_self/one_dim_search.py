#!coding:utf8

#Bug point:
#matlab index start 1 ;python index start 0
#matlab 1:3=1,2,3;python 1:3=1,2 without 3

def split_618(fun,l,h,thres):
    #_618影响搜索精度

    _618=(5**0.5-1.0)/2
    x1=l+(h-l)*_618
    x2=l+(h-x1)

    while h-l>thres:
        if(fun(x1)>=fun(x2)):
            h=x1 
            x1=x2 
            x2=l+(h-x1)
        else:
            l=x2
            x2=x1
            x1=l+(h-x2)
            
    return h/2+l/2

#连分式
def contfract(f,l,h,n=3,thres=0.0001):
    h=(h-l)/n
    X=[l+i*h for i in range(n+1)]
    Z=[df(f,xi) for xi in X]

    #[0->n+1]
    for i in range(1,n+1):
        j=i
        while j<=n:
            X[j]=(Z[j]-Z[i-1])/(X[j]-X[i-1])
            j=j+1

    Xbar=X[0]
    while True:
        #X[i] is bi
        #n-1->0
        XI=[xi for xi in X]
        for i in range(n-1,-1,-1):
            XI[i]=XI[i]-Z[i]/XI[i+1]

        if abs(Xbar-XI[0])<thres:
            return XI[0]

        #XI[0] 是零点f'(x)零点预测值，精度不够则XI[0]加入为X[n+1]
        Xbar=XI[0]
        #X[n+1],Z[n+1]

        Znew=df(f,XI[0])

        if abs(Znew)<thres:
            return XI[0]

        X.append(XI[0])
        Z.append(Znew)
        #1->n+1
        for i in range(1,n+1+1):
            X[n+1]=(Z[n+1]-Z[i-1])/(X[n+1]-X[i-1])#b[n+1]

        #print XI[0]
        n=n+1


def fbnq(fun,l,h,thres):
    #注意这里f0,f1赋值为浮点数，否则1/2=0
    f0=1.0
    f1=2.0
    f2=f1+f0 
    fmax=(h-l)/thres
    while f2<fmax:
        f2=f1+f0 
        x1=l+f0/f2*(h-l)
        x2=l+f1/f2*(h-l)
        if fun(x1)>=fun(x2):
            l=x1 
        else:
            h=x2 
        f0=f1
        f1=f2 

    return h/2+l/2

def advance_back(fun,l,h,thres,p):
    x0=(h+l)/2

    while abs(p)>thres:
        #这里没有考虑h,l，简化了
        if fun(x0+p)<fun(x0):
            x0=x0+p

            p=p+p
        else:
            p=-p/4

    return x0 


#dsc 先搜索,后插值。
def dsc(f,thres,p,x0):
    x_1=x0 
    x1=x0 
    x2=x0

# 没有 do while ，while true if break 模拟
    while True:
        #搜索方向，f增大则换一个方向
        if f(x0+p)>f(x0):
            p=-p
        #沿p加步探测直到遇到不下降
        while f(x0)>=f(x0+p):
            x_1=x0 #x0 is current point xk ,x_1 is xk-1  
            x0=x0+p
            p=p+p
        # x_1 |x0  x2|  x1         4点等距
        #  a   b   c
        #      a   b     c         丢弃一个
        x1=x0+p
        p=p/2
        x2=x1-p

        if f(x2)>f(x0):
            xa=x_1
            xb=x0
            xc=x2 
        else:
            xa=x0
            xb=x2
            xc=x1 

        x0=xb+0.5*(f(xa)-f(xc))/(f(xa)-2*f(xb)+f(xc))*p

        if abs((f(xa)-f(xc))/f(xa))<thres:
            return x0
        p=p/4

def powell(f,thres,p,x0):
    # x0 x1 x2  
    # x2 x0 x1 
    x1=x0+p	
    if f(x1)<f(x0):#p方向下降
        x2=x1+p
    else:
        x2=x0-p		
    #初始探测找三点插值，得到第四点。
    #以四点为基础迭代 丢弃过程和插值过程.
    while True:
        xnew=0.5*((x1**2-x2**2)*f(x0)+(x2**2-x0**2)*f(x1)+(x0**2-x1**2)*f(x2))/((x1-x2)*f(x0)+(x2-x0)*f(x1)+(x0-x1)*f(x2))

        x=[x0,x1,x2,xnew]
        #x[0:3] is 0 1 2 [0,3) 不包含上界
        if abs(x[x.index(min(x[0:3],key=f))]-xnew)<thres:
            return xnew
        else:
            x=sorted(x)
            #dsc丢弃方法
            if f(x[1])<f(x[2]):
                x0=x[0]
                x1=x[1]
                x2=x[2]
            else:
                x0=x[1]
                x1=x[2]
                x2=x[3]

#dsc 1-5 求出一个xnew
#powell 5 丢弃一个
#powell 4-5 迭代插值
def dsc_powell(f,thres,p,x0):
#dsc 1-5
    x_1=x0 
    x1=x0 
    x2=x0
# 没有 do while ，while true if break 模拟
    while True:
        #搜索方向，f增大则换一个方向
        if f(x0+p)>f(x0):
            p=-p
        #沿p加步探测直到遇到不下降
        while f(x0)>=f(x0+p):
            x_1=x0 #x0 is current point xk ,x_1 is xk-1  
            x0=x0+p
            p=p+p
        # x_1 |x0  x2|  x1         4点等距
        #  a   b   c
        #      a   b     c         丢弃一个
        x1=x0+p
        p=p/2
        x2=x1-p

        if f(x2)>f(x0):
            xa=x_1
            xb=x0
            xc=x2 
        else:
            xa=x0
            xb=x2
            xc=x1 

        x0=xb+0.5*(f(xa)-f(xc))/(f(xa)-2*f(xb)+f(xc))*p
        #loop 1 次
        break 
	
        #if abs((f(xa)-f(xc))/f(xa))<thres:
            #return x0
        #p=p/4

    xnew=x0
    x0=xa
    x1=xb
    x2=xc 
    #powell 5-4-5
    while True:
	x=[x0,x1,x2,xnew]
        if abs(x[x.index(min(x[0:3],key=f))]-xnew)<thres:
            return xnew
        else:
            #dsc丢弃方法
            x=sorted(x)
            if f(x[1])<f(x[2]):
                x0=x[0]
	        x1=x[1]
    	        x2=x[2]
            else:
    	        x0=x[1]
                x1=x[2]
	        x2=x[3]
        xnew=0.5*((x1**2-x2**2)*f(x0)+(x2**2-x0**2)*f(x1)+(x0**2-x1**2)*f(x2))/((x1-x2)*f(x0)+(x2-x0)*f(x1)+(x0-x1)*f(x2))



#牛顿迭代要求x0距离极小值比较近,因此开始可以采用别的方法粗略搜索,靠近时采用newton法
def newton(f,x0,thres):
    #use dsc thres=2 粗粒度搜索

    x0=dsc(f,2,20,x0)
    while abs(df(f,x0))>thres:
        x0=x0-df(f,x0)/ddf(f,x0)
        #print x0

    return x0


#用割线代替切线，避免出现切线=0情况
def secant(f,x0,thres):
    x1=dsc(f,2,20,x0)

    while abs(df(f,x1))>thres:
        x2=x1-(x1-x0)*df(f,x1)/(df(f,x1)-df(f,x0))
        x0=x1
        x1=x2
        #print x2

    return x1

def df(f,x0,delta_x=0.00001):
    return (f(x0+delta_x)-f(x0))/delta_x

def ddf(f,x0,delta_x=0.00001):
    return (df(f,x0+delta_x,delta_x)-df(f,x0,delta_x))/delta_x






if __name__=="__main__":
    def tf0(x):
        return x**2+1
    def tf1(x):
        return x**4-x**3+x**2-6*x-13

    #0.618法区间越大，
    x_start=split_618(tf1,-30,30,0.001)
    print x_start,tf1(x_start)

    x_start=contfract(tf1,-30,30)
    print x_start,tf1(x_start)

    x_start=fbnq(tf1,-30,30,0.001)
    print x_start,tf1(x_start)


    x_start=advance_back(tf1,-3.0,3.0,0.0001,0.5)
    print x_start,tf1(x_start)


    x_start=dsc(tf1,0.001,0.5,-10)
    print x_start,tf1(x_start)

    x_start=powell(tf1,0.001,0.5,-10)
    print x_start,tf1(x_start)

    x_start=dsc_powell(tf1,0.001,0.5,-10)
    print x_start,tf1(x_start)

    #print df(tf0,3)
    #print ddf(tf0,3)

    x_start=newton(tf1,-100,0.0001)
    print x_start,tf1(x_start)

    x_start=secant(tf1,-100,0.0001)
    print x_start,tf1(x_start)


    
